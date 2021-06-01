#ifndef DSAA_TEST_SORT_H
#define DSAA_TEST_SORT_H

#include "Catch2/Catch.hpp"
#include "algorithms/Sort.h"
#include "arrays/DynamicArray.h"
#include "algorithms/Random.h"
#include "test/TestObject.h"

TEST_CASE("Test buble_sort.", "[Sort]")
{
    SECTION("An ordinary sequence.")
    {
        size_t arr_size(4);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("The empty sequence.")
    {
        dsaa::DynamicArray<TestObject<int>> arr;

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Just one element.")
    {
        size_t arr_size(1);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Even number of elements.")
    {
        size_t arr_size(6);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Odd number of elements.")
    {
        size_t arr_size(7);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("All elements equal.")
    {
        size_t arr_size(8);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at begining.")
    {
        size_t arr_size(9);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(0);
        while (arr[index] == arr[index + 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at end.")
    {
        size_t arr_size(10);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(arr.size() - 1);
        while (arr[index] == arr[index - 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("A very large sequence.")
    {
        size_t arr_size(679);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Some sequences with a random number of elements.")
    {
        size_t arr_size(51);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::buble_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }
}

TEST_CASE("Test selection_sort.", "[Sort]")
{
    SECTION("An ordinary sequence.")
    {
        size_t arr_size(4);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("The empty sequence.")
    {
        dsaa::DynamicArray<TestObject<int>> arr;

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Just one element.")
    {
        size_t arr_size(1);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Even number of elements.")
    {
        size_t arr_size(6);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Odd number of elements.")
    {
        size_t arr_size(7);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("All elements equal.")
    {
        size_t arr_size(8);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at begining.")
    {
        size_t arr_size(9);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(0);
        while (arr[index] == arr[index + 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at end.")
    {
        size_t arr_size(10);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(arr.size() - 1);
        while (arr[index] == arr[index - 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("A very large sequence.")
    {
        size_t arr_size(679);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Some sequences with a random number of elements.")
    {
        size_t arr_size(51);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::selection_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }
}

TEST_CASE("Test insertion_sort.", "[Sort]")
{
    SECTION("An ordinary sequence.")
    {
        size_t arr_size(4);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("The empty sequence.")
    {
        dsaa::DynamicArray<TestObject<int>> arr;

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Just one element.")
    {
        size_t arr_size(1);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Even number of elements.")
    {
        size_t arr_size(6);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Odd number of elements.")
    {
        size_t arr_size(7);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("All elements equal.")
    {
        size_t arr_size(8);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at begining.")
    {
        size_t arr_size(9);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(0);
        while (arr[index] == arr[index + 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at end.")
    {
        size_t arr_size(10);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(arr.size() - 1);
        while (arr[index] == arr[index - 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("A very large sequence.")
    {
        size_t arr_size(679);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Some sequences with a random number of elements.")
    {
        size_t arr_size(51);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::insertion_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }
}

TEST_CASE("Test merge_sort.", "[Sort]")
{
    SECTION("An ordinary sequence.")
    {
        size_t arr_size(4);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("The empty sequence.")
    {
        dsaa::DynamicArray<TestObject<int>> arr;

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Just one element.")
    {
        size_t arr_size(1);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Even number of elements.")
    {
        size_t arr_size(6);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Odd number of elements.")
    {
        size_t arr_size(7);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("All elements equal.")
    {
        size_t arr_size(8);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at begining.")
    {
        size_t arr_size(9);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(0);
        while (arr[index] == arr[index + 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at end.")
    {
        size_t arr_size(10);

        dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

        int64_t index(arr.size() - 1);
        while (arr[index] == arr[index - 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("A very large sequence.")
    {
        size_t arr_size(679);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Some sequences with a random number of elements.")
    {
        size_t arr_size(51);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::merge_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }
}

#endif //!DSAA_TEST_SORT_H
