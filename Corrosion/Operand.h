#pragma once

#include <cstdint>
#include "Register.h"

enum class OperandType
{
	None,
	Register,
	Imm8,
};

struct Operand
{
	Operand(Register reg)
	{
		m_type = OperandType::Register;
		m_reg = reg;
	}

	Operand(uint8_t value)
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
extern const Operand rsp;
extern const Operand rcx;
extern const Operand rbx;
extern const Operand rdx;