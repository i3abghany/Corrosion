#pragma once

#include "Prototypes.h"
#include "Buffer.h"

Corrosion::const_s32 Corrosion::make_const_ret_func(int32_t val)
{
	Buffer buf{};
	if (!buf)
		return Corrosion::const_s32();
	buf.emit_mov_imm32_into_rax(val);
	buf.emit_ret();
	return MAKE_CONST_S32(buf.data());
}

Corrosion::identity Corrosion::make_identity()
{
	// mov rax, rcx
	// ret
	Buffer buf{};
	if (!buf)
		return Corrosion::identity();
	buf.emit_mov_rcx_into_rax();
	buf.emit_ret();
	return MAKE_IDENTITY(buf.data());
}



Corrosion::increment_s64 Corrosion::make_increment_64()
{
	uint8_t* buf = (uint8_t*)VirtualAlloc(NULL, 128, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!buf)
		return Corrosion::increment_s64();
	buf[0] = 0x48;
	buf[1] = 0x83;
	buf[2] = 0xEC;
	buf[3] = 0x04; // make room for 
	return MAKE_INCREMENT_S64(buf);
}
