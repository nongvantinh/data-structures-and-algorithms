#include "Catch2/Catch.hpp"
#include "lists/DoublyLinkList.h"
#include "algorithms/Random.h"
#include "test/TestObject.h"
#include "arrays/DynamicArray.h"

using iterator = dsaa::DoublyLinkList<TestObject<int>>::iterator;
using const_iterator = dsaa::DoublyLinkList<TestObject<int>>::const_iterator;
using reserve_iterator = dsaa::DoublyLinkList<TestObject<int>>::reverse_iterator;

TEST_CASE("Test DoublyLinkList DoublyLinkListNode default constructor.", "[DoublyLinkList]")
{
    dsaa::DoublyLinkListNode<TestObject<int>> node;

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.previous());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode constructor with value.", "[DoublyLinkList]")
{
    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(value);

    REQUIRE(value == node.value());
    REQUIRE(nullptr == node.previous());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode constructor by moving a value.", "[DoublyLinkList]")
{
    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(std::move(value));

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(nullptr == node.previous());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode constructor with value, previous, next.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(value, &arr.first(), &arr.last());

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(&arr.first() == node.previous());
    REQUIRE(&arr.last() == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode constructor by move a value, previous, next.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(std::move(value), &arr.first(), &arr.last());

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(&arr.first() == node.previous());
    REQUIRE(&arr.last() == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode copy constructor.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(std::move(value), &arr.first(), &arr.last());
    dsaa::DoublyLinkListNode<TestObject<int>> node1(node);

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.first() == node1.previous());
    REQUIRE(&arr.last() == node1.next());

    REQUIRE(node == node1);
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode move constructor.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(std::move(value), &arr.first(), &arr.last());
    dsaa::DoublyLinkListNode<TestObject<int>> node1(std::move(node));

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.first() == node1.previous());
    REQUIRE(&arr.last() == node1.next());

    REQUIRE(node != node1);

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.previous());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode copy assignment.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(std::move(value), &arr.first(), &arr.last());
    dsaa::DoublyLinkListNode<TestObject<int>> node1;

    node1 = node;

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.first() == node1.previous());
    REQUIRE(&arr.last() == node1.next());

    REQUIRE(node == node1);
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode move assignment.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(std::move(value), &arr.first(), &arr.last());
    dsaa::DoublyLinkListNode<TestObject<int>> node1;

    node1 = std::move(node);

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.first() == node1.previous());
    REQUIRE(&arr.last() == node1.next());

    REQUIRE(node != node1);

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.previous());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test DoublyLinkList DoublyLinkListNode operators.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(5, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    TestObject<int> value(6734);
    dsaa::DoublyLinkListNode<TestObject<int>> node(value, &arr.first(), &arr.last());
    dsaa::DoublyLinkListNode<TestObject<int>> node2(node);
    dsaa::DoublyLinkListNode<TestObject<int>> node3;

    REQUIRE(node2 == node);
    REQUIRE(node3 != node);

    REQUIRE(++node == ++node2);
    REQUIRE(--node == --node2);

    REQUIRE(node++ == node2++);
    REQUIRE(node-- == node2--);

    REQUIRE(*node == *node2);
    REQUIRE(*node == node2.value());
    REQUIRE(node.previous() == node2.previous());
    REQUIRE(node.next() == node2.next());
    REQUIRE(node.value() == node2.value());
}

TEST_CASE("Test DoublyLinkList const_iterator default constructor.", "[DoublyLinkList]")
{
    const_iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test DoublyLinkList const_iterator constructor with const_pointer.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);
    SECTION("Iterator at begin")
    {
        const_iterator iter(&arr.first());
        REQUIRE(&arr.first() == iter.content());
        REQUIRE(arr.begin() == iter);
    }
    SECTION("Iterator at end")
    {
        const_iterator iter(nullptr);
        REQUIRE(nullptr == iter.content());
        REQUIRE(arr.end() == iter);
    }
}

TEST_CASE("Test DoublyLinkList const_iterator copy constructor.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr.first());
    const_iterator iter2(iter);

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test DoublyLinkList const_iterator copy assignment.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr.first());
    const_iterator iter2;
    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test DoublyLinkList const_iterator operator.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(5, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr.first());
    const_iterator iter2(iter);
    const_iterator iter3;

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(++iter == ++iter2);
    REQUIRE(--iter == --iter2);

    REQUIRE(iter++ == iter2++);
    REQUIRE(iter-- == iter2--);

    REQUIRE(*iter == arr.first().value());
    REQUIRE(*iter == *arr.first());

    REQUIRE(iter.content() == &arr.first());
}

TEST_CASE("Test DoublyLinkList iterator default constructor.", "[DoublyLinkList]")
{
    iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test DoublyLinkList iterator constructor with const_pointer.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);
    SECTION("Iterator at begin")
    {
        iterator iter(&arr.first());
        REQUIRE(&arr.first() == iter.content());
        REQUIRE(arr.begin() == iter);
    }
    SECTION("Iterator at end")
    {
        iterator iter(nullptr);
        REQUIRE(nullptr == iter.content());
        REQUIRE(arr.end() == iter);
    }
}

TEST_CASE("Test DoublyLinkList iterator copy constructor.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    const_iterator iter(&arr.first());
    iterator iter2(iter);
    iterator iter3(iter2);

    REQUIRE(iter2 == iter);
    REQUIRE(iter2 == iter3);
}

TEST_CASE("Test DoublyLinkList iterator copy assignment.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    iterator iter(&arr.first());
    iterator iter2;
    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test DoublyLinkList iterator operator.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(5, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    iterator iter(&arr.first());
    iterator iter2(iter);
    iterator iter3;

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(++iter == ++iter2);
    REQUIRE(--iter == --iter2);

    REQUIRE(iter++ == iter2++);
    REQUIRE(iter-- == iter2--);

    REQUIRE(*iter == arr.first().value());
    REQUIRE(*iter == *arr.first());

    *iter = TestObject<int>(555);
    REQUIRE(TestObject<int>(555) == *iter);

    REQUIRE(iter.content() == &arr.first());

    iter = &arr.last();
    REQUIRE(iter.content() == &arr.last());
}

TEST_CASE("Test DoublyLinkList default constructor.", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<TestObject<int>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DoublyLinkList default constructor and std::allocator.", "[DoublyLinkList]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::DoublyLinkList<TestObject<int>> arr(allocator);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DoublyLinkList constructor with given size.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::DoublyLinkList<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test DoublyLinkList constructor with given size and std::allocator.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    std::allocator<TestObject<int>> allocator;

    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == num_elem);

    for (iterator arr_iter(arr.begin()); arr.end() != arr_iter; ++arr_iter)
        REQUIRE(dsaa::DoublyLinkList<TestObject<int>>::value_type() == *arr_iter);
}

TEST_CASE("Test DoublyLinkList constructor with given size and value.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem, value);

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

TEST_CASE("Test DoublyLinkList constructor with given size, value and std::allocator.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    std::allocator<TestObject<int>> allocator;

    dsaa::DoublyLinkList<TestObject<int>> arr(num_elem, value, allocator);

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

TEST_CASE("Test DoublyLinkList constructor with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::DoublyLinkList<TestObject<int>> arr(list);

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

TEST_CASE("Test DoublyLinkList constructor with std::initializer_list and std::allocator.", "[DoublyLinkList]")
{
    std::initializer_list<TestObject<int>> list{50, 96, -20, 4, -54, 39};
    std::allocator<TestObject<int>> allocator;

    dsaa::DoublyLinkList<TestObject<int>> arr(list, allocator);

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

TEST_CASE("Test DoublyLinkList constructor with a pair of IIterator.", "[DoublyLinkList]")
{
    std::initializer_list<TestObject<int>> list{-2, 89, 71, -12, -16, 13, -80, -70, -98, -65, -82, 85};
    dsaa::DoublyLinkList<TestObject<int>> arr(list.begin(), list.end());

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

TEST_CASE("Test DoublyLinkList constructor with a pair of IIterator and std::allocator.", "[DoublyLinkList]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    std::allocator<TestObject<int>> allocator;

    dsaa::DoublyLinkList<TestObject<int>> arr(list.begin(), list.end(), allocator);
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

TEST_CASE("Test DoublyLinkList copy constructor.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> arr2(arr);

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

TEST_CASE("Test DoublyLinkList copy constructor and std::allocator.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    std::allocator<TestObject<int>> allocator;
    dsaa::DoublyLinkList<TestObject<int>> arr2(arr, allocator);

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

TEST_CASE("Test DoublyLinkList move constructor.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);
    dsaa::DoublyLinkList<TestObject<int>> arr2(std::move(arr));

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

TEST_CASE("Test DoublyLinkList move constructor with std::allocator.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);
    dsaa::DoublyLinkList<TestObject<int>> arr2(std::move(arr));

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

TEST_CASE("Test DoublyLinkList copy assignment.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> arr2;

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

TEST_CASE("Test DoublyLinkList move assigment.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);
    dsaa::DoublyLinkList<TestObject<int>> arr2;

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

TEST_CASE("Test DoublyLinkList copy assignment using std::initializer_list.", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<TestObject<int>> arr;
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

TEST_CASE("Test DoublyLinkList assign function using pair IIterator.", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<TestObject<int>> arr;
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

TEST_CASE("Test DoublyLinkList assign function with size and value.", "[DoublyLinkList]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
    TestObject<int> value(dsaa::random::random_range_int<int>());
    dsaa::DoublyLinkList<TestObject<int>> arr;

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

TEST_CASE("Test DoublyLinkList assign function using std::initializer_list.", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<TestObject<int>> arr;
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

TEST_CASE("Test DoublyLinkList get_index function.", "[DoublyLinkList]")
{
    size_t size(99);
    dsaa::DoublyLinkList<TestObject<int>> arr(size);

    REQUIRE(0 == arr.get_index(arr.begin()));
    REQUIRE(size == arr.get_index(arr.end()));
}

TEST_CASE("Test DoublyLinkList get_iterator function.", "[DoublyLinkList]")
{
    size_t size(99);
    dsaa::DoublyLinkList<TestObject<int>> arr(size);

    REQUIRE(arr.begin() == arr.get_iterator(0));
    REQUIRE(arr.end() == arr.get_iterator(size));
}

TEST_CASE("Test DoublyLinkList resize function.", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<TestObject<int>> arr;

    SECTION("Test DoublyLinkList resize with value 0.")
    {

        size_t new_size(0);
        arr.resize(new_size);
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Test DoublyLinkList resize with positive value.")
    {
        size_t new_size(88);
        arr.resize(new_size);
        REQUIRE(arr.size() == new_size);
    }

    // SECTION("Test DoublyLinkList resize with very large positive value.")
    // {
    //     size_t new_size(999999);
    //     arr.resize(new_size);
    //     REQUIRE(arr.size() == new_size);
    // }
}

TEST_CASE("Test DoublyLinkList insert_first with parameter value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

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

TEST_CASE("Test DoublyLinkList insert_first by move value.", "[DoublyLinkList]")
{
    size_t arr_size(13);

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
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

TEST_CASE("Test DoublyLinkList insert_first by a mount of size and value.", "[DoublyLinkList]")
{
    size_t arr_size(11);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

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

TEST_CASE("Test DoublyLinkList insert_first by std::initializer_list.", "[DoublyLinkList]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);

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

TEST_CASE("Test DoublyLinkList insert_first by a pair of IIterator.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);

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

TEST_CASE("Test DoublyLinkList emplace_first using parameter pack.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

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

TEST_CASE("Test DoublyLinkList insert_last with parameter value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
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

TEST_CASE("Test DoublyLinkList insert_last by move value.", "[DoublyLinkList]")
{
    size_t arr_size(13);

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
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

TEST_CASE("Test DoublyLinkList insert_last by a mount of size and value.", "[DoublyLinkList]")
{
    size_t arr_size(11);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

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

TEST_CASE("Test DoublyLinkList insert_last by std::initializer_list.", "[DoublyLinkList]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);

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

TEST_CASE("Test DoublyLinkList insert_last by a pair of IIterator.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
    dsaa::DoublyLinkList<TestObject<int>> copy_arr(arr);

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

TEST_CASE("Test DoublyLinkList emplace_last using parameter pack.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());
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

TEST_CASE("Test DoublyLinkList insert_before with one parameter's value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_before the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(0);

        arr.insert_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList insert_before midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() / 2);

        arr.insert_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList insert_before last position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() - 1);

        arr.insert_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList insert_before random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

TEST_CASE("Test DoublyLinkList insert_before by move a value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_before the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(0);

        arr.insert_before(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList insert_before midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(arr.size() / 2);

        arr.insert_before(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList insert_before end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(arr.size() - 1);

        arr.insert_before(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList insert_before random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());
        TestObject<int> copy_of_value(value);

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_before(arr.get_iterator(index), std::move(value));

        REQUIRE(arr.size() == param.size() + 1);

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

TEST_CASE("Test DoublyLinkList insert_before by a mount of size's value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_before the begining position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(0);

        arr.insert_before(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

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

    SECTION("Test DoublyLinkList insert_before midle position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() / 2);

        arr.insert_before(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

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

    SECTION("Test DoublyLinkList insert_before end position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() - 1);

        arr.insert_before(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

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

    SECTION("Test DoublyLinkList insert_before random position.")
    {
        size_t num_elem(dsaa::random::random_range_int<int>(1, 10));
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_before(arr.get_iterator(index), num_elem, value);

        REQUIRE(arr.size() == param.size() + num_elem);

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

TEST_CASE("Test DoublyLinkList insert_before by a std::initializer_list.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_before the begining position.")
    {
        std::initializer_list<TestObject<int>> list{-60, -92, 2, 30, 51, -97, 97, 66};

        size_t index(0);

        arr.insert_before(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

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

    SECTION("Test DoublyLinkList insert_before midle position.")
    {
        std::initializer_list<TestObject<int>> list{-6, 96, 32, 48, -61, -13};

        size_t index(arr.size() / 2);

        arr.insert_before(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

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

    SECTION("Test DoublyLinkList insert_before end position.")
    {
        std::initializer_list<TestObject<int>> list{82, -39, 33, 0, 84, 0, 61, 57, -37, 38, -43, -100};

        size_t index(arr.size() - 1);

        arr.insert_before(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

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

    SECTION("Test DoublyLinkList insert_before random position.")
    {
        std::initializer_list<TestObject<int>> list{8, 61, -76, 89, 35, 68, -59, -1, 81, 40};

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_before(arr.get_iterator(index), list);

        REQUIRE(arr.size() == param.size() + list.size());

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

TEST_CASE("Test DoublyLinkList insert_before by a pair of IIterator.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_before the begining position.")
    {
        std::initializer_list<TestObject<int>> list{-60, -92, 2, 30, 51, -97, 97, 66};

        size_t index(0);

        arr.insert_before(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

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

    SECTION("Test DoublyLinkList insert_before midle position.")
    {
        std::initializer_list<TestObject<int>> list{-6, 96, 32, 48, -61, -13};

        size_t index(arr.size() / 2);

        arr.insert_before(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

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

    SECTION("Test DoublyLinkList insert_before end position.")
    {
        std::initializer_list<TestObject<int>> list{82, -39, 33, 0, 84, 0, 61, 57, -37, 38, -43, -100};

        size_t index(arr.size() - 1);

        arr.insert_before(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

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

    SECTION("Test DoublyLinkList insert_before random position.")
    {
        std::initializer_list<TestObject<int>> list{8, 61, -76, 89, 35, 68, -59, -1, 81, 40};

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.insert_before(arr.get_iterator(index), list.begin(), list.end());

        REQUIRE(arr.size() == param.size() + list.size());

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

TEST_CASE("Test DoublyLinkList emplace_before using parameter pack.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList emplace_before the begining position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(0);

        arr.emplace_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList emplace_before midle position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() / 2);

        arr.emplace_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList emplace_before end position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(arr.size() - 1);

        arr.emplace_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

    SECTION("Test DoublyLinkList emplace_before random position.")
    {
        TestObject<int> value(dsaa::random::random_range_int<int>());

        size_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.emplace_before(arr.get_iterator(index), value);

        REQUIRE(arr.size() == param.size() + 1);

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

TEST_CASE("Test DoublyLinkList insert_after with one parameter's value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_after the begining position.")
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

    SECTION("Test DoublyLinkList insert_after midle position.")
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

    SECTION("Test DoublyLinkList insert_after last position.")
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

    SECTION("Test DoublyLinkList insert_after random position.")
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

TEST_CASE("Test DoublyLinkList insert_after by move a value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_after the begining position.")
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

    SECTION("Test DoublyLinkList insert_after midle position.")
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

    SECTION("Test DoublyLinkList insert_after end position.")
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

    SECTION("Test DoublyLinkList insert_after random position.")
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

TEST_CASE("Test DoublyLinkList insert_after by a mount of size's value.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_after the begining position.")
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

    SECTION("Test DoublyLinkList insert_after midle position.")
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

    SECTION("Test DoublyLinkList insert_after end position.")
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

    SECTION("Test DoublyLinkList insert_after random position.")
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

TEST_CASE("Test DoublyLinkList insert_after by a std::initializer_list.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_after the begining position.")
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

    SECTION("Test DoublyLinkList insert_after midle position.")
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

    SECTION("Test DoublyLinkList insert_after end position.")
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

    SECTION("Test DoublyLinkList insert_after random position.")
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

TEST_CASE("Test DoublyLinkList insert_after by a pair of IIterator.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList insert_after the begining position.")
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

    SECTION("Test DoublyLinkList insert_after midle position.")
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

    SECTION("Test DoublyLinkList insert_after end position.")
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

    SECTION("Test DoublyLinkList insert_after random position.")
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

TEST_CASE("Test DoublyLinkList emplace_after using parameter pack.", "[DoublyLinkList]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList emplace_after the begining position.")
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

    SECTION("Test DoublyLinkList emplace_after midle position.")
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

    SECTION("Test DoublyLinkList emplace_after end position.")
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

    SECTION("Test DoublyLinkList emplace_after random position.")
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

TEST_CASE("Test DoublyLinkList erase function.", "[DoublyLinkList]")
{
    size_t arr_size(42);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList erase the begining position.")
    {
        int64_t index(0);

        arr.erase(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        auto param_end(param.get_iterator(index));
        for (; param_end != param_iter; ++param_iter, ++arr_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DoublyLinkList erase midle position.")
    {
        int64_t index(arr.size() / 2);

        arr.erase(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        auto param_end(param.get_iterator(index));
        for (; param_end != param_iter; ++param_iter, ++arr_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DoublyLinkList erase last position.")
    {
        int64_t index(arr.size() - 1);
        arr.erase(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        auto param_end(param.get_iterator(index));
        for (; param_end != param_iter; ++param_iter, ++arr_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DoublyLinkList erase random position.")
    {
        int64_t index(dsaa::random::random_range_int<int>(0, arr.size() - 1));

        arr.erase(arr.get_iterator(index));

        REQUIRE(arr.size() + 1 == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.begin());
        auto param_end(param.get_iterator(index));
        for (; param_end != param_iter; ++param_iter, ++arr_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));

        ++param_iter;

        // Continues what's left.
        for (; arr.end() != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }
}

TEST_CASE("Test DoublyLinkList erase function with a pair of IIterator.", "[DoublyLinkList]")
{
    size_t arr_size(122);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    SECTION("Test DoublyLinkList erase from begining to the end.")
    {
        arr.erase(arr.begin(), arr.end());

        REQUIRE(arr.empty());
        REQUIRE(0 == arr.size());

        REQUIRE(iterator() == arr.begin());
        REQUIRE(const_iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(const_iterator() == arr.cend());
    }

    SECTION("Test DoublyLinkList erase from begining to midle.")
    {
        size_t index(arr.size() / 2);

        arr.erase(arr.begin(), arr.get_iterator(index));

        REQUIRE(arr.size() + index == param.size());

        auto arr_iter(arr.begin());
        auto param_iter(param.get_iterator(index));
        for (auto arr_end(arr.end()); arr_end != arr_iter; ++arr_iter, ++param_iter)
            REQUIRE(*arr_iter == TestObject<int>(*param_iter));
    }

    SECTION("Test DoublyLinkList erase from midle to the end.")
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

TEST_CASE("Test DoublyLinkList erase_last function.", "[DoublyLinkList]")
{
    size_t arr_size(122);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    arr.erase_last();

    REQUIRE(!arr.empty());
    REQUIRE(arr_size - 1 == arr.size());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}

TEST_CASE("Test DoublyLinkList clean function.", "[DoublyLinkList]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::DoublyLinkList<TestObject<int>> arr(param.begin(), param.end());

    arr.clean();
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}