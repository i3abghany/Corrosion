#pragma once

#include <cstdint>
#include <vector>

#include "Instruction.h"
#include "Operand.h"

enum MOD
{
	DISPLACEMENT_S0  = 0b00,
	DISPLACEMENT_S8  = 0b01,
	DISPLACEMENT_S32 = 0b10,
	REGISTER_ADDR    = 0b11,
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
	None,
	Register,
	RegisterMemory,
};

struct InstructionEncoding
{
	uint16_t opcode;
	ExtensionType extension;
	OperandEncodingType op1_type, op2_type;
};

struct MnemonicEncodings
{
	Mnemonic mnemonic;
	std::vector<InstructionEncoding> encodings;

	MnemonicEncodings(Mnemonic m, std::vector<InstructionEncoding> arr)
		: mnemonic(m), encodings(std::move(arr))
	{
	}
};

extern MnemonicEncodings mov_encodings;
extern MnemonicEncodings ret_encodings;