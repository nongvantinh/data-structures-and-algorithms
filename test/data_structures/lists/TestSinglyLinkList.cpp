#include "Catch2/Catch.hpp"
#include "lists/SinglyLinkList.h"
#include "algorithms/Random.h"
#include "test/TestObject.h"
#include "arrays/DynamicArray.h"

using iterator = dsaa::SinglyLinkList<TestObject<int>>::iterator;
using const_iterator = dsaa::SinglyLinkList<TestObject<int>>::const_iterator;

TEST_CASE("Test SinglyLinkList default constructor.", "[SinglyLinkList]")
{
    dsaa::SinglyLinkList<TestObject<int>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test SinglyLinkList default constructor and std::allocator.", "[SinglyLinkList]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::SinglyLinkList<TestObject<int>> arr(allocator);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test SinglyLinkList constructor with given size.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::SinglyLinkList<TestObject<int>> arr(num_elem);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::SinglyLinkList<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test SinglyLinkList constructor with given size and std::allocator.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    std::allocator<TestObject<int>> allocator;

    dsaa::SinglyLinkList<TestObject<int>> arr(num_elem, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::SinglyLinkList<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test SinglyLinkList constructor with given size and value.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::SinglyLinkList<TestObject<int>> arr(num_elem, value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test SinglyLinkList constructor with given size, value and std::allocator.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    std::allocator<TestObject<int>> allocator;

    dsaa::SinglyLinkList<TestObject<int>> arr(num_elem, value, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test SinglyLinkList constructor with std::initializer_list.", "[SinglyLinkList]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::SinglyLinkList<TestObject<int>> arr(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList constructor with std::initializer_list and std::allocator.", "[SinglyLinkList]")
{
    std::initializer_list<TestObject<int>> list{50, 96, -20, 4, -54, 39};
    std::allocator<TestObject<int>> allocator;

    dsaa::SinglyLinkList<TestObject<int>> arr(list, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList constructor with a pair of IIterator.", "[SinglyLinkList]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::SinglyLinkList<TestObject<int>> arr(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList constructor with a pair of IIterator and std::allocator.", "[SinglyLinkList]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    std::allocator<TestObject<int>> allocator;

    dsaa::SinglyLinkList<TestObject<int>> arr(list.begin(), list.end(), allocator);
    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList copy constructor.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> arr2(arr);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(const_iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test SinglyLinkList copy constructor and std::allocator.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    std::allocator<TestObject<int>> allocator;
    dsaa::SinglyLinkList<TestObject<int>> arr2(arr, allocator);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(const_iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == allocator);
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test SinglyLinkList move constructor.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);
    dsaa::SinglyLinkList<TestObject<int>> arr2(std::move(arr));

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(const_iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test SinglyLinkList move constructor with std::allocator.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);
    dsaa::SinglyLinkList<TestObject<int>> arr2(std::move(arr));

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(const_iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test SinglyLinkList copy assignment.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> arr2;

    arr2 = arr;

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(const_iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test SinglyLinkList move assigment.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);
    dsaa::SinglyLinkList<TestObject<int>> arr2;

    arr2 = std::move(arr);

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(const_iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(const_iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == copy_arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    auto arr_iter(copy_arr.begin());
    auto arr2_iter(arr2.begin());
    for (; copy_arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test SinglyLinkList copy assignment using std::initializer_list.", "[SinglyLinkList]")
{
    dsaa::SinglyLinkList<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{100, 90, -79, 100, -87, 77, -5, -37};

    arr = list;

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList assign function using pair IIterator.", "[SinglyLinkList]")
{
    dsaa::SinglyLinkList<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{-98, -1, 89, -9, 23, -23, -1, -91, 81, 80, -97};

    arr.assign(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList assign function with size and value.", "[SinglyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::SinglyLinkList<TestObject<int>> arr;

    arr.assign(num_elem, value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test SinglyLinkList assign function using std::initializer_list.", "[SinglyLinkList]")
{
    dsaa::SinglyLinkList<TestObject<int>> arr;
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};

    arr.assign(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.begin());
    for (; list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList get_index function.", "[SinglyLinkList]")
{
    size_t size(99);
    dsaa::SinglyLinkList<TestObject<int>> arr(size);

    REQUIRE(0 == arr.get_index(arr.begin()));
    REQUIRE(size == arr.get_index(arr.end()));
}

TEST_CASE("Test SinglyLinkList get_iterator function.", "[SinglyLinkList]")
{
    size_t size(99);
    dsaa::SinglyLinkList<TestObject<int>> arr(size);

    REQUIRE(arr.begin() == arr.get_iterator(0));
    REQUIRE(arr.end() == arr.get_iterator(size));
}

TEST_CASE("Test SinglyLinkList resize function.", "[SinglyLinkList]")
{
    dsaa::SinglyLinkList<TestObject<int>> arr;

    SECTION("Test SinglyLinkList resize with value 0.")
    {

        size_t new_size(0);
        arr.resize(new_size);
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Test SinglyLinkList resize with positive value.")
    {
        size_t new_size(88);
        arr.resize(new_size);
        REQUIRE(arr.size() == new_size);
    }
}

TEST_CASE("Test SinglyLinkList insert_first with parameter value.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.insert_first(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    REQUIRE(*arr_iter == value);
    ++arr_iter;

    for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test SinglyLinkList insert_first by move value.", "[SinglyLinkList]")
{
    size_t arr_size(13);

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());
    TestObject<int> copy_of_value(value);

    arr.insert_first(std::move(value));

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    REQUIRE(*arr_iter == copy_of_value);
    ++arr_iter;

    for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test SinglyLinkList insert_first by a mount of size and value.", "[SinglyLinkList]")
{
    size_t arr_size(11);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.insert_first(num_elem, value);

    REQUIRE(arr.size() == param.size() + num_elem);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    for (size_t i(0); num_elem != i; ++i, ++arr_iter)
        REQUIRE(*arr_iter == value);

    for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test SinglyLinkList insert_first by std::initializer_list.", "[SinglyLinkList]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{-84, 85, -17, -31, -43, -99, 3};

    arr.insert_first(list);

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);

    auto copy_arr_iter(copy_arr.begin());
    auto copy_arr_end(copy_arr.end());
    for (; copy_arr_end != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList insert_first by a pair of IIterator.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{44, 20, -32, 35, -85, -99, -39};

    arr.insert_first(list.begin(), list.end());

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);

    auto copy_arr_iter(copy_arr.begin());
    auto copy_arr_end(copy_arr.end());
    for (; copy_arr_end != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList emplace_first using parameter pack.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.emplace_first(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    REQUIRE(*arr_iter == value);
    ++arr_iter;

    for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test SinglyLinkList insert_last with parameter value.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());

    size_t index(arr.size());

    arr.insert_last(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == value);
}

TEST_CASE("Test SinglyLinkList insert_last by move value.", "[SinglyLinkList]")
{
    size_t arr_size(13);

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());
    TestObject<int> copy_of_value(value);

    size_t index(arr.size());

    arr.insert_last(std::move(value));

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == copy_of_value);
}

TEST_CASE("Test SinglyLinkList insert_last by a mount of size and value.", "[SinglyLinkList]")
{
    size_t arr_size(11);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());

    size_t index(arr.size());

    arr.insert_last(num_elem, value);

    REQUIRE(arr.size() == param.size() + num_elem);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    for (size_t i(0); num_elem != i; ++i, ++arr_iter)
        REQUIRE(*arr_iter == value);
}

TEST_CASE("Test SinglyLinkList insert_last by std::initializer_list.", "[SinglyLinkList]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{-84, 85, -17, -31, -43, -99, 3};

    size_t index(arr.size());

    arr.insert_last(list);

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());
    auto copy_arr_end(copy_arr.get_iterator(index));
    for (; copy_arr_end != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);

    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList insert_last by a pair of IIterator.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::SinglyLinkList<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{44, 20, -32, 35, -85, -99, -39};

    size_t index(arr.size());

    arr.insert_last(list.begin(), list.end());

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());
    auto copy_arr_end(copy_arr.get_iterator(index));
    for (; copy_arr_end != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);

    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test SinglyLinkList emplace_last using parameter pack.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());

    size_t index(arr.size());

    arr.emplace_last(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    for (auto arr_end(arr.get_iterator(index)); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == value);
}

TEST_CASE("Test SinglyLinkList insert_after with one parameter's value.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test SinglyLinkList insert_after the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(0);

        arr.insert_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() / 2);

        arr.insert_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after last position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() - 1);

        arr.insert_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test SinglyLinkList insert_after by move a value.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test SinglyLinkList insert_after the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(0);

        arr.insert_after(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(arr.size() / 2);

        arr.insert_after(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(arr.size() - 1);

        arr.insert_after(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_after(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == copy_of_value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test SinglyLinkList insert_after by a mount of size's value.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test SinglyLinkList insert_after the begining position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(0);

        arr.insert_after(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after midle position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() / 2);

        arr.insert_after(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after end position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() - 1);

        arr.insert_after(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after random position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_after(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (size_t i(0); num_elem != i; ++i, ++arr_iter)
            REQUIRE(*arr_iter == value);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test SinglyLinkList insert_after by a std::initializer_list.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test SinglyLinkList insert_after the begining position.")
    {
        std::initializer_list<TestObject<int>> list{-60, -92, 2, 30, 51, -97, 97, 66};

        size_t index(0);

        arr.insert_after(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after midle position.")
    {
        std::initializer_list<TestObject<int>> list{-6, 96, 32, 48, -61, -13};

        size_t index(arr.size() / 2);

        arr.insert_after(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after end position.")
    {
        std::initializer_list<TestObject<int>> list{82, -39, 33, 0, 84, 0, 61, 57, -37, 38, -43, -100};

        size_t index(arr.size() - 1);

        arr.insert_after(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after random position.")
    {
        std::initializer_list<TestObject<int>> list{8, 61, -76, 89, 35, 68, -59, -1, 81, 40};

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_after(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test SinglyLinkList insert_after by a pair of IIterator.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test SinglyLinkList insert_after the begining position.")
    {
        std::initializer_list<TestObject<int>> list{-60, -92, 2, 30, 51, -97, 97, 66};

        size_t index(0);

        arr.insert_after(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after midle position.")
    {
        std::initializer_list<TestObject<int>> list{-6, 96, 32, 48, -61, -13};

        size_t index(arr.size() / 2);

        arr.insert_after(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after end position.")
    {
        std::initializer_list<TestObject<int>> list{82, -39, 33, 0, 84, 0, 61, 57, -37, 38, -43, -100};

        size_t index(arr.size() - 1);

        arr.insert_after(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList insert_after random position.")
    {
        std::initializer_list<TestObject<int>> list{8, 61, -76, 89, 35, 68, -59, -1, 81, 40};

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_after(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
            REQUIRE(*arr_iter == *list_iter);

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test SinglyLinkList emplace_after using parameter pack.", "[SinglyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test SinglyLinkList emplace_after the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(0);

        arr.emplace_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList emplace_after midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() / 2);

        arr.emplace_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList emplace_after end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() - 1);

        arr.emplace_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test SinglyLinkList emplace_after random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.emplace_after(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        for (auto arr_end(arr.get_iterator(index + 1)); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        REQUIRE(*arr_iter == value);
        ++arr_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test SinglyLinkList clean function.", "[SinglyLinkList]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::SinglyLinkList<TestObject<int>> arr(param.begin(), param.end());

    arr.clean();
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}