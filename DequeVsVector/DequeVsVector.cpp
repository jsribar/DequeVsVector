#include "StopWatch.h"
#include "limited_queue.h"
#include "multi_pattern_match.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

template <typename T>
void push(std::deque<T>& deque, T elem)
{
	deque.push_back(std::move(elem));
	deque.pop_front();
}

template <typename T>
void push_rotate(std::vector<T>& vector, T elem)
{
	auto it = std::rotate(vector.begin(), vector.begin() + 1, vector.end());
	*it = std::move(elem);
}

template <typename T>
void push(std::vector<T>& vector, T elem)
{
	vector.erase(vector.cbegin());
	vector.push_back(std::move(elem));
}

template <typename T, class C, class I>
C prepare(I elems)
{
	return C<T>(elems.cbegin(), elems.cend());
}

void ComparePush()
{
	std::string input{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit." };
	std::deque<char> deque(input.cbegin(), input.cend());
	std::vector<char> vector(input.cbegin(), input.cend());

	const int count = 1000000;

	for (int j = 0; j < 10; ++j)
	{
		{
			StopWatch sw;
			for (int i = 0; i < count; ++i)
			{
				char app = i % 26 + 'A';
				push(deque, app);
			}
		}

		{
			StopWatch sw;
			for (int i = 0; i < count; ++i)
			{
				char app = i % 26 + 'A';
				push(vector, app);
			}
		}

		{
			StopWatch sw;
			for (int i = 0; i < count; ++i)
			{
				char app = i % 26 + 'A';
				push_rotate(vector, app);
			}
		}

		std::cout << std::endl;
	}
}

void CompareMismatch()
{
	std::string input{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit." };
	std::deque<char> deque(input.cbegin(), input.cend());
	std::vector<char> vector(input.cbegin(), input.cend());

	std::string match{ "Lorem ipsum dolor sit amet," };

	const size_t count = 1000000;

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = std::mismatch(match.cbegin(), match.cend(), deque.cbegin(), deque.cend());
			assert(res.first == match.cend() && res.second != deque.cend());
		}
	}

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = std::mismatch(match.cbegin(), match.cend(), vector.cbegin(), vector.cend());
			assert(res.first == match.cend() && res.second != vector.cend());
		}
	}
}

void CompareMismatchBack()
{
	std::string input{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit." };
	std::deque<char> deque(input.cbegin(), input.cend());
	std::vector<char> vector(input.cbegin(), input.cend());

	std::string match{ ", consectetur adipiscing elit." };

	const size_t count = 1000000;

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = std::mismatch(match.crbegin(), match.crend(), deque.crbegin(), deque.crend());
			assert(res.first == match.crend() && res.second != deque.crend());
		}
	}

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = std::mismatch(match.crbegin(), match.crend(), vector.crbegin(), vector.crend());
			assert(res.first == match.crend() && res.second != vector.crend());
		}
	}
}

void CompareMismatchOffset()
{
	std::string input{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit." };
	std::deque<char> deque(input.cbegin(), input.cend());
	std::vector<char> vector(input.cbegin(), input.cend());

	std::string match{ ", consectetur adipiscing elit." };

	const size_t count = 1000000;

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto diff = deque.size() - match.size();
			auto res = std::mismatch(match.cbegin(), match.cend(), deque.cbegin() + diff, deque.cend());
			assert(res.first == match.cend() && res.second == deque.cend());
		}
	}

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto diff = vector.size() - match.size();
			auto res = std::mismatch(match.cbegin(), match.cend(), vector.cbegin() + diff, vector.cend());
			assert(res.first == match.cend() && res.second == vector.cend());
		}
	}
}

void CompareMatchEnd()
{
	multi_pattern_match<char> patterns;
	patterns.add_pattern(", consectetur adipiscing elit.");
	patterns.add_pattern(", consectetur adipiscing elit");
	patterns.add_pattern(", consectetur adipiscing eli");

	std::string input{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit." };

	limited_vector_queue<char> vector(patterns.get_longest());
	limited_deq_queue<char> deque(patterns.get_longest());
	for (auto ch : input)
	{
		vector.push_back(ch);
		deque.push_back(ch);
	}

	const size_t count = 1000000;

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = patterns.matches_end(vector.cbegin(), vector.cend());
			assert(res);
		}
	}

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = patterns.matches_end(deque.cbegin(), deque.cend());
			assert(res);
		}
	}

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = patterns.matches_end(deque.cbegin(), deque.cend());
			assert(res);
		}
	}

	{
		StopWatch sw;
		for (int i = 0; i < count; ++i)
		{
			auto res = patterns.matches_end(vector.cbegin(), vector.cend());
			assert(res);
		}
	}
}


int main()
{
	//ComparePush();

	//CompareMismatch();

	//std::cout << std::endl;

	//CompareMismatchBack();

	//std::cout << std::endl;

	//CompareMismatchOffset();

	CompareMatchEnd();
}
