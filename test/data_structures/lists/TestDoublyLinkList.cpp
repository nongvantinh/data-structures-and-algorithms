#include "Catch2/Catch.hpp"
#include "lists/DoublyLinkList.h"
#include "algorithms/Search.h"

using iterator = dsaa::DoublyLinkList<double>::iterator;
TEST_CASE("Test DoublyLinkListNode constructor", "[DoublyLinkListNode]")
{
    SECTION("Test DoublyLinkListNode default constructor.")
    {
        dsaa::DoublyLinkListNode<double> node;
        REQUIRE(double() == *node);
        REQUIRE(double() == node.value());
        REQUIRE(nullptr == node.previous());
        REQUIRE(nullptr == node.next());
    }

    SECTION("Test DoublyLinkListNode constructor with a value given.")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node(value);
        REQUIRE(value == *node);
        REQUIRE(value == node.value());
        REQUIRE(nullptr == node.previous());
        REQUIRE(nullptr == node.next());
    }

    SECTION("Test DoublyLinkListNode default constructor with values given.")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node(value, nullptr, nullptr);
        REQUIRE(value == *node);
        REQUIRE(value == node.value());
        REQUIRE(nullptr == node.previous());
        REQUIRE(nullptr == node.next());
    }

    SECTION("Test DoublyLinkListNode constructor with sets of values given.")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node1(value);
        dsaa::DoublyLinkListNode<double> node2(value, &node1, nullptr);
        dsaa::DoublyLinkListNode<double> node3(value, &node1, &node2);

        REQUIRE(value == *node1);
        REQUIRE(value == node1.value());
        REQUIRE(nullptr == node1.previous());
        REQUIRE(nullptr == node1.next());

        REQUIRE(value == *node2);
        REQUIRE(value == node2.value());
        REQUIRE(&node1 == node2.previous());
        REQUIRE(nullptr == node2.next());

        REQUIRE(value == *node3);
        REQUIRE(value == node3.value());
        REQUIRE(&node1 == node3.previous());
        REQUIRE(&node2 == node3.next());
    }

    SECTION("Test DoublyLinkListNode constructor by move p_value.")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node1(value);
        dsaa::DoublyLinkListNode<double> node2(std::move(value), &node1, nullptr);
        dsaa::DoublyLinkListNode<double> node3(value, &node1, &node2);

        REQUIRE(256.1667 == *node1);
        REQUIRE(256.1667 == node1.value());
        REQUIRE(nullptr == node1.previous());
        REQUIRE(nullptr == node1.next());

        REQUIRE(256.1667 == *node2);
        REQUIRE(256.1667 == node2.value());
        REQUIRE(&node1 == node2.previous());
        REQUIRE(nullptr == node2.next());

        REQUIRE(double() == *node3);
        REQUIRE(double() == node3.value());
        REQUIRE(&node1 == node3.previous());
        REQUIRE(&node2 == node3.next());
    }

    SECTION("Test DoublyLinkListNode copy constructor.")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node1(value);
        dsaa::DoublyLinkListNode<double> node2(std::move(value), &node1, nullptr);
        dsaa::DoublyLinkListNode<double> node3(value, &node1, &node2);

        dsaa::DoublyLinkListNode<double> node4(node3);

        REQUIRE(double() == *node3);
        REQUIRE(double() == node3.value());
        REQUIRE(&node1 == node3.previous());
        REQUIRE(&node2 == node3.next());

        REQUIRE(node4 == node3);
    }

    SECTION("Test DoublyLinkListNode move constructor.")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node1(value);
        dsaa::DoublyLinkListNode<double> node2(std::move(value), &node1, nullptr);
        dsaa::DoublyLinkListNode<double> node3(value, &node1, &node2);

        dsaa::DoublyLinkListNode<double> node4(std::move(node3));

        REQUIRE(double() == *node3);
        REQUIRE(double() == node3.value());
        REQUIRE(nullptr == node3.previous());
        REQUIRE(nullptr == node3.next());

        REQUIRE(dsaa::DoublyLinkListNode<double>() == node3);
    }
}

TEST_CASE("TEST DoublyLinkList::ConstIterator", "[DoublyLinkListConstIterator]")
{
    SECTION("Test ConstIterator constructor")
    {
        dsaa::DoublyLinkList<double>::ConstIterator const_iterator;

        REQUIRE(nullptr == const_iterator.content());
    }

    SECTION("Test ConstIterator constructor with argument")
    {
        double value(256.1667);
        dsaa::DoublyLinkListNode<double> node1(value);
        dsaa::DoublyLinkListNode<double> node2(std::move(value), &node1, nullptr);
        dsaa::DoublyLinkListNode<double> node3(value, &node2, nullptr);
        node1.next() = &node2;
        node2.next() = &node3;
        dsaa::DoublyLinkList<double>::ConstIterator const_iterator(&node1);

        REQUIRE(&node1 == const_iterator.content());
        ++const_iterator;
        REQUIRE(&node2 == const_iterator.content());
        ++const_iterator;
        REQUIRE(&node3 == const_iterator.content());
        ++const_iterator;
        REQUIRE(nullptr == const_iterator.content());
    }
}

TEST_CASE("Test DoublyLinkList default constructor", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<double> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DoublyLinkList constructor with allocator", "[DoublyLinkList]")
{
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DoublyLinkList constructor with given size .", "[DoublyLinkList]")
{
    size_t arr_size(100);
    double default_value(0.0);
    dsaa::DoublyLinkList<double> arr(arr_size);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr_size);
    for (auto i(arr.begin()); arr.end() != i; ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList constructor with given size and std::allocator.", "[DoublyLinkList]")
{
    size_t arr_size(100);
    double default_value(0.0);
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(arr_size);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr_size);
    for (auto i(arr.begin()); arr.end() != i; ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList constructor with given size and value.", "[DoublyLinkList]")
{
    size_t arr_size(100);
    double default_value(62.2);
    dsaa::DoublyLinkList<double> arr(arr_size, default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr_size);
    for (auto i(arr.begin()); arr.end() != i; ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList constructor with given size and value and std::allocator.", "[DoublyLinkList]")
{
    size_t arr_size(100);
    double default_value(612.2);
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(arr_size, default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr_size);
    for (auto i(arr.begin()); arr.end() != i; ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList constructor with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList constructor with std::initializer_list and std::allocator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList constructor with a pair of iterator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList constructor with a pair of iterator and std::allocator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList copy constructor.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr2(arr);

    REQUIRE(arr2.begin() != arr.begin());
    REQUIRE(arr2.cbegin() != arr.cbegin());
    REQUIRE(arr2.end() == arr.end());
    REQUIRE(arr2.cend() == arr.cend());

    REQUIRE(arr2.get_allocator() == arr.get_allocator());
    REQUIRE(arr2.empty() == arr.empty());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    while (arr_iter != arr.end())
        REQUIRE(*arr_iter++ == *arr2_iter++);
}

TEST_CASE("Test DoublyLinkList copy constructor with std::allocator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr2(arr, std::allocator<dsaa::DoublyLinkListNode<double>>());

    REQUIRE(arr2.begin() != arr.begin());
    REQUIRE(arr2.cbegin() != arr.cbegin());
    REQUIRE(arr2.end() == arr.end());
    REQUIRE(arr2.cend() == arr.cend());

    REQUIRE(arr2.get_allocator() == arr.get_allocator());
    REQUIRE(arr2.empty() == arr.empty());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    while (arr_iter != arr.end())
        REQUIRE(*arr_iter++ == *arr2_iter++);
}

TEST_CASE("Test DoublyLinkList move constructor.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr2(std::move(arr));

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == list.size());

    auto list_iter(list.begin());
    auto arr2_iter(arr2.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr2_iter++);
}

TEST_CASE("Test DoublyLinkList move constructor with std::allocator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};

    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr2(std::move(arr), std::allocator<dsaa::DoublyLinkListNode<double>>());

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == list.size());

    auto list_iter(list.begin());
    auto arr2_iter(arr2.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr2_iter++);
}

TEST_CASE("Test DoublyLinkList copy assignment.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr2;

    REQUIRE(iterator() == arr2.begin());
    REQUIRE(iterator() == arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(iterator() == arr2.cend());

    arr2 = arr;

    REQUIRE(arr2.begin() != arr.begin());
    REQUIRE(arr2.cbegin() != arr.cbegin());
    REQUIRE(arr2.end() == arr.end());
    REQUIRE(arr2.cend() == arr.cend());

    REQUIRE(arr2.get_allocator() == arr.get_allocator());
    REQUIRE(arr2.empty() == arr.empty());
    REQUIRE(arr2.size() == arr.size());

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    while (arr_iter != arr.end())
        REQUIRE(*arr_iter++ == *arr2_iter++);
}

TEST_CASE("Test DoublyLinkList move assignment.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr(list.begin(), list.end());
    dsaa::DoublyLinkList<double, std::allocator<dsaa::DoublyLinkListNode<double>>> arr2;

    REQUIRE(iterator() == arr2.begin());
    REQUIRE(iterator() == arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(iterator() == arr2.cend());

    arr2 = std::move(arr);

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    REQUIRE(iterator() != arr2.begin());
    REQUIRE(iterator() != arr2.cbegin());
    REQUIRE(iterator() == arr2.end());
    REQUIRE(iterator() == arr2.cend());

    REQUIRE(arr2.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr2.empty());
    REQUIRE(arr2.size() == list.size());

    auto list_iter(list.begin());
    auto arr2_iter(arr2.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr2_iter++);
}

TEST_CASE("Test DoublyLinkList with std::initializer_list assignment.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    arr = list;

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList assign method with a pair of iterator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    arr.assign(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList assign method with given size .", "[DoublyLinkList]")
{
    size_t arr_size(100);
    double default_value(0.0);
    dsaa::DoublyLinkList<double> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    arr.assign(arr_size);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr_size);
    for (auto i(arr.begin()); arr.end() != i; ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList with assign method with given size and value.", "[DoublyLinkList]")
{
    size_t arr_size(100);
    double default_value(62.2);
    dsaa::DoublyLinkList<double> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    arr.assign(arr_size, (default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == arr_size);
    for (auto i(arr.begin()); arr.end() != i; ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList assign method with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;

    REQUIRE(iterator() == arr.begin());
    REQUIRE(iterator() == arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(arr.empty());
    REQUIRE(0 == arr.size());

    arr.assign(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(arr.size() == list.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList insert_first method with one value.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    for (size_t i(0); i != size; ++i)
        arr.insert_first(default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_first method by moving parameter.", "[DoublyLinkList]")
{
    size_t size(1);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    for (size_t i(0); i != size; ++i)
        arr.insert_first(std::move(default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    REQUIRE(2256.6211656 == *arr.begin());
}

TEST_CASE("Test DoublyLinkList insert_first method with custom size.", "[DoublyLinkList]")
{
    size_t size(7);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    arr.insert_first(size, (default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_first method with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;
    arr.insert_first(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList insert_first method with a pair of iterator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;
    arr.insert_first(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList emplace_first method.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    for (size_t i(0); i != size; ++i)
        arr.emplace_first(default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_last method with one value.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    for (size_t i(0); i != size; ++i)
        arr.insert_last(default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_last method by moving parameter.", "[DoublyLinkList]")
{
    size_t size(1);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    for (size_t i(0); i != size; ++i)
        arr.insert_last(std::move(default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    REQUIRE(2256.6211656 == *arr.begin());
}

TEST_CASE("Test DoublyLinkList insert_last method with custom size.", "[DoublyLinkList]")
{
    size_t size(7);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    arr.insert_last(size, default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_last method with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;
    arr.insert_last(list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList insert_last method with a pair of iterator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr;
    arr.insert_last(list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList emplace_last method.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr;
    for (size_t i(0); i != size; ++i)
        arr.emplace_last(default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_before method with one value.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    for (size_t i(0); i != size; ++i)
        arr.insert_before(arr.begin(), default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_before method by moving parameter.", "[DoublyLinkList]")
{
    size_t size(1);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    for (size_t i(0); i != size; ++i)
        arr.insert_before(arr.begin(), std::move(default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    REQUIRE(2256.6211656 == *arr.begin());
}

TEST_CASE("Test DoublyLinkList insert_before method with custom size.", "[DoublyLinkList]")
{
    size_t size(7);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    arr.insert_before(arr.begin(), size, default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_before method with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr(list);
    arr.insert_before(arr.begin(), list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);

    list_iter = list.begin();
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList insert_before method with a pair of iterator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr(list);
    arr.insert_before(arr.begin(), list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
    list_iter = list.begin();
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList emplace_before method.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    for (size_t i(0); i != size; ++i)
        arr.emplace_before(arr.begin(), (default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_after method with one value.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    for (size_t i(0); i != size; ++i)
        arr.insert_after(arr.begin(), default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_after method by moving parameter.", "[DoublyLinkList]")
{
    size_t size(1);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    for (size_t i(0); i != size; ++i)
        arr.insert_after(arr.begin(), std::move(default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    REQUIRE(2256.6211656 == *arr.begin());
}

TEST_CASE("Test DoublyLinkList insert_after method with custom size.", "[DoublyLinkList]")
{
    size_t size(7);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    arr.insert_before(arr.begin(), size, (default_value));

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList insert_after method with std::initializer_list.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr(list);
    arr.insert_after(arr.begin(), list);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);

    list_iter = list.begin();
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList insert_after method with a pair of iterator.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6,
                                       6.6};
    dsaa::DoublyLinkList<double> arr(list);
    arr.insert_after(arr.begin(), list.begin(), list.end());

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * list.size() == arr.size());

    auto list_iter(list.begin());
    auto arr_iter(arr.begin());
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
    list_iter = list.begin();
    while (list_iter != list.end())
        REQUIRE(*list_iter++ == *arr_iter++);
}

TEST_CASE("Test DoublyLinkList emplace_after method.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);
    for (size_t i(0); i != size; ++i)
        arr.emplace_after(arr.begin(), default_value);

    REQUIRE(iterator() != arr.begin());
    REQUIRE(iterator() != arr.cbegin());
    REQUIRE(iterator() == arr.end());
    REQUIRE(iterator() == arr.cend());

    REQUIRE(arr.get_allocator() == std::allocator<dsaa::DoublyLinkListNode<double>>());
    REQUIRE(!arr.empty());
    REQUIRE(2 * size == arr.size());
    for (auto i(arr.begin()); i != arr.end(); ++i)
        REQUIRE(default_value == *i);
}

TEST_CASE("Test DoublyLinkList erase_first method.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);

    for (size_t i(0); i != 4; ++i)
        arr.erase_first();

    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DoublyLinkList erase_last method.", "[DoublyLinkList]")
{
    size_t size(4);
    double default_value(2256.6211656);
    dsaa::DoublyLinkList<double> arr(size, default_value);

    for (size_t i(0); i != 4; ++i)
        arr.erase_last();

    REQUIRE(0 == arr.size());
}

TEST_CASE("Test DoublyLinkList erase method.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{1.1,
                                       2.2,
                                       3.3,
                                       4.4,
                                       5.5,
                                       6.6,
                                       7.7,
                                       8.8,
                                       9.9,
                                       10.01};
    dsaa::DoublyLinkList<double> arr(list);

    arr.erase(arr.get_iterator(4));
    auto result(dsaa::linear_search(arr.begin(), arr.end(), (5.5)));

    REQUIRE(result == arr.end());
}

TEST_CASE("Test DoublyLinkList clean method.", "[DoublyLinkList]")
{
    std::initializer_list<double> list{1.1,
                                       2.2,
                                       3.3,
                                       4.4,
                                       5.5,
                                       6.6,
                                       7.7,
                                       8.8,
                                       9.9,
                                       10.01};
    dsaa::DoublyLinkList<double> arr(list);

    arr.clean();
    REQUIRE(0 == arr.size());
}