#pragma once

#include <algorithm>
#include <vector>
#include <deque>

namespace core { namespace unpacker { namespace certutil {

template <typename T, class Container>
class limited_queue
{
public:
	limited_queue(size_t max_size)
		: max_size_m(max_size)
		, min_size_m(max_size)
	{
	}

	limited_queue(size_t max_size, size_t min_size)
		: max_size_m(max_size)
		: min_size_m(min_size)
	{
	}

	void push_back(const T& val)
	{
		container_m.push_back(val);
		shrink();
	}

	void clear() noexcept
	{
		container_m.clear();
	}

	bool empty() const noexcept
	{
		return container_m.empty();
	}

	void reset(size_t max_size, size_t min_size)
	{
		clear();
		max_size_m = max_size;
		min_size_m = min_size;
	}

	template <typename const_iterator = Container::const_iterator>
	const_iterator cbegin() noexcept
	{
		return container_m.cbegin();
	}

	template <typename const_iterator = Container::const_iterator>
	const_iterator cend() noexcept
	{
		return container_m.cend();
	}

	size_t size() const noexcept
	{
		return container_m.size();
	}

	size_t max_size() const noexcept
	{
		return max_size_m;
	}

	size_t min_size() const noexcept
	{
		return min_size_m;
	}

protected:
	Container container_m;
	size_t min_size_m;
	size_t max_size_m;

private:
	virtual void shrink() = 0;
};

// implementation with std::vector
template <typename T>
class limited_vector_queue : public limited_queue<T, std::vector<T>>
{
public:
	using limited_queue::limited_queue;

private:
	void shrink() override
	{
		while (container_m.size() > max_size_m)
			container_m.erase(container_m.begin());
	}
};

// implementation with std::dequeue
template <typename T>
class limited_deq_queue : public limited_queue<T, std::deque<T>>
{
public:
	using limited_queue::limited_queue;

private:
	void shrink() override
	{
		while (container_m.size() > max_size_m)
			container_m.pop_front();
	}
};

} } } // namespace core::unpacker::certutil