#include "Buffer.h"

void Buffer::emit_sub_rsp_imm8(uint8_t value)
{
	buf[occupied++] = 0x48;
	buf[occupied++] = 0x83;
	buf[occupied++] = 0xEC;
	buf[occupied++] = value;
}

void Buffer::emit_add_rsp_imm8(uint8_t value)
{
	buf[occupied++] = 0x48;
	buf[occupied++] = 0x83;
	buf[occupied++] = 0xC4;
	buf[occupied++] = value;
}

void Buffer::emit_mov_imm32_to_stack_at_offset(uint32_t imm32, uint8_t offset)
{
	buf[occupied++] = 0xC7;
	buf[occupied++] = 0x44;
	buf[occupied++] = 0x24;
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

void Buffer::emit_ret()
{
	buf[occupied++] = 0xC2;
}

void Buffer::emit_mov_imm32_into_rax(const uint32_t imm)
{
	buf[occupied++] = 0x48;
	buf[occupied++] = 0xc7;
	buf[occupied++] = 0xc0;
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

void Buffer::emit(const Instruction& insn)
{
	switch (insn.mnemonic)
	{
	case mov:
		emit_mov(insn);
	default:
		break;
	}
}

void Buffer::emit_mov(const Instruction& insn)
{
	// FIXME: lookup table for possible encodings
	InstructionEncoding encoding{
		0x89,
		ExtensionType::REGISTER,
		OperandEncodingType::RegisterMemory,
		OperandEncodingType::Register
	};

	// FIXME: check that encoding matches insn.
	// FIXME: add REX.W if necessary only.
	append_u8(REX::REX_W);

	// FIXME: opcode could be 2 bytes...
	append_u8((uint8_t)encoding.opcode);

	uint8_t modrm = (MOD::REGISTER_ADDR << 6) |
		(insn.op1.m_reg.index() << 3) |
		(insn.op2.m_reg.index());

	append_u8(modrm);
}
