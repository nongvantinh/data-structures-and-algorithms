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
    node = nullptr;
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
    node = nullptr;
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
    node = nullptr;
}

// --------------------------------------------------------------

TEST_CASE("Test BinaryTree default constructor", "[BinaryTree]")
{
    dsaa::BinaryTree<TestObject<int>> tree;
    REQUIRE(nullptr == tree.root());
    REQUIRE(0 == tree.size());
}

TEST_CASE("Test BinaryTree default constructor with std::allocator", "[BinaryTree]")
{
    allocator_type allocator;
    dsaa::BinaryTree<TestObject<int>> tree(allocator);
    REQUIRE(nullptr == tree.root());
    REQUIRE(0 == tree.size());
}

TEST_CASE("Test BinaryTree copy constructor", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);
    dsaa::BinaryTree<TestObject<int>> tree2(tree);
    REQUIRE(nullptr != tree.root());
    REQUIRE(arg.size() == tree.size());
    REQUIRE(arg.size() == tree2.size());

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
    arr_iter = arg.begin();
    tree2.recursive_preorder_tree_walk(tree2.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                       { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree copy constructor with std::allocator", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);
    allocator_type allocator;
    dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
    REQUIRE(nullptr != tree.root());
    REQUIRE(arg.size() == tree.size());
    REQUIRE(arg.size() == tree2.size());

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
    arr_iter = arg.begin();
    tree2.recursive_preorder_tree_walk(tree2.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                       { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree move constructor", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);
    dsaa::BinaryTree<TestObject<int>> tree2(std::move(tree));

    REQUIRE(nullptr == tree.root());
    REQUIRE(0 == tree.size());

    REQUIRE(arg.size() == tree2.size());

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree move constructor with std::allocator", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);
    allocator_type allocator;
    dsaa::BinaryTree<TestObject<int>> tree2(std::move(tree), allocator);

    REQUIRE(nullptr == tree.root());
    REQUIRE(0 == tree.size());

    REQUIRE(arg.size() == tree2.size());

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree with std::initializer_list", "[BinaryTree]")
{
    SECTION("with just one value")
    {
        std::initializer_list<TestObject<int>> arg{6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        REQUIRE(nullptr != tree.root());
        REQUIRE(arg.size() == tree.size());

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with two values")
    {
        std::initializer_list<TestObject<int>> arg{6, 5};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        REQUIRE(nullptr != tree.root());
        REQUIRE(arg.size() == tree.size());

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with three values")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(arg.size() == tree.size());

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with four values")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(arg.size() == tree.size());

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with five values")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(arg.size() == tree.size());

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with five values")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::BinaryTree<TestObject<int>> tree2(tree, allocator);
        REQUIRE(nullptr != tree.root());
        REQUIRE(arg.size() == tree.size());

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }
}

TEST_CASE("Test BinaryTree copy assigment.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    std::initializer_list<TestObject<int>> arg2{2, 5, 7, 6, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);
    dsaa::BinaryTree<TestObject<int>> tree2(arg2);

    tree2 = tree;

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree2.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree move assigment.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    std::initializer_list<TestObject<int>> arg2{2, 5, 7, 6, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);
    dsaa::BinaryTree<TestObject<int>> tree2(arg2);

    tree2 = std::move(tree);

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree2.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree initializer_list assigment.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    std::initializer_list<TestObject<int>> arg2{2, 5, 7, 6, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    tree = arg2;

    auto arr_iter(arg2.begin());
    tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree iterative_minimum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(2) == tree.iterative_minimum(tree.root())->value());
}

TEST_CASE("Test BinaryTree iterative_maximum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(8) == tree.iterative_maximum(tree.root())->value());
}

TEST_CASE("Test BinaryTree recursive_minimum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(2) == tree.recursive_minimum(tree.root())->value());
}

TEST_CASE("Test BinaryTree recursive_maximum.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(8) == tree.recursive_maximum(tree.root())->value());
}

TEST_CASE("Test BinaryTree successor.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(7) == tree.successor(tree.root())->value());
    auto min(tree.iterative_minimum(tree.root()));
    REQUIRE(TestObject<int>(6) == tree.successor(min->parent()->right())->value());
}

TEST_CASE("Test BinaryTree predecessor.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(5) == tree.predecessor(tree.root())->value());
    auto min(tree.iterative_minimum(tree.root()));
    REQUIRE(nullptr == tree.predecessor(min));
}

TEST_CASE("Test BinaryTree recursive_search.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(5) == tree.recursive_search(tree.root(), TestObject<int>(5))->value());
    REQUIRE(nullptr == tree.recursive_search(tree.root(), TestObject<int>(4)));
}

TEST_CASE("Test BinaryTree iterative_search.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 7, 2, 5, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    REQUIRE(TestObject<int>(5) == tree.iterative_search(tree.root(), TestObject<int>(5))->value());
    REQUIRE(nullptr == tree.recursive_search(tree.root(), TestObject<int>(4)));
}

TEST_CASE("Test BinaryTree recursive_preorder_tree_walk.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    auto arr_iter(arg.begin());
    tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                      { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree recursive_inorder_tree_walk.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    std::initializer_list<TestObject<int>> arg2{2, 5, 5, 6, 7, 8};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    auto arr_iter(arg2.begin());
    tree.recursive_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                     { REQUIRE(*arr_iter++ == value->value()); });
}

TEST_CASE("Test BinaryTree recursive_postorder_tree_walk.", "[BinaryTree]")
{
    std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
    std::initializer_list<TestObject<int>> arg2{2, 5, 5, 8, 7, 6};
    dsaa::BinaryTree<TestObject<int>> tree(arg);

    auto arr_iter(arg2.begin());
    tree.recursive_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                       { REQUIRE(*arr_iter++ == value->value()); });
}

/////////////////////////////////////////////////
TEST_CASE("Test BinaryTree iterative_preorder_tree_walk.", "[BinaryTree]")
{
    SECTION("with empty tree.")
    {
        std::initializer_list<TestObject<int>> arg;
        std::initializer_list<TestObject<int>> arg2;
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 1 element.")
    {
        std::initializer_list<TestObject<int>> arg{6};
        std::initializer_list<TestObject<int>> arg2{6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }
    SECTION("with 2 element: heavy on the left.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5};
        std::initializer_list<TestObject<int>> arg2{6, 5};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 2 element: heavy on the right.")
    {
        std::initializer_list<TestObject<int>> arg{6, 7};
        std::initializer_list<TestObject<int>> arg2{6, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 3 element: balanced tree.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 7};
        std::initializer_list<TestObject<int>> arg2{6, 5, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with normal tree.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
        std::initializer_list<TestObject<int>> arg2{6, 5, 2, 5, 7, 8};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }
}

TEST_CASE("Test BinaryTree iterative_inorder_tree_walk.", "[BinaryTree]")
{
    SECTION("with empty tree.")
    {
        std::initializer_list<TestObject<int>> arg;
        std::initializer_list<TestObject<int>> arg2;
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                         { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 1 element.")
    {
        std::initializer_list<TestObject<int>> arg{6};
        std::initializer_list<TestObject<int>> arg2{6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                         { REQUIRE(*arr_iter++ == value->value()); });
    }
    SECTION("with 2 element: heavy on the left.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5};
        std::initializer_list<TestObject<int>> arg2{5, 6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                         { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 2 element: heavy on the right.")
    {
        std::initializer_list<TestObject<int>> arg{6, 7};
        std::initializer_list<TestObject<int>> arg2{6, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                         { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 3 element: balanced tree.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 7};
        std::initializer_list<TestObject<int>> arg2{5, 6, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                         { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with normal tree.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
        std::initializer_list<TestObject<int>> arg2{2, 5, 5, 6, 7, 8};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_inorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                         { REQUIRE(*arr_iter++ == value->value()); });
    }
}

TEST_CASE("Test BinaryTree iterative_postorder_tree_walk.", "[BinaryTree]")
{
    SECTION("with empty tree.")
    {
        std::initializer_list<TestObject<int>> arg;
        std::initializer_list<TestObject<int>> arg2;
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                           { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 1 element.")
    {
        std::initializer_list<TestObject<int>> arg{6};
        std::initializer_list<TestObject<int>> arg2{6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                           { REQUIRE(*arr_iter++ == value->value()); });
    }
    SECTION("with 2 element: heavy on the left.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5};
        std::initializer_list<TestObject<int>> arg2{5, 6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                           { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 2 element: heavy on the right.")
    {
        std::initializer_list<TestObject<int>> arg{6, 7};
        std::initializer_list<TestObject<int>> arg2{7, 6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                           { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with 3 element: balanced tree.")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 7};
        std::initializer_list<TestObject<int>> arg2{5, 7, 6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                           { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("with normal tree.")
    {
        std::initializer_list<TestObject<int>> arg{6, 4, 2, 5, 7, 8};
        std::initializer_list<TestObject<int>> arg2{2, 5, 4, 8, 7, 6};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        auto arr_iter(arg2.begin());
        tree.iterative_postorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                           { REQUIRE(*arr_iter++ == value->value()); });
    }
}
//////////////////////////////////////////////////////
TEST_CASE("Test BinaryTree insert.", "[BinaryTree]")
{
    SECTION("insert on empty tree")
    {
        std::initializer_list<TestObject<int>> arg{6};
        dsaa::BinaryTree<TestObject<int>> tree;

        tree.insert(6);

        auto arr_iter(arg.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("insert on binary tree that has 1 child")
    {
        std::initializer_list<TestObject<int>> arg{6};
        std::initializer_list<TestObject<int>> arg2{6, 5};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        tree.insert(5);

        auto arr_iter(arg2.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("insert on binary tree that has 2 child")
    {
        std::initializer_list<TestObject<int>> arg{6, 5};
        std::initializer_list<TestObject<int>> arg2{6, 5, 7};
        dsaa::BinaryTree<TestObject<int>> tree(arg);

        tree.insert(7);

        auto arr_iter(arg2.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }
}

TEST_CASE("Test BinaryTree erase.", "[BinaryTree]")
{
    SECTION("erase with no left child")
    {
        std::initializer_list<TestObject<int>> arg{6, 7, 8};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        tree.erase(tree.root());

        auto arr_iter(arg.begin());
        ++arr_iter;
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }
    SECTION("erase with no right child")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5};
        dsaa::BinaryTree<TestObject<int>> tree(arg);
        tree.erase(tree.root());

        auto arr_iter(arg.begin());
        ++arr_iter;
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("erase with two children")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
        std::initializer_list<TestObject<int>> arg2{7, 5, 2, 5, 8};

        dsaa::BinaryTree<TestObject<int>> tree(arg);
        auto node(tree.root());
        tree.erase(node);

        auto arr_iter(arg2.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }

    SECTION("erase with two children")
    {
        std::initializer_list<TestObject<int>> arg{6, 5, 2, 5, 7, 8};
        std::initializer_list<TestObject<int>> arg2{6, 5, 2, 7, 8};

        dsaa::BinaryTree<TestObject<int>> tree(arg);
        auto node(tree.root()->left());
        tree.erase(node);

        auto arr_iter(arg2.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&arr_iter](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*arr_iter++ == value->value()); });
    }
}
