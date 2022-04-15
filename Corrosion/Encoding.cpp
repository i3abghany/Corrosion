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

const std::unordered_map<Mnemonic, const MnemonicEncodings*> encodings_map
{
	{Mnemonic::mov, &mov_encodings},
	{Mnemonic::ret, &ret_encodings}
};