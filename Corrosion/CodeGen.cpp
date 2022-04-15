#pragma once

#include "Prototypes.h"
#include "Buffer.h"

Corrosion::const_s32 Corrosion::make_const_ret_func(int32_t val)
{
	Buffer buf{};
	if (!buf)
		return Corrosion::const_s32();
	buf.emit_mov_imm32_into_rax(val);
	buf.emit({ Mnemonic::ret });
	return MAKE_CONST_S32(buf.data());
}

// mov rax, rcx
// ret
Corrosion::identity Corrosion::make_identity()
{
	Buffer buf{};
	if (!buf)
		return Corrosion::identity();
	buf.emit_mov_rcx_into_rax();
	buf.emit({ Mnemonic::ret, Operand{}, Operand{} });
	return MAKE_IDENTITY(buf.data());
}

Corrosion::increment_s64 Corrosion::make_increment_64()
{
	Buffer buf{};
	if (!buf)
		return Corrosion::increment_s64();

	buf.emit_sub_rsp_imm8(4);

	// mov DWORD PTR [rsp + 0], 1
	buf.emit_mov_imm32_to_stack_at_offset(1, 0);

	// add ecx, DWORD PTR [rsp + 0]
	buf.emit_add_from_stack_at_offset_to_ecx(0);

	buf.emit_add_rsp_imm8(4);

	buf.emit_mov_rcx_into_rax();
	buf.emit({ Mnemonic::ret, Operand{}, Operand{} });
	return MAKE_INCREMENT_S64(buf.data());
}
