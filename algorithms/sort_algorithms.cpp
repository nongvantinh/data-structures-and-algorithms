#include "sort_algorithms.h"

void clrs::insertion_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper)
{
	switch (oper)
	{
	case '<':
	{
		for (int i(from_index + 1); i != to_index; ++i)
		{
			double key = arr[i];
			int index = i - 1;
			while (from_index <= index && key < arr[index])
			{
				arr[index + (size_t)1] = arr[index];
				--index;
			}
			arr[index + (size_t)1] = key;
		}
	}
	break;
	case '>':
		for (int i(from_index + 1); i != to_index; ++i)
		{
			double key = arr[i];
			int index = i - 1;
			while (from_index <= index && key > arr[index])
			{
				arr[index + (size_t)1] = arr[index];
				--index;
			}
			arr[index + (size_t)1] = key;
		}
		break;
	default:
		break;
	}
}

void clrs::bubble_sort(std::vector<double>& arr)
{
	for (size_t i(0); i < arr.size(); ++i)
	{
		for (size_t k(i + 1); k < arr.size(); ++k)
		{
			if (arr[k] < arr[i])
			{
				std::swap(arr[k], arr[i]);
			}
		}
	}
}

// O(nlog(n)).
void  clrs::merge_sort(std::vector<double>& v, int from_index, int to_index, char oper)
{
	std::vector<double> result(v);
	if (from_index < to_index - 1)
	{
		size_t mid = ((from_index + to_index - 1) / 2);
		merge_sort(result, from_index, mid + 1, oper);
		merge_sort(result, mid + 1, to_index, oper);
		merge(result, from_index, mid, to_index - 1, oper);
	}

}

void  clrs::merge(std::vector<double>& v, int p, int q, int r, char oper)
{
	std::vector<double> result(v);
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	std::vector<double> left(n1 + 1);
	std::vector<double> right(n2 + 1);
	left[left.size() - 1] = 999999;
	right[right.size() - 1] = 999999;

	for (size_t i(0); i < n1; ++i)
	{
		left[i] = result[p + i];
	}

	for (size_t i(0); i < n2; ++i)
	{
		right[i] = result[q + 1 + i];
	}
	//for (size_t m(p), i(0); )
}
