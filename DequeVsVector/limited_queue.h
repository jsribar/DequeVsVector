#pragma once

#include <algorithm>

template <class Container>
class limited_queue
{
public:
	limited_queue(size_t max_size)
		: max_size_m(max_size)
	{
	}

	template <typename T>
	void push_back(const T& val)
	{
		container_m.push_back(val);
		while (container_m.size() > max_size_m)
			container_m.erase(container_m.begin());
	}

	//template <class Pattern>
	//bool match_end(const Pattern& pattern)
	//{
	//	return std::mismatch(container_m.crbegin(), container_m.crend(), pattern.crbegin(), pattern.crend()).second == pattern.crend();
	//}

	size_t size() const noexcept
	{
		return container_m.size();
	}

	template <typename iterator = Container::iterator>
	iterator begin() noexcept
	{
		return container_m.begin();
	}

	template <typename iterator>
	iterator end() noexcept
	{
		return container_m.end();
	}
private:
	Container container_m;
	size_t min_size_m;
	size_t max_size_m;
};

