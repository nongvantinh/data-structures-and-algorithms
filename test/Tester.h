#ifndef DSAA_TESTER_H
#define DSAA_TESTER_H
#include <cassert>
#include <iostream>

struct verify;
class tester
{
	friend verify;
	const tester *self;
	double m_value;

public:
	static int livecount;
	constexpr tester() noexcept: self(this), m_value(0.0) { ++livecount; }
	constexpr tester(double p_value) noexcept : self(this), m_value(p_value) { ++livecount; }
	constexpr tester(const tester &p_other) noexcept : self(this), m_value(p_other.m_value) { ++livecount; }
	constexpr tester(tester &&p_other) noexcept : self(this), m_value(p_other.m_value)
	{
		++livecount;
		p_other.m_value = 0.0;
	}
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

	tester &operator=(tester &&p_other)
	{
		assert(self == this && p_other.self == &p_other);

		m_value = p_other.m_value;

		p_other.m_value = 0.0;
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
	~verify()
	{
		std::cout << "livecount: " << tester::livecount << std::endl;
		assert(tester::livecount == 0);
	}
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

bool operator<=(const tester &p_first, const tester &p_last)
{
	return (p_first.value() <= p_last.value());
}

bool operator>=(const tester &p_first, const tester &p_last)
{
	return (p_first.value() >= p_last.value());
}

#endif //DSAA_TESTER_H