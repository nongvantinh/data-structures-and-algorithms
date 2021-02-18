#include <iostream>
#include <vector>
#include <ctime>

#include "facilities.h"
#include "algorithms/search_algorithms.h"
#include "algorithms/sort_algorithms.h"

void test();
void test_sort_algorithms();
bool test_insertion_sort(std::vector<double> v);
bool test_bubble_sort(std::vector<double> v);

void test_linear_search();

int giai_thua(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	return n * giai_thua(n - 1);
}

int main()
{
	srand(time(NULL));
	test();
	// test_linear_search();
}

void test()
{
	test_sort_algorithms();
}

void test_sort_algorithms()
{
	std::vector < double> v(10000);
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % 50000 - 25000;
	}

	std::cout << "---------------------------------------------\n";
	std::cout << "sort array with size:: " << v.size() << std::endl;
	std::cout << "running test_insertion_sort: " << (test_insertion_sort(v) ? "OK." : "Failed.") << std::endl;
	return;
	std::cout << "running test_bubble_sort: " << (test_bubble_sort(v) ? "OK." : "Failed.") << std::endl;
}

bool test_insertion_sort(std::vector<double> v)
{
	char oper = '>';
	clrs::insertion_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] > v[i - 1])
			return false;
	}
	oper = '<';
	clrs::insertion_sort(v, 0, v.size(), oper);
	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}

bool test_bubble_sort(std::vector<double> v)
{
	clrs::bubble_sort(v);

	for (size_t i = 1; i < v.size(); ++i)
	{
		if (v[i] < v[i - 1])
			return false;
	}

	return true;
}

void test_linear_search()
{
	std::vector<double> v{ 1,6,7,5,2,6 };
	print(v);
	double value(-88888888888);
	std::cout << "enter value to find: ";
	std::cin >> value;
	int index = clrs::linear_search(v, value, 0, v.size());
	std::cout << "search: " << value << " at index: " << index << std::endl;
}
