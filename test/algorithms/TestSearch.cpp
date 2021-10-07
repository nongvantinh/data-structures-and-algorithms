#ifndef DSAA_TEST_SEARCH_H
#define DSAA_TEST_SEARCH_H

#include "Catch2/Catch.hpp"
#include "algorithms/Search.h"
#include "algorithms/Sort.h"
#include "arrays/DynamicArray.h"
#include "algorithms/Random.h"
#include "test/TestObject.h"

TEST_CASE("Test binary_search.", "[Search]")
{
	SECTION("An ordinary sequence.")
	{
		size_t arr_size(4);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::insertion_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]); // Element in array could be duplicate.
	}

	SECTION("The empty sequence.")
	{
		dsaa::DynamicArray<TestObject<int>> arr;
		REQUIRE(dsaa::binary_search(arr.begin(), arr.end(), TestObject<int>(dsaa::random::random_range_int<int>())) == arr.end());
	}

	SECTION("Just one element.")
	{
		dsaa::DynamicArray<TestObject<int>> arr;
		arr.insert_last(TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(0);

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Even number of elements.")
	{
		size_t arr_size(6);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::insertion_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Odd number of elements.")
	{
		size_t arr_size(7);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::insertion_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("All elements equal.")
	{
		size_t arr_size(8);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));
		// binary_search property will eleminate half of the array. Thus it will returns the midle index.
		REQUIRE(dsaa::binary_search(arr.begin(), arr.end(), arr[index]) == arr.get_iterator(arr.size() / 2));
	}

	SECTION("Difference element at begining.")
	{
		size_t arr_size(9);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(0);
		while (arr[index] >= arr[index + 1]) // binary_search requires array must be sort.
			arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Difference element at end.")
	{
		size_t arr_size(10);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(arr.size() - 1);
		while (arr[index] <= arr[index - 1]) // binary_search requires array must be sort.
			arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("A very large ordered sequence.")
	{
		size_t arr_size(679);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::merge_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Some sequences with a random number of elements (but still ordered).")
	{
		size_t arr_size(234);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::merge_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::binary_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}
}

TEST_CASE("Test linear_search.", "[Search]")
{
	SECTION("An ordinary sequence.")
	{
		size_t arr_size(4);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::insertion_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("The empty sequence.")
	{
		dsaa::DynamicArray<TestObject<int>> arr;
		REQUIRE(dsaa::linear_search(arr.begin(), arr.end(), TestObject<int>(dsaa::random::random_range_int<int>())) == arr.end());
	}

	SECTION("Just one element.")
	{
		dsaa::DynamicArray<TestObject<int>> arr;
		arr.insert_last(TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(0);

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Even number of elements.")
	{
		size_t arr_size(6);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::insertion_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Odd number of elements.")
	{
		size_t arr_size(7);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::insertion_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("All elements equal.")
	{
		size_t arr_size(8);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));
		// linear_search property will find from begining to end. Thus it will return the begining.
		REQUIRE(dsaa::linear_search(arr.begin(), arr.end(), arr[index]) == arr.begin());
	}

	SECTION("Difference element at begining.")
	{
		size_t arr_size(9);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(0);
		while (arr[index] == arr[index + 1])
			arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Difference element at end.")
	{
		size_t arr_size(10);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(arr.size() - 1);
		while (arr[index] == arr[index - 1])
			arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("A very large ordered sequence.")
	{
		size_t arr_size(679);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::merge_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Some sequences with a random number of elements.")
	{
		size_t arr_size(156);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}

	SECTION("Some sequences with a random number of elements (but still ordered).")
	{
		size_t arr_size(234);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		dsaa::merge_sort(arr.begin(), arr.end());

		int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

		auto result(dsaa::linear_search(arr.begin(), arr.end(), arr[index]));
		CHECK(result != arr.end());
		CHECK(*result == arr[index]);
	}
}

#include <iostream>
TEST_CASE("Test search_pair_min_max.", "[Search]")
{
	SECTION("An ordinary sequence.")
	{
		size_t arr_size(4);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("The empty sequence.")
	{
		dsaa::DynamicArray<TestObject<int>> arr;
		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(arr.end() == std::get<0>(min_max));
		CHECK(arr.end() == std::get<1>(min_max));
	}

	SECTION("Just one element.")
	{
		dsaa::DynamicArray<TestObject<int>> arr;
		arr.insert_last(TestObject<int>(dsaa::random::random_range_int<int>()));

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("Even number of elements.")
	{
		size_t arr_size(6);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("Odd number of elements.")
	{
		size_t arr_size(7);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("All elements equal.")
	{
		size_t arr_size(8);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());
	
		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("Difference element at begining.")
	{
		size_t arr_size(9);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(0);
		while (arr[index] == arr[index + 1])
			arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("Difference element at end.")
	{
		size_t arr_size(10);

		dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

		int64_t index(arr.size() - 1);
		while (arr[index] == arr[index - 1])
			arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("A very large ordered sequence.")
	{
		size_t arr_size(679);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("Some sequences with a random number of elements.")
	{
		size_t arr_size(156);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}

	SECTION("Some sequences with a random number of elements (but still ordered).")
	{
		size_t arr_size(234);

		dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
		dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

		auto min = std::min_element(arr.begin(), arr.end());
		auto max = std::max_element(arr.begin(), arr.end());

		auto min_max = dsaa::search_pair_min_max(arr.begin(), arr.end());

		CHECK(min == std::get<0>(min_max));
		CHECK(max == std::get<1>(min_max));
	}
}

#endif //!DSAA_TEST_SEARCH_H
