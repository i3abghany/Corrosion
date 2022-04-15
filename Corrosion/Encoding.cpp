#include "Encoding.h"

const MnemonicEncodings mov_encodings{
	Mnemonic::mov,
	{
		{
			0x89,
			ExtensionType::REGISTER,
			OperandEncodingType::RegisterMemory,
			OperandEncodingType::Register
		},
	}
};

const MnemonicEncodings ret_encodings{
	Mnemonic::ret,
	{
		{
			0xC2,
			ExtensionType::REGISTER,
			OperandEncodingType::None,
			OperandEncodingType::None
		},
	}
};

const MnemonicEncodings add_encodings{
	Mnemonic::add,
	{
		{
			0x83, // Opcode
			ExtensionType::OPCODE,
			0x00, // Opcode extension
			OperandEncodingType::RegisterMemory,
			OperandEncodingType::Imm8
		},
	}
};

const MnemonicEncodings sub_encodings{
	Mnemonic::sub,
	{
		{
			0x83, // Opcode
			ExtensionType::OPCODE,
			0x05, // Opcode extension
			OperandEncodingType::RegisterMemory,
			OperandEncodingType::Imm8
		},
	}
};

const std::unordered_map<Mnemonic, const MnemonicEncodings*> encodings_map
{
	{Mnemonic::add, &add_encodings},
	{Mnemonic::mov, &mov_encodings},
	{Mnemonic::ret, &ret_encodings},
	{Mnemonic::sub, &sub_encodings}
};