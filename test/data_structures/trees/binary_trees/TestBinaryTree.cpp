#include "Catch2/Catch.hpp"
#include "trees/binary_trees/BinaryTree.h"
#include "algorithms/Random.h"
#include "test/TestObject.h"
#include "arrays/DynamicArray.h"
#include "algorithms/Generic.h"

using value_type = TestObject<int>;
using allocator_type = std::allocator<dsaa::BinaryTreeNode<value_type>>;
using reference = value_type &;
using const_reference = value_type const &;
using pointer = dsaa::BinaryTreeNode<value_type> *;
using const_pointer = dsaa::BinaryTreeNode<value_type> const *;
using difference_type = std::ptrdiff_t;
using size_type = size_t;

TEST_CASE("Test BinaryTree BinaryTreeNode default constructor.", "[BinaryTree]")
{
    dsaa::BinaryTreeNode<TestObject<int>> *node = new dsaa::BinaryTreeNode<TestObject<int>>();

    REQUIRE(TestObject<int>() == node->value());
    REQUIRE(TestObject<int>() == **node);
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
}

TEST_CASE("Test BinaryTree BinaryTreeNode constructor with value.", "[BinaryTree]")
{
    TestObject<int> value(6734);
    dsaa::BinaryTreeNode<TestObject<int>> *node = new dsaa::BinaryTreeNode<TestObject<int>>(value);

    REQUIRE(value == **node);
    REQUIRE(value == node->value());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
}

TEST_CASE("Test BinaryTree BinaryTreeNode constructor by move value.", "[BinaryTree]")
{
    TestObject<int> value(6734);
    TestObject<int> value2(value);
    dsaa::BinaryTreeNode<TestObject<int>> *node = new dsaa::BinaryTreeNode<TestObject<int>>(std::move(value));

    REQUIRE(TestObject<int>() == value);
    REQUIRE(value2 == **node);
    REQUIRE(value2 == node->value());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
}

TEST_CASE("Test BinaryTree default constructor", "[BinaryTree]")
{
    dsaa::BinaryTree<TestObject<int>> tree;
    REQUIRE(nullptr == tree.root());
    REQUIRE(0 == tree.size());
}

TEST_CASE("Test BinaryTree default constructor with std::allocator", "[BinaryTree]")
{
    std::allocator<TestObject<int>> allocator;
    dsaa::BinaryTree<TestObject<int>> tree(allocator);
    REQUIRE(nullptr == tree.root());
    REQUIRE(0 == tree.size());

    TestObject<int> value1(1);
    TestObject<int> value2(2);
    TestObject<int> value3(3);
    TestObject<int> value4(4);
}

TEST_CASE("Test BinaryTree copy constructor", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(l);
    dsaa::BinaryTree<TestObject<int>> tree2(tree);
    REQUIRE(nullptr != tree.root());
    REQUIRE(l.size() == tree.size());
    REQUIRE(l.size() == tree2.size());
}

TEST_CASE("Test BinaryTree copy constructor with std::allocator", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(l);
    std::allocator<TestObject<int>> allocator;
    dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
    REQUIRE(nullptr != tree.root());
    REQUIRE(l.size() == tree.size());
    REQUIRE(l.size() == tree2.size());
}

TEST_CASE("Test BinaryTree with std::initializer_list", "[BinaryTree]")
{
    SECTION("with just one value")
    {
        std::initializer_list<TestObject<int>> l{6};
        dsaa::BinaryTree<TestObject<int>> tree{l};
        REQUIRE(nullptr != tree.root());
        REQUIRE(l.size() == tree.size());
    }

    SECTION("with two values")
    {
        std::initializer_list<TestObject<int>> l{6, 5};
        dsaa::BinaryTree<TestObject<int>> tree{l};
        REQUIRE(nullptr != tree.root());
        REQUIRE(l.size() == tree.size());
    }

    SECTION("with three values")
    {
        std::initializer_list<TestObject<int>> l{6, 5, 7};
        dsaa::BinaryTree<TestObject<int>> tree{l};
        std::allocator<TestObject<int>> allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(l.size() == tree.size());
    }

    SECTION("with four values")
    {
        std::initializer_list<TestObject<int>> l{6, 5, 7, 2};
        dsaa::BinaryTree<TestObject<int>> tree{l};
        std::allocator<TestObject<int>> allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(l.size() == tree.size());
    }

    SECTION("with five values")
    {
        std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5};
        dsaa::BinaryTree<TestObject<int>> tree{l};
        std::allocator<TestObject<int>> allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(l.size() == tree.size());
    }

    SECTION("with five values")
    {
        std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
        dsaa::BinaryTree<TestObject<int>> tree{l};
        std::allocator<TestObject<int>> allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(l.size() == tree.size());
    }
}

TEST_CASE("Test BinaryTree copy assigment.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};
    std::allocator<TestObject<int>> allocator;
    dsaa::BinaryTree<TestObject<int>> tree2;

    dsaa::DynamicArray<TestObject<int>> arr;
    dsaa::DynamicArray<TestObject<int>> arr2;
    arr.reserve(tree.size());
    arr2.reserve(tree.size());

    tree2 = tree;
    REQUIRE(tree.root() != tree2.root());

    REQUIRE(nullptr != tree2.root());
    REQUIRE(l.size() == tree2.size());

    dsaa::recursive_postorder_tree_walk(tree.root(), [&arr](pointer &p_node)
                                        { arr.insert_last(p_node->value()); });

    dsaa::recursive_postorder_tree_walk(tree2.root(), [&arr2](pointer &p_node)
                                        { arr2.insert_last(p_node->value()); });

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test BinaryTree initializer_list assigment.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};
    std::allocator<TestObject<int>> allocator;
    dsaa::BinaryTree<TestObject<int>> tree2({5, 6, 7, 8, 9});

    dsaa::DynamicArray<TestObject<int>> arr;
    dsaa::DynamicArray<TestObject<int>> arr2;
    arr.reserve(tree.size());
    arr2.reserve(tree.size());

    dsaa::recursive_postorder_tree_walk(tree.root(), [&arr](pointer &p_node)
                                        { arr.insert_last(p_node->value()); });

    tree2 = l;

    dsaa::recursive_postorder_tree_walk(tree2.root(), [&arr2](pointer &p_node)
                                        { arr2.insert_last(p_node->value()); });

    auto arr_iter(arr.begin());
    auto arr2_iter(arr2.begin());
    for (; arr.end() != arr_iter; ++arr_iter, ++arr2_iter)
        REQUIRE(*arr_iter == *arr2_iter);
}

TEST_CASE("Test BinaryTree iterative_minimum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(2) == tree.iterative_minimum(tree.root())->value());
}

TEST_CASE("Test BinaryTree iterative_maximum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(8) == tree.iterative_maximum(tree.root())->value());
}

TEST_CASE("Test BinaryTree recursive_minimum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(2) == tree.recursive_minimum(tree.root())->value());
}

TEST_CASE("Test BinaryTree recursive_maximum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(8) == tree.recursive_maximum(tree.root())->value());
}

TEST_CASE("Test BinaryTree successor.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(7) == tree.successor(tree.root())->value());
}

TEST_CASE("Test BinaryTree predecessor.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(5) == tree.predecessor(tree.root())->value());
}

TEST_CASE("Test BinaryTree recursive_search.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(5) == tree.recursive_search(tree.root(), TestObject<int>(5))->value());
}

TEST_CASE("Test BinaryTree iterative_search.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> l{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree{l};

    REQUIRE(TestObject<int>(5) == tree.iterative_search(tree.root(), TestObject<int>(5))->value());
}