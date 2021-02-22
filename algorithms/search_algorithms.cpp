#include "search_algorithms.h"

using namespace algorithms;

int search::linear_search(const std::vector<double>& arr,int from_index, int to_index, double value)
{
	int result(-1);
	for (size_t i(from_index); i != to_index; ++i)
	{
		if (arr[i] == value)
		{
			result = i;
			break;
		}
	}
	return result;
}
