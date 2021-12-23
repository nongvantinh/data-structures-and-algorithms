#include "Catch2/Catch.hpp"
#include "algorithms/Random.h"
#include "test/TestObject.h"
#include "arrays/DynamicArray.h"
#include "algorithms/Generic.h"
#include "trees/binary_trees/RedBlackTree.h"
#include "algorithms/Sort.h"
#include <vector>
#include <initializer_list>

using value_type = TestObject<int>;
using allocator_type = std::allocator<dsaa::RedBlackTreeNode<value_type>>;
using reference = value_type &;
using const_reference = value_type const &;
using pointer = dsaa::RedBlackTreeNode<value_type> *;
using const_pointer = dsaa::RedBlackTreeNode<value_type> const *;
using difference_type = std::ptrdiff_t;
using size_type = size_t;

TEST_CASE("Test RedBlackTree RedBlackTreeNode default constructor.", "[RedBlackTree]")
{
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();

    REQUIRE(TestObject<int>() == node->value());
    REQUIRE(TestObject<int>() == **node);
    REQUIRE(false == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode constructor with value.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, value);

    REQUIRE(value == node->value());
    REQUIRE(value == **node);
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode constructor by move value.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    TestObject<int> value2(value);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, std::move(value));

    REQUIRE(TestObject<int>() == value);
    REQUIRE(value2 == **node);
    REQUIRE(value2 == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode constructor with full initialization.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, value, nullptr, nullptr, nullptr);

    REQUIRE(value == **node);
    REQUIRE(value == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode constructor with full initialization by move value.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    TestObject<int> value2(value);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, std::move(value), nullptr, nullptr, nullptr);

    REQUIRE(TestObject<int>() == value);
    REQUIRE(value2 == **node);
    REQUIRE(value2 == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode copy constructor.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, value, nullptr, nullptr, nullptr);

    REQUIRE(value == **node);
    REQUIRE(value == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    dsaa::RedBlackTreeNode<TestObject<int>> *node2 = new dsaa::RedBlackTreeNode<TestObject<int>>(*node);

    REQUIRE(*node2 == *node);
    REQUIRE(**node2 == **node);
    REQUIRE(node2->value() == node->value());
    REQUIRE(node2->is_red() == node->is_red());
    REQUIRE(node2->parent() == node->parent());
    REQUIRE(node2->left() == node->left());
    REQUIRE(node2->right() == node->right());

    delete node;
    delete node2;
    node = node2 = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode move constructor.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, value, nullptr, nullptr, nullptr);

    REQUIRE(value == **node);
    REQUIRE(value == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    dsaa::RedBlackTreeNode<TestObject<int>> *node2 = new dsaa::RedBlackTreeNode<TestObject<int>>(std::move(*node));

    REQUIRE(TestObject<int>() == **node);
    REQUIRE(TestObject<int>() == node->value());
    REQUIRE(false == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    REQUIRE(value == **node2);
    REQUIRE(value == node2->value());
    REQUIRE(true == node2->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    delete node;
    delete node2;
    node = node2 = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode copy assignment.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    TestObject<int> value2(value);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, value, nullptr, nullptr, nullptr);

    REQUIRE(value == **node);
    REQUIRE(value == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    dsaa::RedBlackTreeNode<TestObject<int>> *node2 = new dsaa::RedBlackTreeNode<TestObject<int>>();
    *node2 = *node;

    REQUIRE(*node2 == *node);
    REQUIRE(**node2 == **node);
    REQUIRE(node2->value() == node->value());
    REQUIRE(node2->is_red() == node->is_red());
    REQUIRE(nullptr == node2->parent());
    REQUIRE(nullptr == node2->left());
    REQUIRE(nullptr == node2->right());

    delete node;
    delete node2;
    node = node2 = nullptr;
}

TEST_CASE("Test RedBlackTree RedBlackTreeNode move assignment.", "[RedBlackTree]")
{
    TestObject<int> value(6734);
    TestObject<int> value2(value);
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>(true, value, nullptr, nullptr, nullptr);

    REQUIRE(value2 == **node);
    REQUIRE(value2 == node->value());
    REQUIRE(true == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    dsaa::RedBlackTreeNode<TestObject<int>> *node2 = new dsaa::RedBlackTreeNode<TestObject<int>>();

    *node2 = std::move(*node);

    REQUIRE(TestObject<int>() == **node);
    REQUIRE(TestObject<int>() == node->value());
    REQUIRE(false == node->is_red());
    REQUIRE(nullptr == node->parent());
    REQUIRE(nullptr == node->left());
    REQUIRE(nullptr == node->right());

    REQUIRE(value == **node2);
    REQUIRE(value == node2->value());
    REQUIRE(true == node2->is_red());
    REQUIRE(nullptr == node2->parent());
    REQUIRE(nullptr == node2->left());
    REQUIRE(nullptr == node2->right());

    delete node;
    delete node2;
    node = node2 = nullptr;
}

// --------------------------------------------------------

TEST_CASE("Test RedBlackTree RedBlackTree default constructor.", "[RedBlackTree]")
{
    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
    dsaa::RedBlackTree<TestObject<int>> tree;
    REQUIRE(*node == *tree.root());
    REQUIRE(*node == *tree.sentinel());
    REQUIRE(0 == tree.size());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree default constructor with std::allocator", "[RedBlackTree]")
{
    allocator_type allocator;
    dsaa::RedBlackTree<TestObject<int>> tree(allocator);

    dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
    REQUIRE(*node == *tree.root());
    REQUIRE(*node == *tree.sentinel());
    REQUIRE(0 == tree.size());

    delete node;
    node = nullptr;
}

TEST_CASE("Test RedBlackTree insert", "[RedBlackTree]")
{

    SECTION("With 1 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::DynamicArray<TestObject<int>> elements{600};
        dsaa::DynamicArray<bool> colors{false};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 2 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> elements{600, 300};
        std::initializer_list<bool> colors{false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 3 element, case 3 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        std::initializer_list<TestObject<int>> elements{300, 100, 600};
        std::initializer_list<bool> colors{false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 4 element, case 1 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        std::initializer_list<TestObject<int>> elements{300, 100, 50, 600};
        std::initializer_list<bool> colors{false, false, true, false};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 5 element, case 2 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600};
        std::initializer_list<bool> colors{false, false, true, true, false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 6 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600, 900};
        std::initializer_list<bool> colors{false, false, true, true, false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 7 element, case 6 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200};
        std::initializer_list<bool> colors{false, false, true, true, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 8 element, case 4 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1250, 1200, 1300};
        std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 9 element, case 5 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1300, 1200, 1500};
        std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }
}

TEST_CASE("Test RedBlackTree erase", "[RedBlackTree]")
{
    SECTION("With 1 element, erase root")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::DynamicArray<TestObject<int>> elements{600};
        dsaa::DynamicArray<bool> colors{false};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    SECTION("With 2 element, erase with left child is sentinel")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> elements{600, 300};
        std::initializer_list<bool> colors{false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });
    }

    // SECTION("With 3 element, case 3 of insert")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100};
    //     std::initializer_list<TestObject<int>> elements{300, 100, 600};
    //     std::initializer_list<bool> colors{false, true, true};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }

    // SECTION("With 4 element, case 1 of insert")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
    //     std::initializer_list<TestObject<int>> elements{300, 100, 50, 600};
    //     std::initializer_list<bool> colors{false, false, true, false};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }

    // SECTION("With 5 element, case 2 of insert")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
    //     std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600};
    //     std::initializer_list<bool> colors{false, false, true, true, false, true};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }

    // SECTION("With 6 element")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
    //     std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600, 900};
    //     std::initializer_list<bool> colors{false, false, true, true, false, true};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }

    // SECTION("With 7 element, case 6 of insert")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
    //     std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200};
    //     std::initializer_list<bool> colors{false, false, true, true, false, true, true};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }

    // SECTION("With 8 element, case 4 of insert")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
    //     std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1250, 1200, 1300};
    //     std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }

    // SECTION("With 9 element, case 5 of insert")
    // {
    //     allocator_type allocator;
    //     std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
    //     std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1300, 1200, 1500};
    //     std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
    //     dsaa::RedBlackTree<TestObject<int>> tree(allocator);
    //     auto elements_iter(elements.begin());
    //     auto colors_iter(colors.begin());

    //     for (auto i(arg.begin()); i != arg.end(); ++i)
    //     {
    //         tree.insert(*i);
    //     }

    //     tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
    //                                       {
    //                                           REQUIRE(*elements_iter++ == value->value());
    //                                           REQUIRE(*colors_iter++ == value->is_red());
    //                                       });
    // }
}

TEST_CASE("Test RedBlackTree copy constructor", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        dsaa::RedBlackTree<TestObject<int>> tree;
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        REQUIRE(*node == *tree2.root());
        REQUIRE(*node == *tree2.sentinel());
        REQUIRE(0 == tree2.size());

        delete node;
        node = nullptr;
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 element, case 3 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 element, case 1 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        {
            dsaa::RedBlackTree<TestObject<int>> tree2(tree);

            dsaa::DynamicArray<value_type> arr(arg);
            dsaa::selection_sort(arr.begin(), arr.end());
            auto elements_iter(arr.begin());

            REQUIRE(arr.size() == tree.size());
            REQUIRE(arr.size() == tree2.size());

            tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                              { REQUIRE(*elements_iter++ == value->value()); });
        }
    }

    SECTION("With 5 element, case 2 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 element, case 6 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 element, case 4 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 element, case 5 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test RedBlackTree copy constructor with allocator", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        allocator_type allocator;
        dsaa::RedBlackTree<TestObject<int>> tree(allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        REQUIRE(*node == *tree2.root());
        REQUIRE(*node == *tree2.sentinel());
        REQUIRE(0 == tree2.size());

        delete node;
        node = nullptr;
    }

    SECTION("With 1 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 element, case 3 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 element, case 1 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 element, case 2 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 element, case 6 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 element, case 4 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 element, case 5 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test RedBlackTree move constructor", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        dsaa::RedBlackTree<TestObject<int>> tree;
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        REQUIRE(*node == *tree2.root());
        REQUIRE(*node == *tree2.sentinel());
        REQUIRE(0 == tree2.size());

        delete node;
        node = nullptr;
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 element, case 3 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 element, case 1 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 element, case 2 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 element, case 6 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 element, case 4 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 element, case 5 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test RedBlackTree move constructor with allocator", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        allocator_type allocator;
        dsaa::RedBlackTree<TestObject<int>> tree;
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        REQUIRE(*node == *tree2.root());
        REQUIRE(*node == *tree2.sentinel());
        REQUIRE(0 == tree2.size());

        delete node;
        node = nullptr;
    }
    SECTION("With empty tree")
    {
        dsaa::RedBlackTree<TestObject<int>> tree;
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree));

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        REQUIRE(*node == *tree2.root());
        REQUIRE(*node == *tree2.sentinel());
        REQUIRE(0 == tree2.size());

        delete node;
        node = nullptr;
    }

    SECTION("With 1 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 element, case 3 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 element, case 1 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 element, case 2 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 element, case 6 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 element, case 4 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 element, case 5 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);
        dsaa::RedBlackTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test RedBlackTree constructor using initializer_list", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        std::initializer_list<TestObject<int>> arg;
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        delete node;
        node = nullptr;
    }
    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        std::initializer_list<TestObject<int>> elements{600};
        std::initializer_list<bool> colors{false};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 2 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> elements{600, 300};
        std::initializer_list<bool> colors{false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 3 element, case 3 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        std::initializer_list<TestObject<int>> elements{300, 100, 600};
        std::initializer_list<bool> colors{false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 4 element, case 1 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        std::initializer_list<TestObject<int>> elements{300, 100, 50, 600};
        std::initializer_list<bool> colors{false, false, true, false};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              //   std::cout << "value: " << value->value() << std::endl;
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 5 element, case 2 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600};
        std::initializer_list<bool> colors{false, false, true, true, false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              //   std::cout << "value: " << value->value() << std::endl;
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 6 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600, 900};
        std::initializer_list<bool> colors{false, false, true, true, false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              //   std::cout << "value: " << value->value() << std::endl;
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 7 element, case 6 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200};
        std::initializer_list<bool> colors{false, false, true, true, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              //   std::cout << "value: " << value->value() << std::endl;
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 8 element, case 4 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1250, 1200, 1300};
        std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              //   std::cout << "value: " << value->value() << std::endl;
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 9 element, case 5 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1300, 1200, 1500};
        std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              // std::cout << "value: " << value->value() << std::endl;
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }
}

TEST_CASE("Test RedBlackTree constructor using initializer_list and allocator", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg;
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        delete node;
        node = nullptr;
    }
    SECTION("With 1 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        std::initializer_list<TestObject<int>> elements{600};
        std::initializer_list<bool> colors{false};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 2 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> elements{600, 300};
        std::initializer_list<bool> colors{false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 3 element, case 3 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        std::initializer_list<TestObject<int>> elements{300, 100, 600};
        std::initializer_list<bool> colors{false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 4 element, case 1 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        std::initializer_list<TestObject<int>> elements{300, 100, 50, 600};
        std::initializer_list<bool> colors{false, false, true, false};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 5 element, case 2 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600};
        std::initializer_list<bool> colors{false, false, true, true, false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 6 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600, 900};
        std::initializer_list<bool> colors{false, false, true, true, false, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 7 element, case 6 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200};
        std::initializer_list<bool> colors{false, false, true, true, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 8 element, case 4 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1250, 1200, 1300};
        std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }

    SECTION("With 9 element, case 5 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1300, 1200, 1500};
        std::initializer_list<bool> colors{false, false, true, true, true, false, false, true, true};
        dsaa::RedBlackTree<TestObject<int>> tree(arg, allocator);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root()->parent());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(arg.size() == tree.size());

        auto elements_iter(elements.begin());
        auto colors_iter(colors.begin());
        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &colors_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*colors_iter++ == value->is_red());
                                          });

        delete node;
        node = nullptr;
    }
}

TEST_CASE("Test RedBlackTree copy assignment", "[RedBlackTree]")
{
    SECTION("With empty tree")
    {
        dsaa::RedBlackTree<TestObject<int>> tree;
        dsaa::RedBlackTree<TestObject<int>> tree2(tree);

        dsaa::RedBlackTreeNode<TestObject<int>> *node = new dsaa::RedBlackTreeNode<TestObject<int>>();
        REQUIRE(*node == *tree.root());
        REQUIRE(*node == *tree.sentinel());
        REQUIRE(0 == tree.size());

        REQUIRE(*node == *tree2.root());
        REQUIRE(*node == *tree2.sentinel());
        REQUIRE(0 == tree2.size());

        delete node;
        node = nullptr;
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        std::initializer_list<TestObject<int>> arg2{52};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> arg2{52, 621};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 element, case 3 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 element, case 1 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672, 216};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 element, case 2 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672, 216, 158};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 element")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672, 216, 158, 235};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 element, case 6 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672, 216, 158, 235, 231};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 element, case 4 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672, 216, 158, 235, 231, 211};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 element, case 5 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        std::initializer_list<TestObject<int>> arg2{52, 621, 672, 216, 158, 235, 231, 211, 82};
        dsaa::RedBlackTree<TestObject<int>> tree(arg);
        dsaa::RedBlackTree<TestObject<int>> tree2(arg2);

        tree2 = tree;

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::RedBlackTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}