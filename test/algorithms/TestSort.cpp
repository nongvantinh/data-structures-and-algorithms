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

TEST_CASE("Test sort_heap.", "[Sort]")
{
    SECTION("Test sort_heap using std::less_equal as comparer.")
    {
        SECTION("An ordinary sequence.")
        {
            size_t arr_size(4);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("The empty sequence.")
        {
            dsaa::DynamicArray<TestObject<int>> arr;

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("Just one element.")
        {
            size_t arr_size(1);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("Even number of elements.")
        {
            size_t arr_size(6);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("Odd number of elements.")
        {
            size_t arr_size(7);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("All elements equal.")
        {
            size_t arr_size(8);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("Difference element at begining.")
        {
            size_t arr_size(9);

            dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

            int64_t index(0);
            while (arr[index] == arr[index + 1])
                arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("Difference element at end.")
        {
            size_t arr_size(10);

            dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

            int64_t index(arr.size() - 1);
            while (arr[index] == arr[index - 1])
                arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("A very large sequence.")
        {
            size_t arr_size(679);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }

        SECTION("Some sequences with a random number of elements.")
        {
            size_t arr_size(51);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end());
            dsaa::sort_heap(arr.begin(), arr.end());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
        }
    }

    SECTION("Test sort_heap using std::greater_equal as comparer.")
    {
        SECTION("An ordinary sequence.")
        {
            size_t arr_size(4);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("The empty sequence.")
        {
            dsaa::DynamicArray<TestObject<int>> arr;

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("Just one element.")
        {
            size_t arr_size(1);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("Even number of elements.")
        {
            size_t arr_size(6);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("Odd number of elements.")
        {
            size_t arr_size(7);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("All elements equal.")
        {
            size_t arr_size(8);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("Difference element at begining.")
        {
            size_t arr_size(9);

            dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

            int64_t index(0);
            while (arr[index] == arr[index + 1])
                arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("Difference element at end.")
        {
            size_t arr_size(10);

            dsaa::DynamicArray<TestObject<int>> arr(arr_size, TestObject<int>(dsaa::random::random_range_int<int>()));

            int64_t index(arr.size() - 1);
            while (arr[index] == arr[index - 1])
                arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("A very large sequence.")
        {
            size_t arr_size(679);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }

        SECTION("Some sequences with a random number of elements.")
        {
            size_t arr_size(51);

            dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
            dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

            dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());
            dsaa::sort_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

            REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>()));
        }
    }
}

#include "Test.h"

TEST_CASE("Test lomuto_quick_sort.", "[Sort]")
{
    SECTION("An ordinary sequence.")
    {
        size_t arr_size(4);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("The empty sequence.")
    {
        dsaa::DynamicArray<TestObject<int>> arr;

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Just one element.")
    {
        size_t arr_size(1);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Even number of elements.")
    {
        size_t arr_size(6);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Odd number of elements.")
    {
        size_t arr_size(7);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("All elements equal.")
    {
        size_t arr_size(8);

        TestObject<int> value(dsaa::random::random_range_int<int>());
        dsaa::DynamicArray<TestObject<int>> arr(arr_size, value);

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at begining.")
    {
        size_t arr_size(9);

        TestObject<int> value(dsaa::random::random_range_int<int>());
        dsaa::DynamicArray<TestObject<int>> arr(arr_size, value);

        int64_t index(0);
        while (arr[index] == arr[index + 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Difference element at end.")
    {
        size_t arr_size(10);

        TestObject<int> value(dsaa::random::random_range_int<int>());
        dsaa::DynamicArray<TestObject<int>> arr(arr_size, value);

        int64_t index(arr.size() - 1);
        while (arr[index] == arr[index - 1])
            arr[index] = TestObject<int>(dsaa::random::random_range_int<int>());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("A very large sequence.")
    {
        size_t arr_size(679);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }

    SECTION("Some sequences with a random number of elements.")
    {
        size_t arr_size(51);

        dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
        dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

        dsaa::lomuto_quick_sort(arr.begin(), arr.end());

        REQUIRE(dsaa::is_sorted(arr.begin(), arr.end(), std::less_equal<TestObject<int>>()));
    }
}

#include "MinHeap.h"
TEST_CASE("Test dsaa::heap_property for dsaa::MinHeap.", "[dsaa::heap_property]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::MinHeap<TestObject<int>> arr(list.begin(), list.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(dsaa::heap_property(arr.begin(), arr.end(), arr.get_iterator(i), std::less_equal<TestObject<int>>()));
}

TEST_CASE("Test dsaa::build_heap to build min heap using dsaa::DynamicArray.", "[dsaa::build_heap]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    dsaa::build_heap(arr.begin(), arr.end(), std::less_equal<TestObject<int>>());

    for (int64_t i(arr.size() - 1); 0 <= i; --i)
        REQUIRE(dsaa::heap_property(arr.begin(), arr.end(), arr.get_iterator(i), std::less_equal<TestObject<int>>()));
}

#include "MaxHeap.h"
TEST_CASE("Test dsaa::heap_property dsaa::MaxHeap.", "[dsaa::heap_property]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::MaxHeap<TestObject<int>> arr(list.begin(), list.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(dsaa::heap_property(arr.begin(), arr.end(), arr.get_iterator(i), std::greater_equal<TestObject<int>>()));
}

TEST_CASE("Test dsaa::build_heap to build max heap using dsaa::DynamicArray.", "[dsaa::build_heap]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    dsaa::build_heap(arr.begin(), arr.end(), std::greater_equal<TestObject<int>>());

    for (int64_t i(arr.size() - 1); 0 <= i; --i)
        REQUIRE(dsaa::heap_property(arr.begin(), arr.end(), arr.get_iterator(i), std::greater_equal<TestObject<int>>()));
}

#endif //!DSAA_TEST_SORT_H
