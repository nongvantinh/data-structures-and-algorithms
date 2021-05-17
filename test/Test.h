#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <random>
#include <cassert>

// An "ordinary sequence": {1, 2, 3, 5, 8, 13, 21}
// The empty sequence: { }
// Just one element: { 1 }
// Even number of elements: {1, 2, 3, 4}
// Odd number of elements: {1, 2, 3, 4, 5}
// All elements equal: {1, 1, 1, 1, 1, 1, 1}
// Difference element at begining: {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// Difference element at end: {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}

// Some test sequences are best generated by a program:
// A very large sequence.
// Some sequences with a random number of elements.
// Some sequences with random elements (but still ordered).

struct verify;
class tester
{
	friend verify;
	static int livecount;
	const tester *self;
	double m_value;

public:
	tester() : self(this), m_value(0) { ++livecount; }
	tester(double p_value) : self(this), m_value(p_value) { ++livecount; }
	tester(const tester &p_other) noexcept : self(this), m_value(p_other.m_value) { ++livecount; }
	~tester()
	{
		assert(self == this);
		--livecount;
	}
	tester &operator=(const tester &p_other)
	{
		assert(self == this && p_other.self == &p_other);
		m_value = p_other.m_value;
		return *this;
	}
	double &value() { return m_value; }
	double const &value() const { return m_value; }
	void cfunction() const { assert(self == this); }
	void mfunction() { assert(self == this); }
};

int tester::livecount = 0;
struct verify
{
	~verify() { assert(tester::livecount == 0); }
} verifier;

std::ostream &operator<<(std::ostream &os, tester const &test)
{
	os << test.value();
	return os;
}

bool operator==(const tester &p_first, const tester &p_last)
{
	return p_first.value() == p_last.value();
}

bool operator!=(const tester &p_first, const tester &p_last)
{
	return !(p_first == p_last);
}

bool operator<(const tester &p_first, const tester &p_last)
{
	return (p_first.value() < p_last.value());
}

bool operator<=(const tester &p_first, const tester &p_last)
{
	return (p_first.value() <= p_last.value());
}

bool operator>(const tester &p_first, const tester &p_last)
{
	return (p_first.value() > p_last.value());
}

bool operator>=(const tester &p_first, const tester &p_last)
{
	return (p_first.value() >= p_last.value());
}

tester operator-(const tester &p_first, const tester &p_last)
{
	return tester(p_first.value() - p_last.value());
}

unsigned int random_range(unsigned int start = 0, unsigned int end = 678)
{
	std::random_device device;
	std::mt19937 engine(device());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end); // distribution in range [1, 6]
	return dist6(engine);
}

template <class Iterator>
void print_elem(Iterator p_first, Iterator p_last)
{
	std::cout << "{ ";
	while (p_first != p_last)
	{
		std::cout << *p_first << ",";
		++p_first;
	}
	std::cout << " }" << std::endl;
}

#endif // !TEST_H
