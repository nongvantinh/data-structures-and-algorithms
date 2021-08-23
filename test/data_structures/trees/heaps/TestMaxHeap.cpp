#include "Catch2/Catch.hpp"
#include "MaxHeap.h"
#include "TestObject.h"
#include "Random.h"
#include "Test.h"
#include "Sort.h"

using const_iterator = dsaa::MaxHeap<TestObject<int>>::const_iterator;
using iterator = dsaa::MaxHeap<TestObject<int>>::iterator;
using reserve_iterator = dsaa::MaxHeap<TestObject<int>>::reverse_iterator;

TEST_CASE("Test MaxHeap const_iterator default constructor.", "[MaxHeap]")
{
    const_iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test MaxHeap const_iterator constructor with const_pointer.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);
    SECTION("Iterator at begin")
    {
        const_iterator iter(&arr[0]);
        REQUIRE(&arr[0] == iter.content());
        REQUIRE(arr.cbegin() == iter);
    }
    SECTION("Iterator at end")
    {
        const_iterator iter(&arr.data().data()[num_elem]);
        REQUIRE(&arr.data().data()[num_elem] == iter.content());

        REQUIRE(arr.cend() == iter);
    }
}

TEST_CASE("Test MaxHeap const_iterator copy constructor.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    const_iterator iter2(iter);

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test MaxHeap const_iterator operator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    const_iterator iter2(iter);

    REQUIRE(iter2 == iter);

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

TEST_CASE("Test MaxHeap iterator default constructor.", "[MaxHeap]")
{
    iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test MaxHeap iterator constructor with const_pointer.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);
    SECTION("Iterator at begin")
    {
        iterator iter(&arr[0]);
        REQUIRE(&arr[0] == iter.content());
        REQUIRE(arr.begin() == iter);
    }
    SECTION("Iterator at end")
    {
        iterator iter(&arr.data().data()[num_elem]);
        REQUIRE(&arr.data().data()[num_elem] == iter.content());
        REQUIRE(arr.end() == iter);
    }
}

TEST_CASE("Test MaxHeap iterator copy constructor.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr[0]);
    iterator iter2(iter);
    iterator iter3(iter2);

    REQUIRE(iter2 == iter3);
}

TEST_CASE("Test MaxHeap iterator operator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);

    iterator iter(&arr[0]);
    iterator iter2(iter);

    REQUIRE(iter2 == iter);

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

    TestObject<int> value(dsaa::random::random_range_int<int>());
    *iter = value;
    REQUIRE(value == *iter);
}

TEST_CASE("Test MaxHeap iterator copy assignment.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);

    iterator iter(&arr[0]);
    iterator iter2;

    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test MaxHeap default constructor.", "[MaxHeap]")
{
    dsaa::MaxHeap<TestObject<int>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    REQUIRE(arr.empty());
    REQUIRE(0 == arr.heap_size());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test MaxHeap default constructor and std::allocator.", "[MaxHeap]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::MaxHeap<TestObject<int>> arr(allocator);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    REQUIRE(arr.empty());
    REQUIRE(0 == arr.heap_size());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test MaxHeap constructor with given size.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::MaxHeap<TestObject<int>> arr(num_elem);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == num_elem);

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::MaxHeap<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test MaxHeap constructor with given size and std::allocator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    std::allocator<TestObject<int>> allocator;

    dsaa::MaxHeap<TestObject<int>> arr(num_elem, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == num_elem);

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::MaxHeap<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test MaxHeap constructor with given size and value.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::MaxHeap<TestObject<int>> arr(num_elem, value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == num_elem);

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test MaxHeap constructor with given size, value and std::allocator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    std::allocator<TestObject<int>> allocator;

    dsaa::MaxHeap<TestObject<int>> arr(num_elem, value, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == num_elem);

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test MaxHeap constructor with std::initializer_list.", "[MaxHeap]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::MaxHeap<TestObject<int>> arr(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap constructor with std::initializer_list and std::allocator.", "[MaxHeap]")
{
    std::initializer_list<TestObject<int>> list{50, 96, -20, 4, -54, 39};
    std::allocator<TestObject<int>> allocator;

    dsaa::MaxHeap<TestObject<int>> arr(list, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap constructor with a pair of IIterator.", "[MaxHeap]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::MaxHeap<TestObject<int>> arr(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap constructor with a pair of IIterator and std::allocator.", "[MaxHeap]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    std::allocator<TestObject<int>> allocator;

    dsaa::MaxHeap<TestObject<int>> arr(list.begin(), list.end(), allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap copy constructor.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());
    dsaa::MaxHeap<TestObject<int>> arr2(arr);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(!arr2.empty());
    REQUIRE(arr2.heap_size() == arr.heap_size());
    REQUIRE(arr2.size() == arr.size());

    for (int64_t i(arr2.size() - 1); 0 <= i; --i)
        REQUIRE(arr2.max_heap_property(i));

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test MaxHeap copy constructor and std::allocator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());
    std::allocator<TestObject<int>> allocator;
    dsaa::MaxHeap<TestObject<int>> arr2(arr, allocator);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(!arr2.empty());
    REQUIRE(arr2.heap_size() == arr.heap_size());
    REQUIRE(arr2.size() == arr.size());

    for (int64_t i(arr2.size() - 1); 0 <= i; --i)
        REQUIRE(arr2.max_heap_property(i));

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test MaxHeap move constructor.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());
    dsaa::MaxHeap<TestObject<int>> copy_arr(arr);
    dsaa::MaxHeap<TestObject<int>> arr2(std::move(arr));

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == arr2.heap_size());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.empty());
    REQUIRE(0 == arr.heap_size());
    REQUIRE(0 == arr.size());

    for (int64_t i(arr2.size() - 1); 0 <= i; --i)
        REQUIRE(arr2.max_heap_property(i));

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test MaxHeap move constructor with std::allocator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());
    dsaa::MaxHeap<TestObject<int>> copy_arr(arr);
    dsaa::MaxHeap<TestObject<int>> arr2(std::move(arr));

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == arr2.heap_size());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.empty());
    REQUIRE(0 == arr.heap_size());
    REQUIRE(0 == arr.size());

    for (int64_t i(arr2.size() - 1); 0 <= i; --i)
        REQUIRE(arr2.max_heap_property(i));

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test MaxHeap copy assignment.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());
    dsaa::MaxHeap<TestObject<int>> arr2;

    arr2 = arr;

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(!arr2.empty());
    REQUIRE(arr2.heap_size() == arr.heap_size());
    REQUIRE(arr2.size() == arr.size());

    for (int64_t i(arr2.size() - 1); 0 <= i; --i)
        REQUIRE(arr2.max_heap_property(i));

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test MaxHeap move assigment.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());
    dsaa::MaxHeap<TestObject<int>> copy_arr(arr);
    dsaa::MaxHeap<TestObject<int>> arr2;

    arr2 = std::move(arr);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() != arr2.end());
    REQUIRE(const_iterator() != arr2.cend());

    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == arr2.heap_size());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.empty());
    REQUIRE(0 == arr.heap_size());
    REQUIRE(0 == arr.size());

    for (int64_t i(arr2.size() - 1); 0 <= i; --i)
        REQUIRE(arr2.max_heap_property(i));

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test MaxHeap copy assignment using std::initializer_list.", "[MaxHeap]")
{
    dsaa::MaxHeap<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{100, 90, -79, 100, -87, 77, -5, -37};

    arr = list;

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap assign function using pair IIterator.", "[MaxHeap]")
{
    dsaa::MaxHeap<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{-98, -1, 89, -9, 23, -23, -1, -91, 81, 80, -97};

    arr.assign(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap assign function with size and value.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::MaxHeap<TestObject<int>> arr;

    arr.assign(num_elem, value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == num_elem);

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test MaxHeap assign function using std::initializer_list.", "[MaxHeap]")
{
    dsaa::MaxHeap<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};

    arr.assign(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() != arr.end());
    REQUIRE(const_iterator() != arr.cend());

    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr.heap_size());
    REQUIRE(arr.size() == list.size());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap get_index function.", "[MaxHeap]")
{
    size_t size(99);
    dsaa::MaxHeap<TestObject<int>> arr(size);

    REQUIRE(0 == arr.get_index(arr.begin()));
    REQUIRE(size == arr.get_index(arr.end()));
}

TEST_CASE("Test MaxHeap get_iterator function.", "[MaxHeap]")
{
    size_t size(99);
    dsaa::MaxHeap<TestObject<int>> arr(size);

    REQUIRE(arr.begin() == arr.get_iterator(0));
    REQUIRE(arr.end() == arr.get_iterator(size));
}

TEST_CASE("Test MaxHeap shrink_size function.", "[MaxHeap]")
{
    dsaa::MaxHeap<TestObject<int>> arr(100);

    SECTION("Test MaxHeap shrink_size with value 0.")
    {
        size_t new_size(0);
        arr.shrink_size(new_size);

        REQUIRE(arr.heap_size() == new_size);
    }

    SECTION("Test MaxHeap shrink_size with positive value.")
    {
        size_t new_size(88);
        arr.shrink_size(new_size);

        REQUIRE(arr.heap_size() == new_size);
    }
}

TEST_CASE("Test MaxHeap extract_max function.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    size_t old_size(arr.heap_size());
    auto result = arr.extract_max();

    REQUIRE(arr.heap_size() + 1 == old_size);
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap insert function.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    size_t old_size(arr.heap_size());
    auto result = arr.extract_max();

    TestObject<int> value(dsaa::random::random_range_int<int>(1, 100));

    arr.insert(value);
    REQUIRE(arr.heap_size() == old_size);
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap insert function by moving value.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    size_t old_size(arr.heap_size());
    auto result = arr.extract_max();

    TestObject<int> value(dsaa::random::random_range_int<int>(1, 100));

    arr.insert(std::move(value));
    REQUIRE(arr.heap_size() == old_size);
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap insert function with size and value.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    auto result = arr.extract_max();

    TestObject<int> value(dsaa::random::random_range_int<int>(1, 100));

    arr.insert(num_elem, value);
    REQUIRE(arr.heap_size() == arr.size());
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap insert function with std::initializer_list.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    auto result = arr.extract_max();

    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    arr.insert(list);
    REQUIRE(arr.heap_size() == arr.size());
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap insert function by a pair of iterator.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    auto result = arr.extract_max();

    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    arr.insert(list.begin(), list.end());
    REQUIRE(arr.heap_size() == arr.size());
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap emplace function.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));

    size_t old_size(arr.heap_size());
    auto result = arr.extract_max();

    TestObject<int> value(dsaa::random::random_range_int<int>(1, 100));

    arr.emplace(value);
    REQUIRE(arr.heap_size() == old_size);
    for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
        REQUIRE(arr.max_heap_property(i));
}

TEST_CASE("Test MaxHeap erase_at function.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    SECTION("erase at begining")
    {
        int64_t index(0);

        arr.erase_at(arr.get_iterator(index));

        for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
            REQUIRE(arr.max_heap_property(i));
    }

    SECTION("erase at midle")
    {
        int64_t index(arr.heap_size() / 2);

        arr.erase_at(arr.get_iterator(index));

        for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
            REQUIRE(arr.max_heap_property(i));
    }

    SECTION("erase at last")
    {
        int64_t index(arr.heap_size() - 1);

        arr.erase_at(arr.get_iterator(index));

        for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
            REQUIRE(arr.max_heap_property(i));
    }
}

TEST_CASE("Test MaxHeap erase function.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    SECTION("erase begining to midle")
    {
        int64_t index(arr.size() / 2);

        arr.erase(arr.begin(), arr.get_iterator(index));

        for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
            REQUIRE(arr.max_heap_property(i));
    }

    SECTION("erase midle to end")
    {
        int64_t index(arr.size() / 2);

        arr.erase(arr.get_iterator(index), arr.end());

        for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
            REQUIRE(arr.max_heap_property(i));
    }
    SECTION("erase begining to end")
    {
        int64_t index(0);

        arr.erase(arr.get_iterator(index), arr.end());

        for (int64_t i(arr.heap_size() - 1); 0 <= i; --i)
            REQUIRE(arr.max_heap_property(i));

        REQUIRE(0 == arr.heap_size());

        REQUIRE(iterator() == arr.begin());
        REQUIRE(const_iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(const_iterator() == arr.cend());
    }
}

TEST_CASE("Test MaxHeap clear function.", "[MaxHeap]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::MaxHeap<TestObject<int>> arr(param.begin(), param.end());

    arr.clear();

    REQUIRE(0 == arr.heap_size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}
