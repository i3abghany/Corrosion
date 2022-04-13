#pragma once

#include "Operand.h"

enum Mnemonic
{
	mov = 1,
};

struct Instruction
{
	Mnemonic mnemonic;
	Operand op1, op2;
};