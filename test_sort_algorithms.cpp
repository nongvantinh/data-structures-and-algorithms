#include "test_sort_algorithms.h"

#include "sort_algorithms.h"

#include <vector>

bool algorithms::test::sort::test_insertion_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % (50000 - -50000 + 1) + -50000;
	}

	char oper = '>';
	algorithms::sort::insertion_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	algorithms::sort::insertion_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}

bool algorithms::test::sort::test_selection_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % 50000 - 25000;
	}
	char oper = '>';
	algorithms::sort::selection_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	algorithms::sort::selection_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}
	return true;
}

bool algorithms::test::sort::test_bubble_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % (50000 - -50000 + 1) + -50000;
	}

	char oper = '>';
	algorithms::sort::bubble_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	algorithms::sort::bubble_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}

bool algorithms::test::sort::test_merge_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % (50000 - -50000 + 1) + -50000;
	}

	char oper = '>';
	algorithms::sort::merge_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	algorithms::sort::merge_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}
