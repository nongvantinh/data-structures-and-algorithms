#ifndef DSAA_TEST_ARRAY_H
#define DSAA_TEST_ARRAY_H

#include "Catch2/Catch.hpp"
#include "arrays/Array.h"
#include "test/Tester.h"
#include "test/Test.h"
#include "algorithms/Search.h"
#include <memory>
#include <limits>
using iterator = dsaa::Array<tester>::iterator;
TEST_CASE("Test Array constructor", "[array]")
{
    SECTION("Test Array with default constructor")
    {
        dsaa::Array<tester> arr;

        REQUIRE(iterator() == arr.begin());
        REQUIRE(iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(iterator() == arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() == arr.data());
        REQUIRE(arr.empty());
        REQUIRE(0 == arr.capacity());
        REQUIRE(0 == arr.size());
    }

    SECTION("Test Array with default constructor and allocator.")
    {
        dsaa::Array<tester, std::allocator<tester>> arr;

        REQUIRE(iterator() == arr.begin());
        REQUIRE(iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(iterator() == arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() == arr.data());
        REQUIRE(arr.empty());
        REQUIRE(0 == arr.capacity());
        REQUIRE(0 == arr.size());
    }

    SECTION("Test constructor with given size.")
    {
        size_t arr_size{100};
        dsaa::Array<tester> arr(arr_size);

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == arr_size);
        REQUIRE(arr.size() == arr_size);
        for (size_t i{0}; i < arr_size; ++i)
            REQUIRE(0.0 == arr[i]);
    }

    SECTION("Test constructor with given size and allocator.")
    {
        size_t arr_size{100};
        dsaa::Array<tester, std::allocator<tester>> arr(arr_size);

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == arr_size);
        REQUIRE(arr.size() == arr_size);
        for (size_t i{0}; i < arr_size; ++i)
            REQUIRE(0.0 == arr[i]);
    }

    SECTION("Test constructor with given size and value.")
    {
        size_t arr_size{100};
        dsaa::Array<tester> arr(arr_size, 4.4);

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == arr_size);
        REQUIRE(arr.size() == arr_size);
        for (size_t i{0}; i < arr_size; ++i)
            REQUIRE(4.4 == arr[i]);
    }

    SECTION("Test constructor with given size, value and allocator.")
    {
        size_t arr_size{100};
        dsaa::Array<tester, std::allocator<tester>> arr(arr_size, 4.4);

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == arr_size);
        REQUIRE(arr.size() == arr_size);
        for (size_t i{0}; i < arr_size; ++i)
            REQUIRE(4.4 == arr[i]);
    }

    SECTION("Test constructor with std::initializer_list.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr{list};

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == list.size());
        REQUIRE(arr.size() == list.size());
        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }

    SECTION("Test constructor with std::initializer_list and std::allocator.")
    {
        std::initializer_list<tester> list{1.1,
                                           2.2,
                                           3.3,
                                           4.4,
                                           5.5,
                                           6.6,
                                           7.7,
                                           8.7,
                                           9.8,
                                           10.6};
        dsaa::Array<tester, std::allocator<tester>> arr{list};

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == list.size());
        REQUIRE(arr.size() == list.size());
        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }

    SECTION("Test constructor with given pair IIterator.")
    {
        std::initializer_list<tester> list{1.1,
                                           2.2,
                                           3.3,
                                           4.4,
                                           5.5,
                                           6.6,
                                           7.7,
                                           8.7,
                                           9.8,
                                           10.6};
        dsaa::Array<tester> arr(list.begin(), list.end());

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() >= list.size());
        REQUIRE(arr.size() == list.size());
        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }

    SECTION("Test constructor with given pair IIterator and std::allocator.")
    {
        std::initializer_list<tester> list{1.1,
                                           2.2,
                                           3.3,
                                           4.4,
                                           5.5,
                                           6.6,
                                           7.7,
                                           8.7,
                                           9.8,
                                           10.6};
        dsaa::Array<tester, std::allocator<tester>> arr(list.begin(), list.end());

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() >= list.size());
        REQUIRE(arr.size() == list.size());
        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }

    SECTION("Test copy constructor.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr(list.begin(), list.end());
        dsaa::Array<tester> arr2(arr);

        REQUIRE(iterator() != arr2.begin());
        REQUIRE(iterator() != arr2.cbegin());
        REQUIRE(iterator() != arr2.end());
        REQUIRE(iterator() != arr2.cend());

        REQUIRE(arr2.get_allocator() == arr.get_allocator());
        REQUIRE(iterator().content() != arr2.data());
        REQUIRE(!arr2.empty());
        REQUIRE(arr2.capacity() == arr.size());
        REQUIRE(arr2.size() == arr.size());
        auto arr_iter{arr.begin()};
        auto arr2_iter{arr2.begin()};
        while (arr_iter != arr.end())
            REQUIRE(*arr_iter++ == *arr2_iter++);
    }

    SECTION("Test copy constructor and std::allocator.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr(list.begin(), list.end());
        dsaa::Array<tester, std::allocator<tester>> arr2(arr);

        REQUIRE(iterator() != arr2.begin());
        REQUIRE(iterator() != arr2.cbegin());
        REQUIRE(iterator() != arr2.end());
        REQUIRE(iterator() != arr2.cend());

        REQUIRE(arr2.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr2.data());
        REQUIRE(!arr2.empty());
        REQUIRE(arr2.capacity() == arr.size());
        REQUIRE(arr2.size() == arr.size());
        auto arr_iter{arr.begin()};
        auto arr2_iter{arr2.begin()};
        while (arr_iter != arr.end())
            REQUIRE(*arr_iter++ == *arr2_iter++);
    }

    SECTION("Test move constructor.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr(list);
        size_t capacity(arr.capacity()), size(arr.size());
        dsaa::Array<tester> arr2(std::move(arr));

        REQUIRE(iterator() == arr.begin());
        REQUIRE(iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(iterator() == arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() == arr.data());
        REQUIRE(arr.empty());
        REQUIRE(0 == arr.capacity());
        REQUIRE(0 == arr.size());

        REQUIRE(iterator() != arr2.begin());
        REQUIRE(iterator() != arr2.cbegin());
        REQUIRE(iterator() != arr2.end());
        REQUIRE(iterator() != arr2.cend());

        REQUIRE(arr2.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr2.data());
        REQUIRE(!arr2.empty());
        REQUIRE(arr2.capacity() == capacity);
        REQUIRE(arr2.size() == size);

        auto list_iter{list.begin()};
        auto arr2_iter{arr2.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr2_iter++);
    }

    SECTION("Test move constructor with allocator.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr(list);
        size_t capacity(arr.capacity()), size(arr.size());
        dsaa::Array<tester> arr2(std::move(arr), std::allocator<tester>());

        REQUIRE(iterator() == arr.begin());
        REQUIRE(iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(iterator() == arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() == arr.data());
        REQUIRE(arr.empty());
        REQUIRE(0 == arr.capacity());
        REQUIRE(0 == arr.size());

        REQUIRE(iterator() != arr2.begin());
        REQUIRE(iterator() != arr2.cbegin());
        REQUIRE(iterator() != arr2.end());
        REQUIRE(iterator() != arr2.cend());

        REQUIRE(arr2.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr2.data());
        REQUIRE(!arr2.empty());
        REQUIRE(arr2.capacity() == capacity);
        REQUIRE(arr2.size() == size);

        auto list_iter{list.begin()};
        auto arr2_iter{arr2.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr2_iter++);
    }

    SECTION("Test copy assignment.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr(list);
        dsaa::Array<tester> arr2;
        arr2 = arr;

        REQUIRE(iterator() != arr2.begin());
        REQUIRE(iterator() != arr2.cbegin());
        REQUIRE(iterator() != arr2.end());
        REQUIRE(iterator() != arr2.cend());

        REQUIRE(arr2.get_allocator() == arr.get_allocator());
        REQUIRE(iterator().content() != arr2.data());
        REQUIRE(!arr2.empty());
        REQUIRE(arr2.capacity() == arr.size());
        REQUIRE(arr2.size() == arr.size());
        auto arr_iter{arr.begin()};
        auto arr2_iter{arr2.begin()};
        while (arr_iter != arr.end())
            REQUIRE(*arr_iter++ == *arr2_iter++);
    }

    SECTION("Test move assigment.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr(list);
        size_t capacity(arr.capacity()), size(arr.size());
        dsaa::Array<tester> arr2;

        arr2 = std::move(arr);

        REQUIRE(iterator() == arr.begin());
        REQUIRE(iterator() == arr.cbegin());
        REQUIRE(iterator() == arr.end());
        REQUIRE(iterator() == arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() == arr.data());
        REQUIRE(arr.empty());
        REQUIRE(0 == arr.capacity());
        REQUIRE(0 == arr.size());

        REQUIRE(iterator() != arr2.begin());
        REQUIRE(iterator() != arr2.cbegin());
        REQUIRE(iterator() != arr2.end());
        REQUIRE(iterator() != arr2.cend());

        REQUIRE(arr2.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr2.data());
        REQUIRE(!arr2.empty());
        REQUIRE(arr2.capacity() == capacity);
        REQUIRE(arr2.size() == size);

        auto list_iter{list.begin()};
        auto arr2_iter{arr2.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr2_iter++);
    }

    SECTION("Test copy assignment using std::initilizer_list.")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        dsaa::Array<tester> arr;
        arr = list;

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == list.size());
        REQUIRE(arr.size() == list.size());

        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }
}

TEST_CASE("Test Array assign methods", "[array]")
{
    dsaa::Array<tester> arr;
    SECTION("Test assign method using pair IIterator")
    {
        std::initializer_list<tester> list{6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6,
                                           6.6};
        arr.assign(list.begin(), list.end());

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() >= list.size());
        REQUIRE(arr.size() == list.size());

        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }

    SECTION("Test assign method with size and value")
    {
        size_t size{100};
        double value{7.3};
        arr.assign(size, value);

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == size);
        REQUIRE(arr.size() == size);

        auto arr_iter{arr.begin()};
        while (arr_iter != arr.end())
            REQUIRE(*arr_iter++ == value);
    }

    SECTION("Test assign method using std::initializer_list")
    {
        std::initializer_list<tester> list{2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4};
        arr.assign(list);

        REQUIRE(iterator() != arr.begin());
        REQUIRE(iterator() != arr.cbegin());
        REQUIRE(iterator() != arr.end());
        REQUIRE(iterator() != arr.cend());

        REQUIRE(arr.get_allocator() == std::allocator<tester>());
        REQUIRE(iterator().content() != arr.data());
        REQUIRE(!arr.empty());
        REQUIRE(arr.capacity() == list.size());
        REQUIRE(arr.size() == list.size());

        auto list_iter{list.begin()};
        auto arr_iter{arr.begin()};
        while (list_iter != list.end())
            REQUIRE(*list_iter++ == *arr_iter++);
    }
}

TEST_CASE("Test Array reserve.", "[array]")
{
    dsaa::Array<tester> arr;

    SECTION("Array reserve doesn't change capacity")
    {
        size_t new_capacity{0};
        size_t old_capacity{arr.capacity()};
        size_t old_size{arr.size()};
        arr.reserve(new_capacity);
        REQUIRE(arr.capacity() == new_capacity);
        REQUIRE(arr.capacity() == old_capacity);
        REQUIRE(arr.size() == old_size);
    }

    SECTION("Array reserve change capacity")
    {
        size_t new_capacity{75};
        size_t old_size{arr.size()};
        arr.reserve(new_capacity);
        REQUIRE(arr.capacity() == new_capacity);
        REQUIRE(arr.size() == old_size);
    }
}

TEST_CASE("Test Array resizing.", "[array]")
{
    dsaa::Array<tester> arr;

    SECTION("resize to 0")
    {
        size_t new_size{0};
        size_t old_capacity{arr.capacity()};
        arr.resize(new_size);
        REQUIRE(arr.capacity() == old_capacity);
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Array resize change capacity and size")
    {
        size_t new_size{21};
        arr.resize(new_size);
        REQUIRE(arr.capacity() == new_size);
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Array resize change capacity and size")
    {
        size_t new_size{111};
        arr.resize(new_size);
        REQUIRE(arr.capacity() == new_size);
        REQUIRE(arr.size() == new_size);
    }

    SECTION("Array resize change size but not capacity")
    {
        size_t new_capacity{100};
        arr.reserve(new_capacity);

        SECTION("Resize to smaller size.")
        {
            size_t new_size{34};
            size_t old_capacity{arr.capacity()};
            arr.resize(new_size);
            REQUIRE(arr.capacity() == old_capacity);
            REQUIRE(arr.size() == new_size);
        }

        SECTION("Resize to larger size but not larger capacity")
        {
            size_t new_size{85};
            size_t old_capacity{arr.capacity()};
            arr.resize(new_size);
            REQUIRE(arr.capacity() == old_capacity);
            REQUIRE(arr.size() == new_size);
        }
    }
}

TEST_CASE("Array insert last methods", "[array]")
{
    dsaa::Array<tester> arr;
    SECTION("Insert last with parameter value")
    {
        arr.insert_last(92.2);
        arr.insert_last(92.2);
        arr.insert_last(92.2);
        REQUIRE(arr.capacity() >= 3);
        REQUIRE(arr.size() == 3);
    }

    SECTION("Insert last by move value")
    {
        tester value1{92.1}, value2{23.1}, value3{73.1};
        arr.insert_last(std::move(value1));
        arr.insert_last(std::move(value2));
        arr.insert_last(std::move(value3));
        REQUIRE(arr.capacity() >= 3);
        REQUIRE(arr.size() == 3);

        REQUIRE(value1 == tester(0.0));
        REQUIRE(value2 == tester(0.0));
        REQUIRE(value3 == tester(0.0));
    }

    SECTION("Insert last by a mount of size and value")
    {
        size_t size(99);
        double value(21.1);
        arr.insert_last(size, value);
        REQUIRE(arr.capacity() >= size);
        REQUIRE(arr.size() == size);
    }

    SECTION("Insert last by std::initializer_list ")
    {
        std::initializer_list<tester> list{2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4};

        arr.insert_last(list);
        REQUIRE(arr.capacity() == list.size());
        REQUIRE(arr.size() == list.size());

        auto list_iter(list.begin());
        for(auto iter(arr.begin()); iter != arr.end(); ++iter, ++list_iter)
            REQUIRE(*iter == *list_iter);
    }

    SECTION("Insert last by a pair of IIterator")
    {
        std::initializer_list<tester> list{2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4};

        arr.insert_last(list.begin(), list.end());
        REQUIRE(arr.capacity() == list.size());
        REQUIRE(arr.size() == list.size());
                auto list_iter(list.begin());
        for(auto iter(arr.begin()); iter != arr.end(); ++iter, ++list_iter)
            REQUIRE(*iter == *list_iter);

    }
}

TEST_CASE("Array insert at methods", "[array]")
{
    dsaa::Array<tester> arr(10);
    SECTION("Insert at with parameter value")
    {
        size_t old_size{arr.size()};

        arr.insert_at(arr.begin(), 93.8);
        arr.insert_at(arr.begin(), 93.8);
        arr.insert_at(arr.begin(), 93.8);
        REQUIRE(arr.capacity() >= 13);
        REQUIRE(arr.size() == 13);

        REQUIRE(arr.capacity() >= old_size + 3);
        REQUIRE(arr.size() == old_size + 3);
    }

    SECTION("Insert at by move value")
    {
        tester value1{92.1}, value2{23.1}, value3{73.1};
        size_t old_size{arr.size()};
        arr.insert_at(arr.begin(), std::move(value1));
        arr.insert_at(arr.begin(), std::move(value2));
        arr.insert_at(arr.begin(), std::move(value3));
        REQUIRE(arr.capacity() >= 13);
        REQUIRE(arr.size() == 13);

        REQUIRE(value1 == tester(0.0));
        REQUIRE(value2 == tester(0.0));
        REQUIRE(value3 == tester(0.0));

        REQUIRE(arr.capacity() >= old_size + 3);
        REQUIRE(arr.size() == old_size + 3);
    }

    SECTION("Insert at by a mount of size and value")
    {
        size_t size(100);
        size_t old_size{arr.size()};
        tester value(21.1);
        arr.insert_at(arr.begin(), size, value);
        REQUIRE(arr.capacity() >= old_size + size);
        REQUIRE(arr.size() == old_size + size);

        for (size_t i(0); i < size; ++i)
            REQUIRE(arr[i] == value);
    }

    SECTION("Insert at by a std::initializer_list")
    {
        size_t old_size{arr.size()};
        std::initializer_list<tester> list{2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4};

        arr.insert_at(arr.begin(), list);
        REQUIRE(arr.capacity() >= old_size + list.size());
        REQUIRE(arr.size() == old_size + list.size());
        size_t index{0};
        for (auto i(list.begin()); i != list.end(); ++i, ++index)
            REQUIRE(arr[index] == *i);
    }

    SECTION("Insert at by a pair of IIterator")
    {
        size_t old_size{arr.size()};
        std::initializer_list<tester> list{2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4,
                                           2.4};

        arr.insert_at(arr.begin(), list.begin(), list.end());
        REQUIRE(arr.capacity() >= old_size + list.size());
        REQUIRE(arr.size() == old_size + list.size());
        size_t index{0};
        for (auto i(list.begin()); i != list.end(); ++i, ++index)
            REQUIRE(arr[index] == *i);
    }
}

TEST_CASE("Array erase at method", "[array]")
{
    dsaa::Array<tester> arr(100);

    for (size_t i(0); i != arr.size(); ++i)
    {
        arr[i] = i;
    }

    size_t index(75);
    tester value(*arr.get_iterator(index));
    arr.erase_at(arr.get_iterator(index));

    auto result = dsaa::linear_search(arr.begin(), arr.end(), value);
    REQUIRE(result == arr.end());
}

TEST_CASE("Array erase with a pair iterator", "[array]")
{
    dsaa::Array<tester> arr(100);

    for (size_t i(0); i != arr.size(); ++i)
    {
        arr[i] = i;
    }

    arr.erase(arr.begin(), arr.end());
    REQUIRE(arr.size() == 0);
}
TEST_CASE("Array erase last", "[array]")
{
    dsaa::Array<tester> arr(100);

    for (size_t i(0); i != arr.size(); ++i)
    {
        arr[i] = i;
    }

    auto value(arr.last());
    arr.erase_last();
    REQUIRE(arr.last() != value);
}

TEST_CASE("Array clear function", "[array]")
{
    dsaa::Array<tester> arr(100);

    for (size_t i(0); i != arr.size(); ++i)
    {
        arr[i] = i;
    }

    auto value(arr.last());
    arr.clear();
    REQUIRE(arr.size() == 0);
}

#endif // !DSAA_TEST_ARRAY_H