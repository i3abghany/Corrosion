#include "Buffer.h"

void Buffer::emit_sub_rsp_imm8(uint8_t value)
{
	append_u8(0x48);
	append_u8(0x83);
	append_u8(0xEC);
	append_u8(value);
}

void Buffer::emit_add_rsp_imm8(uint8_t value)
{
	append_u8(0x48);
	append_u8(0x83);
	append_u8(0xC4);
	append_u8(value);
}

void Buffer::emit_mov_imm32_to_stack_at_offset(uint32_t imm32, uint8_t offset)
{
	append_u8(0xC7);
	append_u8(0x44);
	append_u8(0x24);
	append_u8(offset);
	append_u32(imm32);
}

void Buffer::emit_add_from_stack_at_offset_to_ecx(uint8_t offset)
{
	append_u8(0x03);
	append_u8(0x4C);
	append_u8(0x24);
	append_u8(offset);
}

void Buffer::emit_mov_imm32_into_rax(const uint32_t imm)
{
	append_u8(0x48);
	append_u8(0xC7);
	append_u8(0xC0);
	append_u32(imm);
}

void Buffer::emit_mov_rcx_into_rax()
{
	Instruction insn{ Mnemonic::mov, rcx, rax };
	emit(insn);
}

void Buffer::append_u8(uint8_t byte)
{
	buf[occupied++] = byte;
}

void Buffer::append_u32(uint32_t dword)
{
	auto dw_ptr = (uint32_t*)&buf[occupied];
	*dw_ptr = dword;
	occupied += sizeof(dword);
}

void Buffer::emit_ret(const Instruction& insn)
{
	auto enc = ret_encodings.encodings[0];
	append_u8(enc.opcode);
}

void Buffer::emit(const Instruction& insn)
{
	switch (insn.mnemonic)
	{
	case Mnemonic::mov:
		emit_mov(insn);
		break;
	case Mnemonic::ret:
		emit_ret(insn);
	default:
		break;
	}
}

static InstructionEncoding get_matching_encoding(const Instruction& insn, std::vector<InstructionEncoding> encodings)
{

	const auto matching_operand = [](const OperandType op_type, const OperandEncodingType enc_type) -> bool
	{
		if (op_type == OperandType::Register &&
			(enc_type == OperandEncodingType::Register || enc_type == OperandEncodingType::RegisterMemory))
			return true;

		if (op_type == OperandType::None && enc_type == OperandEncodingType::None)
			return true;

		return false;
	};

	for (const auto& enc : mov_encodings.encodings)
	{
		if (!matching_operand(insn.op1.m_type, enc.op1_type) || !matching_operand(insn.op2.m_type, enc.op2_type))
			continue;
		return enc;
	}

	assert(false);
	return {};
}

void Buffer::emit_mov(const Instruction& insn)
{
	InstructionEncoding encoding = get_matching_encoding(insn, mov_encodings.encodings);

	if (encoding.op1_type == OperandEncodingType::Register ||
		encoding.op2_type == OperandEncodingType::Register ||
		encoding.op1_type == OperandEncodingType::RegisterMemory ||
		encoding.op2_type == OperandEncodingType::RegisterMemory)
	{
		append_u8(REX::REX_W);
	}

	// FIXME: opcode could be 2 bytes...
	append_u8((uint8_t)encoding.opcode);

	uint8_t modrm = (MOD::REGISTER_ADDR << 6) |
		(insn.op1.m_reg.index() << 3) |
		(insn.op2.m_reg.index());

	append_u8(modrm);
}
