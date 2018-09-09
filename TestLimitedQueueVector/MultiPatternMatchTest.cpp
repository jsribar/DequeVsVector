#include "stdafx.h"
#include "CppUnitTest.h"

#include "../DequeVsVector/multi_pattern_match.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(multi_pattern_match)
	{
	public:
		using match = core::unpacker::certutil::multi_pattern_match<char>;

		TEST_METHOD(add_pattern_increases_size)
		{
			match m;
			m.add_pattern("abc");
			Assert::AreEqual(size_t(1), m.get_patterns().size());
		}

		TEST_METHOD(after_add_pattern_patterns_are_sorted_by_length)
		{
			match m;
			m.add_pattern("abcde");
			m.add_pattern("abc");
			m.add_pattern("abcd");
			Assert::IsTrue(m.get_patterns()[0].size() < m.get_patterns()[1].size());
			Assert::IsTrue(m.get_patterns()[1].size() < m.get_patterns()[2].size());
		}

		TEST_METHOD(match_for_single_pattern_returns_true_if_search_string_is_equal_to_pattern)
		{
			match m;
			m.add_pattern("bcd");

			std::string search("bcd");
			Assert::IsTrue(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_single_pattern_returns_true_if_search_string_ends_with_pattern)
		{
			match m;
			m.add_pattern("bcd");

			std::string search("abcd");
			Assert::IsTrue(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_single_pattern_returns_false_if_search_string_is_shorter_than_pattern)
		{
			match m;
			m.add_pattern("bcd");

			std::string search("cd");
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));

			search = "bc";
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_single_pattern_returns_false_if_search_string_starts_with_pattern)
		{
			match m;
			m.add_pattern("bcd");

			std::string search("bcde");
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_multiple_patterns_returns_true_if_search_string_is_equal_to_pattern)
		{
			match m;
			m.add_pattern("bcd");
			m.add_pattern("bcd");

			std::string search("bcd");
			Assert::IsTrue(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_multiple_patterns_returns_true_if_search_string_ends_with_pattern)
		{
			match m;
			m.add_pattern("bcd");
			m.add_pattern("aaa");
			m.add_pattern("bbb");

			std::string search("abcd");
			Assert::IsTrue(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_multiple_patterns_returns_false_if_search_string_is_shorter_than_pattern)
		{
			match m;
			m.add_pattern("bcd");
			m.add_pattern("aaa");
			m.add_pattern("bbb");

			std::string search("cd");
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));

			search = "bc";
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_multiple_patterns_returns_false_if_search_string_starts_with_pattern)
		{
			match m;
			m.add_pattern("bcd");
			m.add_pattern("aaa");
			m.add_pattern("bbb");

			std::string search("bcde");
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));
		}

		TEST_METHOD(match_for_multiple_patterns_returns_false_for_partially_matching_patterns_but_not_ending)
		{
			match m;
			m.add_pattern("cde");
			m.add_pattern("abc");
			m.add_pattern("bcd");

			std::string search("abcdef");
			Assert::IsFalse(m.matches_end(search.cbegin(), search.cend()));
		}
	};
}