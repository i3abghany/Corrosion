#pragma once

#include <cstdint>

#include "Operand.h"

enum MOD
{
	DISPLACEMENT_s0  = 0b00,
	DISPLACEMENT_s8  = 0b01,
	DISPLACEMENT_s32 = 0b10,
	REGISTER_ADDR    = 0b11
};

enum REX
{
	REX   =     0b01000000,
	REX_W = REX | (1 << 3),
	REX_R = REX | (1 << 2),
	REX_X = REX | (1 << 1),
	REX_B = REX | (1 << 0),
};

enum class ExtensionType
{
	REGISTER,
	OPCODE,
	OPCODE_EMBED,
};

enum class OperandEncodingType
{
	RegisterMemory,
	Register,
};

struct InstructionEncoding
{
	uint16_t opcode;
	ExtensionType extension;
	OperandEncodingType op1, op2;
};