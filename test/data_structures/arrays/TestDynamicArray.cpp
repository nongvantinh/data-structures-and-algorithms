#ifndef DSAA_TEST_DYNAMIC_ARRAY_H
#define DSAA_TEST_DYNAMIC_ARRAY_H

#include "Catch2/Catch.hpp"
#include "arrays/DynamicArray.h"
#include "algorithms/Random.h"
#include "test/TestObject.h"

using iterator = dsaa::DynamicArray<TestObject<int>>::iterator;
using const_iterator = dsaa::DynamicArray<TestObject<int>>::const_iterator;
using reserve_iterator = dsaa::DynamicArray<TestObject<int>>::reverse_iterator;

TEST_CASE("Test DynamicArray const_iterator default constructor.", "[DynamicArray]")
{
    const_iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test DynamicArray const_iterator constructor with const_pointer.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);
    SECTION("Iterator at begin")
    {
        const_iterator iter(&arr[0]);
        REQUIRE(&arr[0] == iter.content());
        REQUIRE(arr.cbegin() == iter);
    }
    SECTION("Iterator at end")
    {
        const_iterator iter(&arr.data()[num_elem]);
        REQUIRE(&arr.data()[num_elem] == iter.content());
        REQUIRE(arr.cend() == iter);
    }
}

TEST_CASE("Test DynamicArray const_iterator copy constructor.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    const_iterator iter2(iter);

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test DynamicArray const_iterator copy assignment.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    const_iterator iter2;
    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test DynamicArray const_iterator operator.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    const_iterator iter2(iter);
    const_iterator iter3;

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(++iter == ++iter2);
    REQUIRE(--iter == --iter2);

    REQUIRE(iter++ == iter2++);
    REQUIRE(iter-- == iter2--);

    REQUIRE(arr.begin() + num_elem == arr.end());
    REQUIRE(arr.end() - num_elem == arr.begin());

    REQUIRE((iter += 5) == (iter2 += 5));
    REQUIRE((iter -= 5) == (iter2 -= 5));

    REQUIRE(iter - iter2 == 0);

    REQUIRE(arr.begin() < arr.end());
    REQUIRE(arr.end() > arr.begin());

    REQUIRE(arr.begin() <= arr.begin());
    REQUIRE(arr.begin() >= arr.begin());

    REQUIRE(arr.end() <= arr.end());
    REQUIRE(arr.end() >= arr.end());
}

TEST_CASE("Test DynamicArray iterator default constructor.", "[DynamicArray]")
{
    iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test DynamicArray iterator constructor with const_pointer.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);
    SECTION("Iterator at begin")
    {
        iterator iter(&arr[0]);
        REQUIRE(&arr[0] == iter.content());
        REQUIRE(arr.begin() == iter);
    }
    SECTION("Iterator at end")
    {
        iterator iter(&arr.data()[num_elem]);
        REQUIRE(&arr.data()[num_elem] == iter.content());
        REQUIRE(arr.end() == iter);
    }
}

TEST_CASE("Test DynamicArray iterator copy constructor.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    iterator iter2(iter);
    iterator iter3(iter2);

    REQUIRE(iter2 == iter3);
}

TEST_CASE("Test DynamicArray iterator copy assignment.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    iterator iter(&arr[0]);
    iterator iter2;
    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test DynamicArray iterator operator.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    iterator iter(&arr[0]);
    iterator iter2(iter);
    iterator iter3;

    REQUIRE(iter2 == iter);
    REQUIRE(iter2 != iter3);

    REQUIRE(++iter == ++iter2);
    REQUIRE(--iter == --iter2);

    REQUIRE(iter++ == iter2++);
    REQUIRE(iter-- == iter2--);

    REQUIRE(arr.begin() + num_elem == arr.end());
    REQUIRE(arr.end() - num_elem == arr.begin());

    REQUIRE((iter += 5) == (iter2 += 5));
    REQUIRE((iter -= 5) == (iter2 -= 5));

    REQUIRE(iter - iter2 == 0);

    REQUIRE(arr.begin() < arr.end());
    REQUIRE(arr.end() > arr.begin());

    REQUIRE(arr.begin() <= arr.begin());
    REQUIRE(arr.begin() >= arr.begin());

    REQUIRE(arr.end() <= arr.end());
    REQUIRE(arr.end() >= arr.end());

    *iter = TestObject<int>(555);
    REQUIRE(TestObject<int>(555) == *iter);
}

TEST_CASE("Test DynamicArray default constructor.", "[DynamicArray]")
{
    dsaa::DynamicArray<TestObject<int>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() == arr.data());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.capacity());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DynamicArray default constructor and std::allocator.", "[DynamicArray]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::DynamicArray<TestObject<int>> arr(allocator);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() == arr.data());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.capacity());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DynamicArray constructor with given size.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DynamicArray<TestObject<int>> arr(num_elem);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::DynamicArray<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test DynamicArray constructor with given size and std::allocator.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    std::allocator<TestObject<int>> allocator;

    dsaa::DynamicArray<TestObject<int>> arr(num_elem, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::DynamicArray<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test DynamicArray constructor with given size and value.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::DynamicArray<TestObject<int>> arr(num_elem, value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test DynamicArray constructor with given size, value and std::allocator.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    std::allocator<TestObject<int>> allocator;

    dsaa::DynamicArray<TestObject<int>> arr(num_elem, value, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test DynamicArray constructor with std::initializer_list.", "[DynamicArray]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::DynamicArray<TestObject<int>> arr(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray constructor with std::initializer_list and std::allocator.", "[DynamicArray]")
{
    std::initializer_list<TestObject<int>> list{50, 96, -20, 4, -54, 39};
    std::allocator<TestObject<int>> allocator;

    dsaa::DynamicArray<TestObject<int>> arr(list, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray constructor with a pair of IIterator.", "[DynamicArray]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::DynamicArray<TestObject<int>> arr(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray constructor with a pair of IIterator and std::allocator.", "[DynamicArray]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    std::allocator<TestObject<int>> allocator;

    dsaa::DynamicArray<TestObject<int>> arr(list.begin(), list.end(), allocator);
    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray copy constructor.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> arr2(arr);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr2.data());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() <= arr2.capacity());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test DynamicArray copy constructor and std::allocator.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    std::allocator<TestObject<int>> allocator;
    dsaa::DynamicArray<TestObject<int>> arr2(arr, allocator);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr2.data());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() <= arr2.capacity());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test DynamicArray move constructor.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> copy_arr(arr);
    dsaa::DynamicArray<TestObject<int>> arr2(std::move(arr));

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr2.data());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() <= arr2.capacity());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() == arr.data());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.capacity());
    REQUIRE(0 == arr.size());

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test DynamicArray move constructor with std::allocator.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> copy_arr(arr);
    dsaa::DynamicArray<TestObject<int>> arr2(std::move(arr));

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr2.data());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() <= arr2.capacity());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() == arr.data());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.capacity());
    REQUIRE(0 == arr.size());

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test DynamicArray copy assignment.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> arr2;

    arr2 = arr;

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr2.data());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() <= arr2.capacity());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test DynamicArray move assigment.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> copy_arr(arr);
    dsaa::DynamicArray<TestObject<int>> arr2;

    arr2 = std::move(arr);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr2.data());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() <= arr2.capacity());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() == arr.data());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.capacity());
    REQUIRE(0 == arr.size());

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test DynamicArray copy assignment using std::initializer_list.", "[DynamicArray]")
{
    dsaa::DynamicArray<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{100, 90, -79, 100, -87, 77, -5, -37};

    arr = list;

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray assign function using pair IIterator.", "[DynamicArray]")
{
    dsaa::DynamicArray<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{-98, -1, 89, -9, 23, -23, -1, -91, 81, 80, -97};

    arr.assign(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray assign function with size and value.", "[DynamicArray]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::DynamicArray<TestObject<int>> arr;

    arr.assign(num_elem, value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test DynamicArray assign function using std::initializer_list.", "[DynamicArray]")
{
    dsaa::DynamicArray<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};

    arr.assign(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(iterator().content() != arr.data());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() <= arr.capacity());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray get_index function.", "[DynamicArray]")
{
    size_t size(99);
    dsaa::DynamicArray<TestObject<int>> arr(size);

    REQUIRE(0 == arr.get_index(arr.begin()));
    REQUIRE(size == arr.get_index(arr.end()));
}

TEST_CASE("Test DynamicArray get_iterator function.", "[DynamicArray]")
{
    size_t size(99);
    dsaa::DynamicArray<TestObject<int>> arr(size);

    REQUIRE(arr.begin() == arr.get_iterator(0));
    REQUIRE(arr.end() == arr.get_iterator(size));
}

TEST_CASE("Test DynamicArray reserve function.", "[DynamicArray]")
{
    dsaa::DynamicArray<TestObject<int>> arr;

    SECTION("Test DynamicArray reserve with value 0.")
    {
        size_t old_capacity(arr.capacity());
        size_t old_size(arr.size());

        int64_t new_capacity(0);

        arr.reserve(new_capacity);

        REQUIRE(arr.capacity() == old_capacity);
        REQUIRE(arr.size() == old_size);
    }

    SECTION("Test DynamicArray reserve with positive value.")
    {
        size_t new_capacity(99);
        size_t old_size(arr.size());

        arr.reserve(new_capacity);

        REQUIRE(arr.capacity() == new_capacity);
        REQUIRE(arr.size() == old_size);
    }

    SECTION("Test DynamicArray reserve with very large positive value.")
    {
        size_t new_capacity(999999);
        size_t old_size(arr.size());
        arr.reserve(new_capacity);

        REQUIRE(arr.capacity() == new_capacity);
        REQUIRE(arr.size() == old_size);
    }
}

TEST_CASE("Test DynamicArray resize function.", "[DynamicArray]")
{
    dsaa::DynamicArray<TestObject<int>> arr;

    SECTION("Test DynamicArray resize with value 0.")
    {
        size_t old_capacity(arr.capacity());
        size_t new_size(0);
        arr.resize(new_size);

        REQUIRE(old_capacity <= arr.capacity());
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Test DynamicArray resize with positive value.")
    {
        size_t old_capacity(arr.capacity());
        size_t new_size(88);
        arr.resize(new_size);

        REQUIRE(old_capacity <= arr.capacity());
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Test DynamicArray resize with very large positive value.")
    {
        size_t old_capacity(arr.capacity());
        size_t new_size(999999);
        arr.resize(new_size);

        REQUIRE(old_capacity <= arr.capacity());
        REQUIRE(arr.size() == new_size);
    }
}

TEST_CASE("Test DynamicArray insert_last with parameter value.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());

    size_t old_cacity(arr.capacity());
    size_t index(arr.size());

    arr.insert_last(value);

    REQUIRE(arr.size() == param.size() + 1);
    REQUIRE(old_cacity <= arr.capacity());

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == value);
}

TEST_CASE("Test DynamicArray insert_last by move value.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());
    TestObject<int> copy_of_value(value);

    size_t old_cacity(arr.capacity());
    size_t index(arr.size());

    arr.insert_last(std::move(value));

    REQUIRE(arr.size() == param.size() + 1);
    REQUIRE(old_cacity <= arr.capacity());

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == copy_of_value);
}

TEST_CASE("Test DynamicArray insert_last by a mount of size and value.", "[DynamicArray]")
{
    size_t arr_size(11);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());

    size_t old_cacity(arr.capacity());
    size_t index(arr.size());

    arr.insert_last(num_elem, value);

    REQUIRE(arr.size() == param.size() + num_elem);
    REQUIRE(old_cacity <= arr.capacity());

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    for (size_t i(0); num_elem != i; ++i, ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test DynamicArray insert_last by std::initializer_list.", "[DynamicArray]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{-84, 85, -17, -31, -43, -99, 3};

    size_t old_cacity(arr.capacity());
    size_t index(arr.size());

    arr.insert_last(list);

    REQUIRE(arr.size() == copy_arr.size() + list.size());
    REQUIRE(old_cacity <= arr.capacity());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());
    auto copy_arr_end(copy_arr.get_iterator(index));
    for (; copy_arr_end != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);

    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray insert_last by a pair of IIterator.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DynamicArray<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{44, 20, -32, 35, -85, -99, -39};

    size_t old_cacity(arr.capacity());
    size_t index(arr.size());

    arr.insert_last(list.begin(), list.end());

    REQUIRE(arr.size() == copy_arr.size() + list.size());
    REQUIRE(old_cacity <= arr.capacity());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());
    auto copy_arr_end(copy_arr.get_iterator(index));
    for (; copy_arr_end != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);

    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test DynamicArray emplace_last using parameter pack.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());

    size_t old_cacity(arr.capacity());
    size_t index(arr.size());

    arr.emplace_last(value);

    REQUIRE(arr.size() == param.size() + 1);
    REQUIRE(old_cacity <= arr.capacity());

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == value);
}

TEST_CASE("Test DynamicArray insert_at with one parameter's value.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray insert_at the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(0);

        arr.insert_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size() / 2);

        arr.insert_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.insert_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(dsaa::random::random_range_int<int>(0, arr.size()));

        arr.insert_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray insert_at by move a value.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray insert_at the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t old_cacity(arr.capacity());
        size_t index(0);

        arr.insert_at(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t old_cacity(arr.capacity());
        size_t index(arr.size() / 2);

        arr.insert_at(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.insert_at(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t old_cacity(arr.capacity());
        size_t index(dsaa::random::random_range_int<int>(0, arr.size()));

        arr.insert_at(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray insert_at by a mount of size's value.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray insert_at the begining position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(0);

        arr.insert_at(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at midle position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size() / 2);

        arr.insert_at(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at end position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.insert_at(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at random position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.insert_at(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray insert_at by a std::initializer_list.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray insert_at the begining position.")
    {
        std::initializer_list<TestObject<int>> list{-60, -92, 2, 30, 51, -97, 97, 66};

        size_t old_cacity(arr.capacity());
        size_t index(0);

        arr.insert_at(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at midle position.")
    {
        std::initializer_list<TestObject<int>> list{-6, 96, 32, 48, -61, -13};

        size_t old_cacity(arr.capacity());
        size_t index(arr.size() / 2);

        arr.insert_at(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at end position.")
    {
        std::initializer_list<TestObject<int>> list{82, -39, 33, 0, 84, 0, 61, 57, -37, 38, -43, -100};

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.insert_at(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at random position.")
    {
        std::initializer_list<TestObject<int>> list{8, 61, -76, 89, 35, 68, -59, -1, 81, 40};

        size_t old_cacity(arr.capacity());
        size_t index(dsaa::random::random_range_int<int>(0, arr.size()));

        arr.insert_at(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray insert_at by a pair of IIterator.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray insert_at the begining position.")
    {
        std::initializer_list<TestObject<int>> list{-60, -92, 2, 30, 51, -97, 97, 66};

        size_t old_cacity(arr.capacity());
        size_t index(0);

        arr.insert_at(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at midle position.")
    {
        std::initializer_list<TestObject<int>> list{-6, 96, 32, 48, -61, -13};

        size_t old_cacity(arr.capacity());
        size_t index(arr.size() / 2);

        arr.insert_at(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at end position.")
    {
        std::initializer_list<TestObject<int>> list{82, -39, 33, 0, 84, 0, 61, 57, -37, 38, -43, -100};

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.insert_at(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray insert_at random position.")
    {
        std::initializer_list<TestObject<int>> list{8, 61, -76, 89, 35, 68, -59, -1, 81, 40};

        size_t old_cacity(arr.capacity());
        size_t index(dsaa::random::random_range_int<int>(0, arr.size()));

        arr.insert_at(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray emplace_at using parameter pack.", "[DynamicArray]")
{
    size_t arr_size(dsaa::random::random_range_int<int>(10, 20));
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray emplace_at the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(0);

        arr.emplace_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray emplace_at midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size() / 2);

        arr.emplace_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray emplace_at end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(arr.size());

        arr.emplace_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray emplace_at random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t old_cacity(arr.capacity());
        size_t index(dsaa::random::random_range_int<int>(0, arr.size()));

        arr.emplace_at(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);
        REQUIRE(old_cacity <= arr.capacity());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray erase_at function.", "[DynamicArray]")
{
    size_t arr_size(42);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray erase_at the begining position.")
    {
        int64_t index(0);

        arr.erase_at(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray erase_at midle position.")
    {
        int64_t index(arr.size() / 2);

        arr.erase_at(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray erase_at last position.")
    {
        int64_t index(arr.size() - 1);
        arr.erase_at(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray erase_at random position.")
    {
        int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.erase_at(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray erase function with a pair of IIterator.", "[DynamicArray]")
{
    size_t arr_size(122);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DynamicArray erase from begining to the end.")
    {
        size_t capacity(arr.capacity());

        arr.erase(arr.begin(), arr.end());

        REQUIRE(arr.capacity() == capacity);
        REQUIRE(arr.empty());
        REQUIRE(0 == arr.size());

        REQUIRE(iterator() == arr.begin());
        REQUIRE(const_iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(const_iterator() == arr.cend());
    }

    SECTION("Test DynamicArray erase from begining to midle.")
    {
        size_t index(arr.size() / 2);

        arr.erase(arr.begin(), arr.get_iterator(index));

        REQUIRE(arr.size() + index == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.get_iterator(index));
        for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DynamicArray erase from midle to the end.")
    {
        size_t index(arr.size() / 2);

        arr.erase(arr.get_iterator(index), arr.end());

        REQUIRE(arr.size() + index == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DynamicArray erase_last function.", "[DynamicArray]")
{
    size_t arr_size(122);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    size_t capacity(arr.capacity());

    arr.erase_last();

    REQUIRE(arr.capacity() == capacity);
    REQUIRE(!arr.empty());
    REQUIRE(arr_size - 1 == arr.size());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());
}

TEST_CASE("Test DynamicArray clear function.", "[DynamicArray]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DynamicArray<TestObject<int>> arr(param.begin(), param.end());

    size_t capacity(arr.capacity());
    arr.clear();
    REQUIRE(arr.capacity() == capacity);
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}

#endif // !DSAA_TEST_DYNAMIC_ARRAY_H