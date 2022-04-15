#pragma once

#include <windows.h>
#include <cassert>
#include <iostream>

#include "Prototypes.h"
#include "Instruction.h"
#include "Operand.h"
#include "Register.h"
#include "Encoding.h"

class Buffer
{
public:
	explicit Buffer(size_t msize = 128ULL)
	{
		buf = (uint8_t*)VirtualAlloc(NULL, msize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		memory_size = msize;
	}

	operator bool() const
	{
		return buf != NULL;
	}

	void emit_sub_rsp_imm8(uint8_t value);

	void emit_add_rsp_imm8(uint8_t value);

	void emit_mov_imm32_to_stack_at_offset(uint32_t imm32, uint8_t offset);

	void emit_add_from_stack_at_offset_to_ecx(uint8_t offset);

	void emit_mov_imm32_into_rax(const uint32_t imm);

	void emit_mov_rcx_into_rax();

	void emit(const Instruction& insn);

	void append_u8(uint8_t byte);

	void append_u32(uint32_t dword);

	uint8_t* data() const { return buf; }

private:
	uint8_t* buf = NULL;
	size_t occupied = 0;
	size_t memory_size;
};

