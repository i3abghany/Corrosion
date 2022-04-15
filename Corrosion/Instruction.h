#pragma once

#include "Operand.h"

enum class Mnemonic
{
	mov,
	ret,
};

struct Instruction
{
	Mnemonic mnemonic;
	Operand op1, op2;

	Instruction(Mnemonic m, Operand o1 = {}, Operand o2 = {})
		: mnemonic(m), op1(o1), op2(o2)
	{
	}
};