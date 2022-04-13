#pragma once

#include <windows.h>
#include <cassert>
#include <iostream>

#include "Prototypes.h"

class Buffer
{
public:
	explicit Buffer(size_t memory_size = 128ULL)
	{
		buf = (uint8_t*)VirtualAlloc(NULL, memory_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}

	operator bool() const
	{
		return buf != NULL;
	}

	void emit_sub_rsp_imm8(uint8_t value)
	{
		buf[occupied++] = 0x48;
		buf[occupied++] = 0x83;
		buf[occupied++] = 0xEC;
		buf[occupied++] = value;
	}

	void emit_add_rsp_imm8(uint8_t value)
	{
		buf[occupied++] = 0x48;
		buf[occupied++] = 0x83;
		buf[occupied++] = 0xC4;
		buf[occupied++] = value;
	}

	void emit_mov_imm32_to_stack_at_offset(uint32_t imm32, uint8_t offset)
	{
		buf[occupied++] = 0xC7;
		buf[occupied++] = 0x44;
		buf[occupied++] = 0x24;
		append_u8(offset);
		append_u32(imm32);
	}

	void emit_add_from_stack_at_offset_to_ecx(uint8_t offset)
	{
		append_u8(0x03);
		append_u8(0x4C);
		append_u8(0x24);
		append_u8(offset);
	}

	void emit_ret()
	{
		buf[occupied++] = 0xC2;
	}

	void emit_mov_imm32_into_rax(const uint32_t imm)
	{
		buf[occupied++] = 0x48;
		buf[occupied++] = 0xc7;
		buf[occupied++] = 0xc0;
		append_u32(imm);
	}

	void emit_mov_rcx_into_rax()
	{
		buf[occupied++] = 0x48;
		buf[occupied++] = 0x89;
		buf[occupied++] = 0xC8;
	}

	void append_u8(uint8_t byte)
	{
		buf[occupied++] = byte;
	}

	void append_u32(uint32_t dword)
	{
		auto dw_ptr = (uint32_t*)&buf[occupied];
		*dw_ptr = dword;
		occupied += sizeof(dword);
	}

	uint8_t* data() const { return buf; }

private:
	uint8_t* buf = NULL;
	size_t occupied = 0;
};

