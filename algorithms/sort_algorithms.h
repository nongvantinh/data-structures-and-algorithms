#include <iostream>
#include <vector>

namespace algorithms 
{
	namespace sort
	{
		// O(n^2).
		void insertion_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper);
		// O(n^2).
		void selection_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper);
		// O(n^2).
		void bubble_sort(std::vector<double>& arr,  const int& from_index, const int& to_index, const char& oper);
		// O(nlog(n)).
		void merge_sort(std::vector<double>& arr,  const int& from_index, const int& to_index, const char& oper);
		// O(n).
		void merge(std::vector<double>& arr,const int& from_index,const int& mid_index,const int& to_index,const char& oper);
	}		
}
