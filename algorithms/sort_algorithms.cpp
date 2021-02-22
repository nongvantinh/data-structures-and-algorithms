#include "sort_algorithms.h"

using namespace algorithms;

void sort::insertion_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper)
{
	switch (oper)
	{
		case '<':
			{
				for (int i(from_index + 1); i != to_index; ++i)
				{
					double key = arr[i];
					int index = i - 1; // Can not mark index as size_t. size_t can not store negative value.
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

void sort::selection_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper)
{
	switch(oper)
	{
		case '<':
			for(size_t i(from_index); i != to_index; ++i)
			{
				size_t index(i);
				for(size_t k(i + 1); k != to_index; ++k)
				{
					if(arr[k] < arr[index])
					{
						index = k;
					}	
				}	
				if(index != i)
				{
					double temp(arr[i]);
					arr[i] = arr[index];
					arr[index] = temp;
				}
			}
			break;
		case '>':
			for(size_t i(from_index); i != to_index; ++i)
			{
				size_t index(i);
				for(size_t k(i + 1); k != to_index; ++k)
				{
					if(arr[k] > arr[index])
					{
						index = k;
					}	
				}	
				if(index != i)
				{
					double temp(arr[i]);
					arr[i] = arr[index];
					arr[index] = temp;
				}
			}

			break;
		default:
			break;
	}
}

void sort::bubble_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper)
{
	switch(oper)
	{
		case '<':
			for (size_t i(from_index); i != to_index; ++i)
			{
				for (size_t k(i + 1); k != to_index; ++k)
				{
					if (arr[k] < arr[i])
					{
						double temp(arr[i]);
						arr[i] = arr[k];
						arr[k] = temp;
					}
				}
			}
			break;
		case '>':
			for (size_t i(from_index); i < to_index; ++i)
			{
				for (size_t k(i + 1); k < to_index; ++k)
				{
					if (arr[k] > arr[i])
					{
						double temp(arr[i]);
						arr[i] = arr[k];
						arr[k] = temp;
					}
				}
			}
			break;
		default:
			break;
	}
}

void sort::merge_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper)
{
	return;
	if (from_index < to_index - 1)
	{
		size_t mid = ((from_index + to_index - 1) / 2);
		merge_sort(arr, from_index, mid + 1, oper);
		merge_sort(arr, mid + 1, to_index, oper);
		merge(arr, from_index, mid, to_index - 1, oper);
	}

}

void sort::merge(std::vector<double>& v, int p, int q, int r, char oper)
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
