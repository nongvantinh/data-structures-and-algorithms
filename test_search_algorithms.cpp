#include "test_search_algorithms.h"

#include "search_algorithms.h"
#include "sort_algorithms.h"

#include <vector>
#include <cstdlib>

bool algorithms::test::search::test_linear_search()
{
	std::vector<double> v;
	for(size_t i(0); i < 1000; ++i)
	{
		v.resize(i + 1);
		for(size_t index(0); index != v.size(); ++index)
		{
			v[index] = rand() % (50000 - -50000 + 1) + -50000;
		}
		double value(v[rand() % ((v.size()-1) - 0 + 1) + 0]);
		int index = algorithms::search::linear_search(v, 0, v.size(), value);
		if(index == -1)
			return false;
	}
	return true;
}

bool algorithms::test::search::test_binary_search()
{
	std::vector<double> v;
	for(size_t i(0); i < 1000; ++i)
	{
		v.resize(i + 1);
		for(size_t index(0); index != v.size(); ++index)
		{
			v[index] = rand() % (50000 - -50000 + 1) + -50000;
		}
		algorithms::sort::merge_sort(v, 0, v.size(), '<');
		double value(v[rand() % ((v.size()-1) - 0 + 1) + 0]);
		int index = algorithms::search::binary_search(v, 0, v.size(), value);
		if(index == -1)
			return false;
	}
	return true;
}

