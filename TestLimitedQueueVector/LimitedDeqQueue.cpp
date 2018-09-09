#include "stdafx.h"
#include "CppUnitTest.h"

#include "../DequeVsVector/limited_queue.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(limited_deq_queue)
	{
	public:
		template <typename T>
		using queue = core::unpacker::certutil::limited_deq_queue<T>;

		TEST_METHOD(push_back_increases_size)
		{
			queue<char> lq(5);
			lq.push_back('A');
			Assert::AreEqual(size_t(1), lq.size());
		}

		TEST_METHOD(push_back_doesnot_increase_size_beyond_max_size)
		{
			queue<char> lq(2);
			lq.push_back('A');
			lq.push_back('B');
			Assert::AreEqual(size_t(2), lq.size());
			lq.push_back('C');
			Assert::AreEqual(size_t(2), lq.size());
		}

		TEST_METHOD(cbegin_returns_iterator_to_first_element)
		{
			queue<char> lq(2);
			lq.push_back('A');
			lq.push_back('B');
			Assert::AreEqual('A', *lq.cbegin());
		}

		TEST_METHOD(clear_removes_all_elements)
		{
			queue<char> lq(2);
			lq.push_back('A');
			lq.push_back('B');
			lq.clear();
			Assert::AreEqual(size_t(0), lq.size());
			Assert::IsTrue(lq.empty());
		}

	};
}