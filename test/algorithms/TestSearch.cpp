#ifndef DSAA_TEST_SEARCH_H
#define DSAA_TEST_SEARCH_H

#include "Catch2/Catch.hpp"
#include "algorithms/Search.h"
#include "arrays/Array.h"
#include <algorithm>
#include "Test.h"

TEST_CASE("test binary search", "[search]")
{
	SECTION("An ordinary sequence")
	{
		dsaa::Array<int> arr{1, 2, 3, 5, 8, 13, 21};
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 3) == 3);
	}
	SECTION("The empty sequence")
	{
		dsaa::Array<int> arr;
		REQUIRE(dsaa::binary_search(arr.begin(), arr.end(), 5) == arr.end());
	}
	SECTION("Just one element")
	{
		dsaa::Array<int> arr{1};
		REQUIRE(dsaa::binary_search(arr.begin(), arr.end(), 1) != arr.end());
	}
	SECTION("Even number of elements")
	{
		dsaa::Array<int> arr{1, 2, 3, 4};
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 4) == 4);
	}
	SECTION("Odd number of elements")
	{
		dsaa::Array<int> arr{1, 2, 3, 4, 5};
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("All elements equal: ")
	{
		dsaa::Array<int> arr{1, 1, 1, 1, 1, 1, 1};
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("Difference element at begining: ")
	{
		dsaa::Array<int> arr{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 0) == 0);
	}
	SECTION("Difference element at end: ")
	{
		dsaa::Array<int> arr{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("A very large ordered sequence.")
	{
		dsaa::Array<int> arr(101);
		for (size_t i(0); i < arr.size(); ++i)
			arr[i] = i;
		REQUIRE(*dsaa::binary_search(arr.begin(), arr.end(), 75) == 75);
	}
	SECTION("Some sequences with a random number of elements (but still ordered)..")
	{
		dsaa::Array<int> arr(222);
		for (size_t i(0); i < arr.size(); ++i)
			arr[i] = dsaa::random_range();
		std::sort(arr.begin(), arr.end());
		REQUIRE((*dsaa::binary_search(arr.begin(), arr.end(), 75) == 75 || dsaa::binary_search(arr.begin(), arr.end(), 75) == arr.end()));
	}
}

TEST_CASE("test linear search", "[search]")
{
	SECTION("An ordinary sequence")
	{
		dsaa::Array<int> arr{1, 2, 3, 5, 8, 13, 21};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 3) == 3);
	}
	SECTION("The empty sequence")
	{
		dsaa::Array<int> arr;
		REQUIRE(dsaa::linear_search(arr.begin(), arr.end(), 5) == arr.end());
	}
	SECTION("Just one element")
	{
		dsaa::Array<int> arr{1};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("Even number of elements")
	{
		dsaa::Array<int> arr{1, 2, 3, 4};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 4) == 4);
	}
	SECTION("Odd number of elements")
	{
		dsaa::Array<int> arr{1, 2, 3, 4, 5};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("All elements equal: ")
	{
		dsaa::Array<int> arr{1, 1, 1, 1, 1, 1, 1};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("Difference element at begining: ")
	{
		dsaa::Array<int> arr{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 0) == 0);
	}
	SECTION("Difference element at end: ")
	{
		dsaa::Array<int> arr{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 1) == 1);
	}
	SECTION("A very large ordered sequence.")
	{
		dsaa::Array<int> arr(101);
		for (size_t i(0); i < arr.size(); ++i)
			arr[i] = i;
		REQUIRE(*dsaa::linear_search(arr.begin(), arr.end(), 75) == 75);
	}
	SECTION("Some sequences with a random number of elements.")
	{
		dsaa::Array<int> arr(222);
		for (size_t i(0); i < arr.size(); ++i)
			arr[i] = dsaa::random_range();
		REQUIRE((*dsaa::linear_search(arr.begin(), arr.end(), 75) == 75 || dsaa::linear_search(arr.begin(), arr.end(), 75) == arr.end()));
	}
	SECTION("Some sequences with random elements (but still ordered)..")
	{
		dsaa::Array<int> arr(222);
		for (size_t i(0); i < arr.size(); ++i)
			arr[i] = dsaa::random_range();
		std::sort(arr.begin(), arr.end());

		REQUIRE((*dsaa::linear_search(arr.begin(), arr.end(), 75) == 75 || dsaa::linear_search(arr.begin(), arr.end(), 75) == arr.end()));
	}
}

#endif //!DSAA_TEST_SEARCH_H
