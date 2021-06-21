#include "Catch2/Catch.hpp"
#include "Queue.h"
#include "Random.h"
#include "TestObject.h"
#include "DynamicArray.h"

using iterator = dsaa::Queue<TestObject<int>>::iterator;
using const_iterator = dsaa::Queue<TestObject<int>>::const_iterator;

TEST_CASE("Test Queue QueueNode default constructor.", "[Queue]")
{
    dsaa::QueueNode<TestObject<int>> node;

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Queue QueueNode constructor with value.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::QueueNode<TestObject<int>> node(value);

    REQUIRE(value == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Queue QueueNode constructor by moving a value.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::QueueNode<TestObject<int>> node(std::move(value));

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Queue QueueNode constructor with value, next.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});

    dsaa::QueueNode<TestObject<int>> node(value, &arr.peek());

    REQUIRE(value == node.value());
    REQUIRE(&arr.peek() == node.next());
}

TEST_CASE("Test Queue QueueNode constructor by move a value, next.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});
    dsaa::QueueNode<TestObject<int>> node(std::move(value), &arr.peek());

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(&arr.peek() == node.next());
}

TEST_CASE("Test Queue QueueNode copy constructor.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});

    dsaa::QueueNode<TestObject<int>> node(value, &arr.peek());
    dsaa::QueueNode<TestObject<int>> node1(node);

    REQUIRE(value == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node == node1);
}

TEST_CASE("Test Queue QueueNode move constructor.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});

    dsaa::QueueNode<TestObject<int>> node(value, &arr.peek());
    dsaa::QueueNode<TestObject<int>> node1(std::move(node));

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node != node1);

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Queue QueueNode copy assignment.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});

    dsaa::QueueNode<TestObject<int>> node(value, &arr.peek());
    dsaa::QueueNode<TestObject<int>> node1;

    node1 = node;

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node == node1);
}

TEST_CASE("Test Queue QueueNode move assignment.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});

    dsaa::QueueNode<TestObject<int>> node(value, &arr.peek());
    dsaa::QueueNode<TestObject<int>> node1;

    node1 = std::move(node);

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node != node1);

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Queue QueueNode operators.", "[Queue]")
{
    TestObject<int> value(6734);
    dsaa::Queue<TestObject<int>> arr({value});

    dsaa::QueueNode<TestObject<int>> node(value, &arr.peek());
    dsaa::QueueNode<TestObject<int>> node2(node);
    dsaa::QueueNode<TestObject<int>> node3;

    REQUIRE(*node == *node2);
    REQUIRE(*node == node2.value());

    REQUIRE(node.next() == node2.next());
    REQUIRE(node.value() == node2.value());

    REQUIRE(node2 == node);
    REQUIRE(node3 != node);

    REQUIRE(++node == ++node2);
}

TEST_CASE("Test Queue const_iterator default constructor.", "[Queue]")
{
    const_iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test Queue const_iterator constructor with const_pointer.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Queue<TestObject<int>> arr({value});
    SECTION("Iterator at begin")
    {
        const_iterator iter(&arr.peek());
        REQUIRE(&arr.peek() == iter.content());
        REQUIRE(arr.begin() == iter);
    }
    SECTION("Iterator at end")
    {
        const_iterator iter(nullptr);
        REQUIRE(nullptr == iter.content());
        REQUIRE(arr.end() == iter);
    }
}

TEST_CASE("Test Queue const_iterator copy constructor.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Queue<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    const_iterator iter2(iter);

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test Queue const_iterator copy assignment.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Queue<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    const_iterator iter2;

    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test Queue const_iterator operator.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(5, 10));
    dsaa::Queue<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    const_iterator iter2(iter);
    const_iterator iter3;

    REQUIRE(*iter == arr.peek().value());

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(++iter == ++iter2);
}

TEST_CASE("Test Queue iterator default constructor.", "[Queue]")
{
    iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test Queue iterator constructor with const_pointer.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Queue<TestObject<int>> arr({value});
    SECTION("Iterator at begin")
    {
        iterator iter(&arr.peek());
        REQUIRE(&arr.peek() == iter.content());
        REQUIRE(arr.begin() == iter);
    }
    SECTION("Iterator at end")
    {
        iterator iter(nullptr);
        REQUIRE(nullptr == iter.content());
        REQUIRE(arr.end() == iter);
    }
}

TEST_CASE("Test Queue iterator copy constructor.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Queue<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    iterator iter2(iter);
    iterator iter3(iter2);

    REQUIRE(iter2 == iter);
    REQUIRE(iter2 == iter3);
}

TEST_CASE("Test Queue iterator copy assignment.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Queue<TestObject<int>> arr({value});

    iterator iter(&arr.peek());
    iterator iter2;

    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test Queue iterator operator.", "[Queue]")
{
    int value(dsaa::random::random_range_int<int>(5, 10));
    dsaa::Queue<TestObject<int>> arr({value});

    iterator iter(&arr.peek());
    iterator iter2(iter);
    iterator iter3;

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(*iter == arr.peek().value());
    REQUIRE(iter.content()->value() == arr.peek().value());

    REQUIRE(++iter == ++iter2);
}

TEST_CASE("Test Queue default constructor.", "[Queue]")
{
    dsaa::Queue<TestObject<int>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test Queue default constructor and std::allocator.", "[Queue]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::Queue<TestObject<int>> arr(allocator);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test Queue constructor with std::initializer_list.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::Queue<TestObject<int>> arr(list);

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

TEST_CASE("Test Queue constructor with std::initializer_list and std::allocator.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{50, 96, -20, 4, -54, 39};
    std::allocator<TestObject<int>> allocator;

    dsaa::Queue<TestObject<int>> arr(list, allocator);

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

TEST_CASE("Test Queue constructor with a pair of IIterator.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::Queue<TestObject<int>> arr(list.begin(), list.end());

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

TEST_CASE("Test Queue constructor with a pair of IIterator and std::allocator.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    std::allocator<TestObject<int>> allocator;

    dsaa::Queue<TestObject<int>> arr(list.begin(), list.end(), allocator);
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

TEST_CASE("Test Queue copy constructor.", "[Queue]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> arr2(arr);

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

TEST_CASE("Test Queue copy constructor and std::allocator.", "[Queue]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    std::allocator<TestObject<int>> allocator;
    dsaa::Queue<TestObject<int>> arr2(arr, allocator);

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

TEST_CASE("Test Queue move constructor.", "[Queue]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> copy_arr(arr);
    dsaa::Queue<TestObject<int>> arr2(std::move(arr));

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

TEST_CASE("Test Queue move constructor with std::allocator.", "[Queue]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> copy_arr(arr);
    dsaa::Queue<TestObject<int>> arr2(std::move(arr));

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

TEST_CASE("Test Queue copy assignment.", "[Queue]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> arr2;

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

TEST_CASE("Test Queue move assigment.", "[Queue]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> copy_arr(arr);
    dsaa::Queue<TestObject<int>> arr2;

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

TEST_CASE("Test Queue copy assignment using std::initializer_list.", "[Queue]")
{
    dsaa::Queue<TestObject<int>> arr;
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

TEST_CASE("Test Queue assign function using pair IIterator.", "[Queue]")
{
    dsaa::Queue<TestObject<int>> arr;
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

TEST_CASE("Test Queue assign function using std::initializer_list.", "[Queue]")
{
    dsaa::Queue<TestObject<int>> arr;
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

TEST_CASE("Test Queue peek function.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    dsaa::Queue<TestObject<int>> arr(list);

    REQUIRE(arr.peek().value() == *list.begin());
    REQUIRE(arr.size() == list.size());
}

TEST_CASE("Test Queue get_index function.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    dsaa::Queue<TestObject<int>> arr(list);

    REQUIRE(0 == arr.get_index(arr.begin()));
    REQUIRE(list.size() == arr.get_index(arr.end()));
}

TEST_CASE("Test Queue get_iterator function.", "[Queue]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    dsaa::Queue<TestObject<int>> arr(list);

    REQUIRE(arr.begin() == arr.get_iterator(0));
    REQUIRE(arr.end() == arr.get_iterator(list.size()));
}

TEST_CASE("Test Queue insert with parameter value.", "[Queue]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.insert(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    for (; param.end() != param_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == value);
}

TEST_CASE("Test Queue insert by move value.", "[Queue]")
{
    size_t arr_size(13);

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    TestObject<int> value(dsaa::random::random_range_int<int>());
    TestObject<int> copy_of_value(value);

    arr.insert(std::move(value));

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    for (; param.end() != param_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == copy_of_value);
}

TEST_CASE("Test Queue insert by std::initializer_list.", "[Queue]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{-84, 85, -17, -31, -43, -99, 3};

    arr.insert(list);

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());

    for (; copy_arr.end() != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);

    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Queue insert by a pair of IIterator.", "[Queue]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Queue<TestObject<int>> copy_arr(arr);

    std::initializer_list<TestObject<int>> list{44, 20, -32, 35, -85, -99, -39};

    arr.insert(list.begin(), list.end());

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());

    for (; copy_arr.end() != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);

    for (auto list_iter(list.begin()); list.end() != list_iter; ++list_iter, ++arr_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Queue emplace using parameter pack.", "[Queue]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.emplace(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());

    for (; param.end() != param_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));

    REQUIRE(*arr_iter == value);
}

TEST_CASE("Test Queue extract function.", "[Queue]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value = arr.extract();

    REQUIRE(!arr.empty());
    REQUIRE(param.size() - 1 == arr.size());
    REQUIRE(value == TestObject<int>(param[0]));

    auto arr_iter(arr.begin());
    auto param_iter(param.begin());
    ++param_iter;

    for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test Queue clean function.", "[Queue]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Queue<TestObject<int>> arr(param.begin(), param.end());

    arr.clean();
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}