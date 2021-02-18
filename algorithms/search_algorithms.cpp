#include "search_algorithms.h"

int clrs::linear_search(const std::vector<double>& v, const double& value, int from_index, int to_index)
{
	int result(-1);

	for (size_t i(from_index); i != to_index; ++i)
	{
		if (v[i] == value)
		{
			return i;
		}
	}
	return result;
}