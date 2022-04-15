#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

#include "Instruction.h"
#include "Operand.h"
#include "Macros.h"

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
	Imm8,
};

struct InstructionEncoding
{
	uint16_t opcode;
	ExtensionType extension;
	uint8_t opcode_extension;
	OperandEncodingType op1_type, op2_type;

	InstructionEncoding(uint16_t opc, ExtensionType ext, OperandEncodingType o1t, OperandEncodingType o2t)
		: opcode(opc), extension(ext), op1_type(o1t), opcode_extension(0), op2_type(o2t)
	{
		VERIFY(ext != ExtensionType::OPCODE);
	}

	InstructionEncoding(uint16_t opc, ExtensionType ext, uint8_t op_ext, OperandEncodingType o1t, OperandEncodingType o2t)
		: opcode(opc), extension(ext), op1_type(o1t), opcode_extension(op_ext), op2_type(o2t)
	{
		VERIFY(ext == ExtensionType::OPCODE);
	}

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

const extern MnemonicEncodings add_encodings;
const extern MnemonicEncodings mov_encodings;
const extern MnemonicEncodings ret_encodings;
const extern MnemonicEncodings sub_encodings;

const extern std::unordered_map<Mnemonic, const MnemonicEncodings*> encodings_map;