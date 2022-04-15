#pragma once

#include <cstdint>
#include "Register.h"

enum class OperandType
{
	None,
	Register,
};

struct Operand
{
	Operand(Register reg)
	{
		m_type = OperandType::Register;
		m_reg = reg;
	}

	Operand()
	{
		m_type = OperandType::None;
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