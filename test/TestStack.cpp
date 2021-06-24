#include "Catch2/Catch.hpp"
#include "Stack.h"
#include "Random.h"
#include "TestObject.h"
#include "DynamicArray.h"

using iterator = dsaa::Stack<TestObject<int>>::iterator;
using const_iterator = dsaa::Stack<TestObject<int>>::const_iterator;

TEST_CASE("Test Stack StackNode default constructor.", "[Stack]")
{
    dsaa::StackNode<TestObject<int>> node;

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Stack StackNode constructor with value.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::StackNode<TestObject<int>> node(value);

    REQUIRE(value == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Stack StackNode constructor by moving a value.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::StackNode<TestObject<int>> node(std::move(value));

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Stack StackNode constructor with value, next.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});

    dsaa::StackNode<TestObject<int>> node(value, &arr.peek());

    REQUIRE(value == node.value());
    REQUIRE(&arr.peek() == node.next());
}

TEST_CASE("Test Stack StackNode constructor by move a value, next.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});
    dsaa::StackNode<TestObject<int>> node(std::move(value), &arr.peek());

    REQUIRE(TestObject<int>(6734) == node.value());
    REQUIRE(&arr.peek() == node.next());
}

TEST_CASE("Test Stack StackNode copy constructor.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});

    dsaa::StackNode<TestObject<int>> node(value, &arr.peek());
    dsaa::StackNode<TestObject<int>> node1(node);

    REQUIRE(value == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node == node1);
}

TEST_CASE("Test Stack StackNode move constructor.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});

    dsaa::StackNode<TestObject<int>> node(value, &arr.peek());
    dsaa::StackNode<TestObject<int>> node1(std::move(node));

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node != node1);

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Stack StackNode copy assignment.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});

    dsaa::StackNode<TestObject<int>> node(value, &arr.peek());
    dsaa::StackNode<TestObject<int>> node1;

    node1 = node;

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node == node1);
}

TEST_CASE("Test Stack StackNode move assignment.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});

    dsaa::StackNode<TestObject<int>> node(value, &arr.peek());
    dsaa::StackNode<TestObject<int>> node1;

    node1 = std::move(node);

    REQUIRE(TestObject<int>(6734) == node1.value());
    REQUIRE(&arr.peek() == node1.next());

    REQUIRE(node != node1);

    REQUIRE(TestObject<int>() == node.value());
    REQUIRE(nullptr == node.next());
}

TEST_CASE("Test Stack StackNode operators.", "[Stack]")
{
    TestObject<int> value(6734);
    dsaa::Stack<TestObject<int>> arr({value});

    dsaa::StackNode<TestObject<int>> node(value, &arr.peek());
    dsaa::StackNode<TestObject<int>> node2(node);
    dsaa::StackNode<TestObject<int>> node3;

    REQUIRE(*node == *node2);
    REQUIRE(*node == node2.value());

    REQUIRE(node.next() == node2.next());
    REQUIRE(node.value() == node2.value());

    REQUIRE(node2 == node);
    REQUIRE(node3 != node);

    REQUIRE(++node == ++node2);
}

TEST_CASE("Test Stack const_iterator default constructor.", "[Stack]")
{
    const_iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test Stack const_iterator constructor with const_pointer.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Stack<TestObject<int>> arr({value});
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

TEST_CASE("Test Stack const_iterator copy constructor.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Stack<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    const_iterator iter2(iter);

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test Stack const_iterator copy assignment.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Stack<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    const_iterator iter2;

    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test Stack const_iterator operator.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(5, 10));
    dsaa::Stack<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    const_iterator iter2(iter);
    const_iterator iter3;

    REQUIRE(*iter == arr.peek().value());

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(++iter == ++iter2);
}

TEST_CASE("Test Stack iterator default constructor.", "[Stack]")
{
    iterator iter;
    REQUIRE(nullptr == iter.content());
}

TEST_CASE("Test Stack iterator constructor with const_pointer.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Stack<TestObject<int>> arr({value});
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

TEST_CASE("Test Stack iterator copy constructor.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Stack<TestObject<int>> arr({value});

    const_iterator iter(&arr.peek());
    iterator iter2(iter);
    iterator iter3(iter2);

    REQUIRE(iter2 == iter);
    REQUIRE(iter2 == iter3);
}

TEST_CASE("Test Stack iterator copy assignment.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(1, 10));
    dsaa::Stack<TestObject<int>> arr({value});

    iterator iter(&arr.peek());
    iterator iter2;

    iter2 = iter;

    REQUIRE(iter2 == iter);
}

TEST_CASE("Test Stack iterator operator.", "[Stack]")
{
    int value(dsaa::random::random_range_int<int>(5, 10));
    dsaa::Stack<TestObject<int>> arr({value});

    iterator iter(&arr.peek());
    iterator iter2(iter);
    iterator iter3;

    REQUIRE(iter2 == iter);
    REQUIRE(iter != iter3);

    REQUIRE(*iter == arr.peek().value());
    REQUIRE(iter.content()->value() == arr.peek().value());

    REQUIRE(++iter == ++iter2);
}

TEST_CASE("Test Stack default constructor.", "[Stack]")
{
    dsaa::Stack<TestObject<int>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test Stack default constructor and std::allocator.", "[Stack]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::Stack<TestObject<int>> arr(allocator);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == allocator);
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test Stack constructor with std::initializer_list.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::Stack<TestObject<int>> arr(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack constructor with std::initializer_list and std::allocator.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};
    std::allocator<TestObject<int>> allocator;

    dsaa::Stack<TestObject<int>> arr(list, allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack constructor with a pair of IIterator.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};

    dsaa::Stack<TestObject<int>> arr(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack constructor with a pair of IIterator and std::allocator.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{38, 43, 30, -82, 60, 77, -12, -61, 55};
    std::allocator<TestObject<int>> allocator;

    dsaa::Stack<TestObject<int>> arr(list.begin(), list.end(), allocator);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(const_iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<TestObject<int>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto arr_iter(arr.begin());
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack move constructor.", "[Stack]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> copy_arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> arr2(std::move(arr));

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

TEST_CASE("Test Stack move constructor with std::allocator.", "[Stack]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> copy_arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> arr2(std::move(arr));

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

TEST_CASE("Test Stack move assigment.", "[Stack]")
{
    size_t num_elem(dsaa::random::random_range_int<int>(1, 10));

    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(num_elem));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> copy_arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> arr2;

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

TEST_CASE("Test Stack copy assignment using std::initializer_list.", "[Stack]")
{
    dsaa::Stack<TestObject<int>> arr;
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
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack assign function using pair IIterator.", "[Stack]")
{
    dsaa::Stack<TestObject<int>> arr;
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
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack assign function using std::initializer_list.", "[Stack]")
{
    dsaa::Stack<TestObject<int>> arr;
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
    auto list_iter(list.end() - 1);
    for (; arr.end() != arr_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);
}

TEST_CASE("Test Stack peek function.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    dsaa::Stack<TestObject<int>> arr(list);

    REQUIRE(arr.peek().value() == *(list.end() - 1));
    REQUIRE(arr.size() == list.size());
}

TEST_CASE("Test Stack get_index function.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    dsaa::Stack<TestObject<int>> arr(list);

    REQUIRE(0 == arr.get_index(arr.begin()));
    REQUIRE(list.size() == arr.get_index(arr.end()));
}

TEST_CASE("Test Stack get_iterator function.", "[Stack]")
{
    std::initializer_list<TestObject<int>> list{43, -84, -67, -90, -13, -69, 78, -27};
    dsaa::Stack<TestObject<int>> arr(list);

    REQUIRE(arr.begin() == arr.get_iterator(0));
    REQUIRE(arr.end() == arr.get_iterator(list.size()));
}

TEST_CASE("Test Stack insert with parameter value.", "[Stack]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.insert(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.end() - 1);

    REQUIRE(*arr_iter == value);
    ++arr_iter;

    for (; arr.end() != arr_iter; ++arr_iter, --param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test Stack insert with by move parameter value.", "[Stack]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());
    TestObject<int> copy_value(value);

    arr.insert(std::move(value));

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.end() - 1);

    REQUIRE(*arr_iter == copy_value);
    ++arr_iter;

    for (; arr.end() != arr_iter; ++arr_iter, --param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test Stack insert by std::initializer_list.", "[Stack]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> copy_arr(param.begin(), param.end());

    std::initializer_list<TestObject<int>> list{-84, 85, -17, -31, -43, -99, 3};

    arr.insert(list);

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());
    auto list_iter(list.end() - 1);

    for (; list.begin() <= list_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);

    for (; copy_arr.end() != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);
}

TEST_CASE("Test Stack insert by a pair of IIterator.", "[Stack]")
{
    size_t arr_size(12);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());
    dsaa::Stack<TestObject<int>> copy_arr(param.begin(), param.end());

    std::initializer_list<TestObject<int>> list{-84, 85, -17, -31, -43, -99, 3};

    arr.insert(list.begin(), list.end());

    REQUIRE(arr.size() == copy_arr.size() + list.size());

    auto arr_iter(arr.begin());
    auto copy_arr_iter(copy_arr.begin());
    auto list_iter(list.end() - 1);

    for (; list.begin() <= list_iter; ++arr_iter, --list_iter)
        REQUIRE(*list_iter == *arr_iter);

    for (; copy_arr.end() != copy_arr_iter; ++copy_arr_iter, ++arr_iter)
        REQUIRE(*copy_arr_iter == *arr_iter);
}

TEST_CASE("Test Stack emplace using parameter pack.", "[Stack]")
{
    size_t arr_size(13);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value(dsaa::random::random_range_int<int>());

    arr.emplace(value);

    REQUIRE(arr.size() == param.size() + 1);

    auto arr_iter(arr.begin());
    auto param_iter(param.end() - 1);

    REQUIRE(*arr_iter == value);
    ++arr_iter;

    for (; arr.end() != arr_iter; ++arr_iter, --param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test Stack extract function.", "[Stack]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());

    TestObject<int> value = arr.extract();

    REQUIRE(!arr.empty());
    REQUIRE(param.size() - 1 == arr.size());
    REQUIRE(value == TestObject<int>(param[param.size() - 1]));

    auto arr_iter(arr.begin());
    auto param_iter(param.end() - 1);

    REQUIRE(TestObject<int>(*param_iter) == value);
    --param_iter;

    for (; arr.end() != arr_iter; ++arr_iter, --param_iter)
        REQUIRE(*arr_iter == TestObject<int>(*param_iter));
}

TEST_CASE("Test Stack clean function.", "[Stack]")
{
    size_t arr_size(51);
    dsaa::DynamicArray<int> param(dsaa::random::random_range_ints<int>(arr_size));
    dsaa::Stack<TestObject<int>> arr(param.begin(), param.end());

    arr.clean();
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(const_iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(const_iterator() == arr.cend());
}