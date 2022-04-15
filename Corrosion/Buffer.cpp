#include "Buffer.h"
#include "Macros.h"

#include <unordered_map>

void Buffer::emit_sub_rsp_imm8(uint8_t value)
{
	Instruction insn{ Mnemonic::sub, rsp, Operand{value} };
	emit(insn);
}

void Buffer::emit_add_rsp_imm8(uint8_t value)
{
	Instruction insn{ Mnemonic::add, rsp, Operand{value} };
	emit(insn);
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
	Instruction insn{ Mnemonic::mov, rax, rcx };
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

static InstructionEncoding get_matching_encoding(const Instruction& insn, std::vector<InstructionEncoding> encs)
{
	const auto matching_operand = [](const OperandType op_type, const OperandEncodingType enc_type) -> bool
	{
		if (op_type == OperandType::Register &&
			(enc_type == OperandEncodingType::Register || enc_type == OperandEncodingType::RegisterMemory))
			return true;

		if (op_type == OperandType::None && enc_type == OperandEncodingType::None)
			return true;

		if (op_type == OperandType::Imm8 && enc_type == OperandEncodingType::Imm8)
			return true;

		return false;
	};

	for (const auto& enc : encs)
	{
		if (!matching_operand(insn.op1.m_type, enc.op1_type) || !matching_operand(insn.op2.m_type, enc.op2_type))
			continue;
		return enc;
	}

	VERIFY_NOT_REACHED();
}

void Buffer::emit(const Instruction& insn)
{
	const MnemonicEncodings& encs = *encodings_map.at(insn.mnemonic);
	InstructionEncoding encoding = get_matching_encoding(insn, encs.encodings);

	// FIXME: We currently treat any register access as a 64-bit access.
	// REX.W prefix is only relevant if one of the operands is a 64-bit
	// or an extended register (R8 - R15)
	if (encoding.op1_type == OperandEncodingType::Register ||
		encoding.op2_type == OperandEncodingType::Register ||
		encoding.op1_type == OperandEncodingType::RegisterMemory ||
		encoding.op2_type == OperandEncodingType::RegisterMemory)
	{
		append_u8(REX::REX_W);
	}

	// FIXME: opcode could be 2 bytes...
	append_u8((uint8_t)encoding.opcode);

	bool needs_modrm = insn.op1.m_type == OperandType::Register || insn.op2.m_type == OperandType::Register;
	if (!needs_modrm)
		return;

	uint8_t modrm = 0;
	if (insn.op1.m_type == OperandType::Register || insn.op2.m_type == OperandType::Register)
		modrm |= (MOD::REGISTER_ADDR << 6);
	else
		TODO();

	if (encoding.extension == ExtensionType::REGISTER)
		modrm |= (insn.op2.m_reg.index()) << 3;
	else if (encoding.extension == ExtensionType::OPCODE)
		modrm |= (encoding.opcode_extension << 3);
	else
		TODO();

	modrm |= insn.op1.m_reg.index();
	
	append_u8(modrm);

	if (insn.op2.m_type == OperandType::Imm8)
		append_u8(insn.op1.u8_val);
}
