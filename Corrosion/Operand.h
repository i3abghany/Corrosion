#pragma once

#include <cstdint>
#include "Register.h"

struct Operand
{
	enum class OperandType
	{
		REGISTER_OPERAND = 1,
	};

	Operand(OperandType type, Register reg)
	{
		m_type = type;
		m_reg = reg;
	}

	OperandType m_type;
	union
	{
		Register m_reg;
	};
};

extern const Operand rax;
extern const Operand rcx;
extern const Operand rbx;
extern const Operand rdx;