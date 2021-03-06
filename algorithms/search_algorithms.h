#include <iostream>
#include <vector>

namespace algorithms 
{
	namespace search
	{
		int linear_search(const std::vector<double>& arr,const int& from_index, const int& to_index,const double& value);
		int binary_search(const std::vector<double>& arr, const int& from_index, const int& to_index, const double& value);
	}
}
