#include "stdafx.h"
#include "CppUnitTest.h"

#include "../DequeVsVector/limited_queue.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(LimitedQueueVectorTest)
	{
	public:
		
		TEST_METHOD(push_back_increases_size)
		{
			limited_queue<std::vector<char>> lq(5);
			lq.push_back('A');
			Assert::AreEqual(size_t(1), lq.size());
		}

		TEST_METHOD(push_back_doesnot_increase_size_beyond_max_size)
		{
			limited_queue<std::vector<char>> lq(2);
			lq.push_back('A');
			lq.push_back('B');
			Assert::AreEqual(size_t(2), lq.size());
			lq.push_back('C');
			Assert::AreEqual(size_t(2), lq.size());
		}

		TEST_METHOD(begin_returns_iterator_to_first_element)
		{
			limited_queue<std::vector<char>> lq(2);
			lq.push_back('A');
			lq.push_back('B');
			Assert::AreEqual('A', *lq.begin());
		}

	};
}