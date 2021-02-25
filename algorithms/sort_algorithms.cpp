#include "sort_algorithms.h"

#include <limits>

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
			for(size_t i(from_index); i != to_index - 1; ++i)
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
			for(size_t i(from_index); i != to_index - 1; ++i)
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
	if (from_index < to_index - 1)
	{
		size_t mid_index = (from_index + to_index) / 2;
		merge_sort(arr, from_index, mid_index, oper);
		merge_sort(arr, mid_index, to_index, oper);
		merge(arr, from_index, mid_index, to_index, oper);
	}
}

void sort::merge(std::vector<double>& arr,const int& from_index,const int& mid_index,const int& to_index,const char& oper)
{
	size_t arr1_size = mid_index - from_index; 
	size_t arr2_size = to_index - mid_index; 
	std::vector<double> left(arr1_size + 1);
	std::vector<double> right(arr2_size + 1);

	for (size_t i(0); i < arr1_size; ++i)
	{
		left[i] = arr[from_index + i];
	}

	for (size_t i(0); i < arr2_size; ++i)
	{
		right[i] = arr[mid_index + i];
	}
	switch(oper)
	{
		case '<':

			left[arr1_size] = std::numeric_limits<double>::infinity();
			right[arr2_size] = std::numeric_limits<double>::infinity();

			for(size_t k(from_index), i(0), m(0); k < to_index; ++k)
			{
				if(i < arr1_size && left[i] <= right[m])
				{
					arr[k] = left[i];
					++i;
				}
				else
				{
					arr[k] = right[m];
					++m;
				}
			}

			break;
		case '>':

			left[arr1_size] = -std::numeric_limits<double>::infinity();
			right[arr2_size] = -std::numeric_limits<double>::infinity();

			for(size_t k(from_index), i(0), m(0); k < to_index; ++k)
			{
				if(i < arr1_size && left[i] >= right[m])
				{
					arr[k] = left[i];
					++i;
				}
				else
				{
					arr[k] = right[m];
					++m;
				}
			}
			break;
	}
}
