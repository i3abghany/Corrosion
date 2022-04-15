#include "Encoding.h"

MnemonicEncodings mov_encodings{
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

MnemonicEncodings ret_encodings{
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