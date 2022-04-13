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

const Operand rax = {
	Operand::OperandType::REGISTER_OPERAND,
	rax_reg
};

const Operand rcx = {
	Operand::OperandType::REGISTER_OPERAND,
	rcx_reg
};

const Operand rbx = {
	Operand::OperandType::REGISTER_OPERAND,
	rbx_reg
};

const Operand rdx = {
	Operand::OperandType::REGISTER_OPERAND,
	rdx_reg
};