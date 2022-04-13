#include "pch.h"
#include "CppUnitTest.h"

#include "../Corrosion/Prototypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CorrosionTest
{
	TEST_CLASS(CorrosionTest)
	{
	public:
		
		TEST_METHOD(MakeIdentity)
		{
			auto i = Corrosion::make_identity();
			Assert::IsTrue((bool)i);
		}

		TEST_METHOD(InvokeIdentity)
		{
			auto i = Corrosion::make_identity();
			Assert::AreEqual(i(123), 123);
		}

		TEST_METHOD(MakeConstS32)
		{
			auto c = Corrosion::make_const_ret_func(123);
			Assert::IsTrue((bool)c);
		}

		TEST_METHOD(InvokeConstS32)
		{
			auto c = Corrosion::make_const_ret_func(123);
			Assert::AreEqual(c(), 123);

			c = Corrosion::make_const_ret_func(0);
			Assert::AreEqual(c(), 0);
		}

	};
}
