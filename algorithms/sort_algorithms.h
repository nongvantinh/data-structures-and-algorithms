#include <iostream>
#include <vector>

namespace clrs
{
	// O(n^2). Sort vector with [from_index, to_index) in oper order.
	void insertion_sort(std::vector<double>& arr, const int& from_index, const int& to_index, const char& oper);

	// O(n^2). Sort vector with [from_index, to_index) in oper order.
	void bubble_sort(std::vector<double>& arr);

	// O(nlog(n)). Sort vector with [from_index, to_index) in oper order.
	void merge_sort(std::vector<double>& v, int from_index, int to_index, char oper);
	void merge(std::vector<double>& v, int p, int q, int r, char oper);
}
