#pragma once

#include <cstdint>
#include <vector>
#include "Register.h"

enum class OperandType
{
	None,
	Register,
	Imm8,
};

struct Operand
{
	explicit Operand(Register reg)
	{
		m_type = OperandType::Register;
		m_reg = reg;
	}

	explicit Operand(uint8_t value)
	{
		m_type = OperandType::Imm8;
		u8_val = value;
	}

	Operand()
	{
		m_type = OperandType::None;
	}
	
	OperandType m_type;
	union
	{
		Register m_reg;
		uint8_t u8_val;
	};
};

extern const Operand rax;
extern const Operand rcx;
extern const Operand rdx;
extern const Operand rbx;
extern const Operand rsp;
extern const Operand rbp;
extern const Operand rsi;
extern const Operand rdi;
extern const Operand r8;
extern const Operand r9;
extern const Operand r10;
extern const Operand r11;
extern const Operand r12;
extern const Operand r13;
extern const Operand r14;
extern const Operand r15;

extern const std::vector<Operand> register_operands;