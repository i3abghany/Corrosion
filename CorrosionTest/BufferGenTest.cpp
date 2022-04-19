#include "pch.h"
#include "CppUnitTest.h"

#include "../Corrosion/Buffer.h"
#include "../Corrosion/Instruction.h"
#include "../Corrosion/Operand.h"

#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BufferGenTest
{
	TEST_CLASS(BufferGen)
	{
	public:

		TEST_METHOD(TestMovRegToReg)
		{
			constexpr size_t bin_size = 3;
			for (const auto& op1 : register_operands)
			{
				for (const auto& op2 : register_operands)
				{
					Buffer buf;
					Instruction insn{Mnemonic::mov, op1, op2};
					buf.emit(insn);
					uint8_t expected_bin[bin_size] = { 
						0x48,
						0x89,
						(MOD::REGISTER_ADDR << 6) | (op2.m_reg.index() << 3) | op1.m_reg.index()
					};
					Assert::AreEqual(bin_size, buf.occupied());
					uint8_t* p = buf.data();
					for (int i = 0; i < bin_size; i++)
					{
						Assert::AreEqual(expected_bin[i], p[i]);
					}
				}
			}
		}
	};
}