#include "pch.h"
#include "CppUnitTest.h"
#include "../AlgoData_Ca2/Queue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Queue_Test
{
	TEST_CLASS(Queue_Test)
	{
		Queue<int>* queue = nullptr;
		TEST_METHOD_INITIALIZE(SetUp)
		{
			queue = new Queue<int>(5);
		}
	public:
		TEST_METHOD(TestQueueConstructor)
		{
			Assert::IsNotNull(queue);
		}
		TEST_METHOD(TestEnqueue)
		{
			queue->Enqueue(1);
			queue->Enqueue(2);
			
			Assert::AreEqual(2, queue->size());
		}
		TEST_METHOD(TestFullEnqueue)
		{
			queue->Enqueue(1);
			queue->Enqueue(2);
			queue->Enqueue(3);
			queue->Enqueue(4);
			queue->Enqueue(5);
			queue->Enqueue(6);
			queue->Enqueue(7);

			Assert::AreEqual(5, queue->size());
		}
		TEST_METHOD(TestNullEnqueue)
		{
			queue->Enqueue(1);
			queue->Enqueue(NULL);

			Assert::AreEqual(1, queue->size());
		}
		TEST_METHOD(TestDequeue)
		{
			queue->Enqueue(1);
			queue->Enqueue(2);
			int result = queue->Dequeue();
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(TestEmptyDequeue)
		{
			queue->Enqueue(1);
			queue->Dequeue();
			queue->Dequeue();
			int result = queue->Dequeue();
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(TestSize)
		{
			queue->Enqueue(1);
			queue->Enqueue(2);
			queue->Dequeue();
			queue->Dequeue();
			queue->Dequeue();
			queue->Dequeue();

			Assert::AreEqual(0, queue->size());
		}
		TEST_METHOD(Testclear)
		{
			queue->Enqueue(1);
			queue->Enqueue(2);
			queue->Dequeue();
			queue->Enqueue(2);
			queue->clear();
			Assert::AreEqual(0, queue->size());
		}

	};
}
