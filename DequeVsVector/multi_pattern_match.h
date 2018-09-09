#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <vector>

namespace core { namespace unpacker { namespace certutil {

template <typename T>
class multi_pattern_match
{
	using Pattern = std::basic_string<T>;
	using PatternCollection = std::vector<Pattern>;
public:
	void add_pattern(const Pattern pattern)
	{
		patterns_m.push_back(pattern);
		sort_by_length();
	}

	template <typename InputIterator>
	bool matches_end(InputIterator first, InputIterator last)
	{
		assert(distance(first, last) >= 0);
		size_t length = std::distance(first, last);
		for (const auto& pattern : patterns_m)
		{
			if (length < pattern.size())
				break;	// patterns are sorted from shortest so no need to match further
			auto offset = length - pattern.size();
			auto mismatch = std::mismatch(pattern.cbegin(), pattern.cend(), first + offset, last);
			if (mismatch.first == pattern.cend())
			{
				assert(mismatch.second == last);
				return true;
			}
		}
		return false;
	}

	size_t get_longest() const noexcept
	{
		return patterns_m.empty() ? 0 : patterns_m.back().size();
	}

	size_t get_shortest() const noexcept
	{
		return patterns_m.empty() ? 0 : patterns_m.front().size();
	}

	const PatternCollection& get_patterns() const noexcept
	{
		return patterns_m;
	}

private:
	PatternCollection patterns_m;

	void sort_by_length()
	{
		std::sort(patterns_m.begin(), patterns_m.end(), [](const auto& p1, const auto& p2) { return p1.size() < p2.size(); });
	}
};

} } } // namespace core::unpacker::certutil
