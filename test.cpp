#include "test.h"

#include <iostream>
#include <vector>

#include "sort_algorithms.h"
#include "search_algorithms.h"
#include "facilities.h"

using namespace algorithms;

void test()
{
	test_sort_algorithms();
	test_search_algorithms();
}

void test_sort_algorithms()
{
	std::cout << "---------------------------------------------\n";
	std::cout << "running test_sort_algorithms.\n";
	std::cout << "test_insertion_sort: " << (test_insertion_sort() ? "OK." : "Failed.") << std::endl;
	std::cout << "test_selection_sort: " << (test_selection_sort() ? "OK." : "Failed.") << std::endl;
	std::cout << "test_bubble_sort: "    << (test_bubble_sort()    ? "OK." : "Failed.") << std::endl;
}

void test_search_algorithms()
{

}

bool test_insertion_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % 50000 - 25000;
	}


	char oper = '>';
	sort::insertion_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	sort::insertion_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}

bool test_selection_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % 50000 - 25000;
	}
	char oper = '>';
	sort::selection_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	sort::selection_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}
	return true;
}

bool test_bubble_sort()
{
	std::vector<double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % 50000 - 25000;
	}


	char oper = '>';
	sort::bubble_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	sort::bubble_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}

bool test_linear_search()
{
	std::vector<double> v{ 1,6,7,5,2,6 };
	double value(v[5]);
	int index = search::linear_search(v, value, 0, v.size());
	return index != -1;
}
