#include "pch.h"
#include "CppUnitTest.h"
#include "../AlgoData_Ca2/Stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Stack_Test
{
	TEST_CLASS(Stack_Test)
	{
		Stack<int> stack;

	public:
		TEST_METHOD(TestPush)
		{
			stack.push(1);
			stack.push(2);

			Assert::AreEqual(2, stack.size());

			stack.push(3);
			stack.push(4);
			stack.push(5);
			stack.push(6);

			Assert::AreEqual(6, stack.size());
		}
		TEST_METHOD(TestPop)
		{
			stack.push(1);
			stack.push(2);
			int result = stack.pop();
			Assert::AreEqual(2, result);
			result = stack.pop();
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(TestFront)
		{
			stack.push(1);
			stack.push(2);
			int result = stack.front();
			Assert::AreEqual(2, stack.size());
			Assert::AreEqual(2, result);
		}
		TEST_METHOD(TestSize)
		{
			stack.push(1);
			stack.push(2);
			Assert::AreEqual(2, stack.size());
			stack.clear();
			Assert::AreEqual(0, stack.size());
		}
	};
}
