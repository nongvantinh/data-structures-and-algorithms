#include "search_algorithms.h"


int algorithms::search::linear_search(const std::vector<double>& arr, const int& from_index, const int& to_index, const double& value)
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

int algorithms::search::binary_search(const std::vector<double>& arr, const int& from_index, const int& to_index, const double& value)
{
	int low(from_index);
	int high(to_index);
	int mid(-1);
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(mid == arr.size())
			return -1;
		else if(value == arr[mid])
			return mid;
		else if (value < arr[mid])
			high = mid;
		else
			low = mid;
	}
	return -1;
}
