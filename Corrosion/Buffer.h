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

	void emit_sub_rsp(size_t size)
	{
		// TODO: support larger sizes when needed.
		assert(size < 256);
	}

	void emit_ret()
	{
		buf[occupied] = 0xC2;
		occupied++;
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

