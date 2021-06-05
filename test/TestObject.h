#ifndef DSAA_TESTER_H
#define DSAA_TESTER_H
#include <cassert>
#include <iostream>

namespace dsaa
{
	namespace TestObject
	{
		inline int livecount(0); // C++17
		// or: extern int livecount;
		// and put definittion in TestObject.cpp: int livecount(0);
	}
}

struct verify;

template <typename T>
class TestObject
{
	const TestObject *self;
	T m_value;

public:
	constexpr TestObject() noexcept : self(this), m_value(T()) { ++dsaa::TestObject::livecount; }
	constexpr TestObject(T p_value) noexcept : self(this), m_value(p_value) { ++dsaa::TestObject::livecount; }
	constexpr TestObject(const TestObject &p_other) noexcept : self(this), m_value(p_other.m_value) { ++dsaa::TestObject::livecount; }
	constexpr TestObject(TestObject &&p_other) noexcept : self(this), m_value(std::move(p_other.m_value))
	{
		++dsaa::TestObject::livecount;
		p_other.m_value = T();
	}

	~TestObject()
	{
		assert(self == this);
		--dsaa::TestObject::livecount;
	}

	TestObject &operator=(const TestObject &p_other)
	{
		assert(self == this && p_other.self == &p_other);

		m_value = p_other.m_value;
		return *this;
	}

	TestObject &operator=(TestObject &&p_other)
	{
		assert(self == this && p_other.self == &p_other);

		m_value = std::move(p_other.m_value);

		p_other.m_value = T();
		return *this;
	}

	T &value()
	{
		assert(self == this);
		return m_value;
	}
	T const &value() const
	{
		assert(self == this);
		return m_value;
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, TestObject<T> const &p_tester)
{
	os << p_tester.value();
	return os;
}

template <typename T>
bool operator==(const TestObject<T> &p_first, const TestObject<T> &p_last)
{
	return p_first.value() == p_last.value();
}

template <typename T>
bool operator!=(const TestObject<T> &p_first, const TestObject<T> &p_last)
{
	return !(p_first == p_last);
}

template <typename T>
bool operator<(const TestObject<T> &p_first, const TestObject<T> &p_last)
{
	return (p_first.value() < p_last.value());
}

template <typename T>
bool operator<=(const TestObject<T> &p_first, const TestObject<T> &p_last)
{
	return (p_first.value() <= p_last.value());
}

template <typename T>
bool operator>=(const TestObject<T> &p_first, const TestObject<T> &p_last)
{
	return (p_first.value() >= p_last.value());
}

template <typename T>
bool operator>(const TestObject<T> &p_first, const TestObject<T> &p_last)
{
	return (p_first.value() > p_last.value());
}
#endif //DSAA_TESTER_H