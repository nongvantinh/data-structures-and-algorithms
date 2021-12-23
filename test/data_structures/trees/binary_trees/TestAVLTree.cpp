#include "Catch2/Catch.hpp"
#include "algorithms/Random.h"
#include "test/TestObject.h"
#include "arrays/DynamicArray.h"
#include "algorithms/Generic.h"
#include "trees/binary_trees/AVLTree.h"
#include "algorithms/Sort.h"
#include <initializer_list>

using value_type = TestObject<int>;
using allocator_type = std::allocator<dsaa::AVLTree<value_type>>;
using reference = value_type &;
using const_reference = value_type const &;
using pointer = dsaa::AVLTreeNode<value_type> *;
using const_pointer = dsaa::AVLTreeNode<value_type> const *;
using difference_type = std::ptrdiff_t;
using size_type = size_t;
//
//TEST_CASE("Test AVLTree AVLTreeNode default constructor.", "[AVLTree]")
//{
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>();
//
//	REQUIRE(TestObject<int>() == node->value());
//	REQUIRE(TestObject<int>() == **node);
//	REQUIRE(0 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	delete node;
//	node = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode constructor with value.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, value);
//
//	REQUIRE(value == node->value());
//	REQUIRE(value == **node);
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	delete node;
//	node = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode constructor by move value.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	TestObject<int> value2(value);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, std::move(value));
//
//	REQUIRE(TestObject<int>() == value);
//	REQUIRE(value2 == **node);
//	REQUIRE(value2 == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	delete node;
//	node = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode constructor with full initialization.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, value, nullptr, nullptr, nullptr);
//
//	REQUIRE(value == **node);
//	REQUIRE(value == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	delete node;
//	node = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode constructor with full initialization by move value.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	TestObject<int> value2(value);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, std::move(value), nullptr, nullptr, nullptr);
//
//	REQUIRE(TestObject<int>() == value);
//	REQUIRE(value2 == **node);
//	REQUIRE(value2 == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	delete node;
//	node = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode copy constructor.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, value, nullptr, nullptr, nullptr);
//
//	REQUIRE(value == **node);
//	REQUIRE(value == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	dsaa::AVLTreeNode<TestObject<int>>* node2 = new dsaa::AVLTreeNode<TestObject<int>>(*node);
//
//	REQUIRE(*node2 == *node);
//	REQUIRE(**node2 == **node);
//	REQUIRE(node2->value() == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(node2->parent() == node->parent());
//	REQUIRE(node2->left() == node->left());
//	REQUIRE(node2->right() == node->right());
//
//	delete node;
//	delete node2;
//	node = node2 = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode move constructor.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, value, nullptr, nullptr, nullptr);
//
//	REQUIRE(value == **node);
//	REQUIRE(value == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	dsaa::AVLTreeNode<TestObject<int>>* node2 = new dsaa::AVLTreeNode<TestObject<int>>(std::move(*node));
//
//	REQUIRE(TestObject<int>() == **node);
//	REQUIRE(TestObject<int>() == node->value());
//	REQUIRE(0 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	REQUIRE(value == **node2);
//	REQUIRE(value == node2->value());
//	REQUIRE(1 == node2->height());
//	REQUIRE(nullptr == node2->parent());
//	REQUIRE(nullptr == node2->left());
//	REQUIRE(nullptr == node2->right());
//
//	delete node;
//	delete node2;
//	node = node2 = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode copy assignment.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	TestObject<int> value2(value);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, value, nullptr, nullptr, nullptr);
//
//	REQUIRE(value == **node);
//	REQUIRE(value == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	dsaa::AVLTreeNode<TestObject<int>>* node2 = new dsaa::AVLTreeNode<TestObject<int>>();
//	*node2 = *node;
//
//	REQUIRE(*node2 == *node);
//	REQUIRE(**node2 == **node);
//	REQUIRE(node2->value() == node->value());
//	REQUIRE(node2->height() == node->height());
//	REQUIRE(nullptr == node2->parent());
//	REQUIRE(nullptr == node2->left());
//	REQUIRE(nullptr == node2->right());
//
//	delete node;
//	delete node2;
//	node = node2 = nullptr;
//}
//
//TEST_CASE("Test AVLTree AVLTreeNode move assignment.", "[AVLTree]")
//{
//	TestObject<int> value(6734);
//	TestObject<int> value2(value);
//	dsaa::AVLTreeNode<TestObject<int>>* node = new dsaa::AVLTreeNode<TestObject<int>>(1, value, nullptr, nullptr, nullptr);
//
//	REQUIRE(value2 == **node);
//	REQUIRE(value2 == node->value());
//	REQUIRE(1 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	dsaa::AVLTreeNode<TestObject<int>>* node2 = new dsaa::AVLTreeNode<TestObject<int>>();
//
//	*node2 = std::move(*node);
//
//	REQUIRE(TestObject<int>() == **node);
//	REQUIRE(TestObject<int>() == node->value());
//	REQUIRE(0 == node->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	REQUIRE(value == **node2);
//	REQUIRE(value == node2->value());
//	REQUIRE(1 == node2->height());
//	REQUIRE(nullptr == node->parent());
//	REQUIRE(nullptr == node->left());
//	REQUIRE(nullptr == node->right());
//
//	delete node;
//	delete node2;
//	node = node2 = nullptr;
//}
//
//// --------------------------------------------------------
//
//TEST_CASE("Test AVLTree AVLTree default constructor.", "[AVLTree]")
//{
//	dsaa::AVLTree<TestObject<int>> tree;
//	REQUIRE(nullptr == tree.root());
//	REQUIRE(0 == tree.size());
//}
//
//TEST_CASE("Test AVLTree default constructor with std::allocator", "[AVLTree]")
//{
//	allocator_type allocator;
//	dsaa::AVLTree<TestObject<int>> tree(allocator);
//
//	REQUIRE(nullptr == tree.root());
//	REQUIRE(0 == tree.size());
//}
//
//TEST_CASE("Test AVLTree insert", "[AVLTree]")
//{
//	SECTION("With 1 element")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600 };
//		dsaa::DynamicArray<TestObject<int>> elements{ 600 };
//		dsaa::DynamicArray<int> heights{ 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 2 elements")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300 };
//		std::initializer_list<TestObject<int>> elements{ 600, 300 };
//		std::initializer_list<int> heights{ 2, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 3 elements, case 1 of insert")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100 };
//		std::initializer_list<TestObject<int>> elements{ 300, 100, 600 };
//		std::initializer_list<int> heights{ 2, 1, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 4 elements, Only update height")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100, 50 };
//		std::initializer_list<TestObject<int>> elements{ 300, 100, 50, 600 };
//		std::initializer_list<int> heights{ 3, 2, 1, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 5 elements, case 2 of insert")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100, 50, 75 };
//		std::initializer_list<TestObject<int>> elements{ 300, 75, 50, 100, 600 };
//		std::initializer_list<int> heights{ 3, 2, 1, 1, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 6 elements, only update height")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100, 50, 75, 900 };
//		std::initializer_list<TestObject<int>> elements{ 300, 75, 50, 100, 600, 900 };
//		std::initializer_list<int> heights{ 3, 2, 1, 1, 2, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//
//	}
//
//	SECTION("With 7 elements, case 3 of insert")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100, 50, 75, 900, 1200 };
//		std::initializer_list<TestObject<int>> elements{ 300, 75, 50, 100, 900, 600, 1200 };
//		std::initializer_list<int> heights{ 3, 2, 1, 1, 2, 1, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 8 elements, only update height")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100, 50, 75, 900, 1200, 1300 };
//		std::initializer_list<TestObject<int>> elements{ 300, 75, 50, 100, 900, 600, 1200, 1300 };
//		std::initializer_list<int> heights{ 4, 2, 1, 1, 3, 1, 2, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//
//	SECTION("With 9 elements, case 4 of insert")
//	{
//		allocator_type allocator;
//		std::initializer_list<TestObject<int>> arg{ 600, 300, 100, 50, 75, 900, 1200, 1300, 1250 };
//		std::initializer_list<TestObject<int>> elements{ 300, 75, 50, 100, 900, 600, 1250, 1200, 1300 };
//		std::initializer_list<int> heights{ 4, 2, 1, 1, 3, 1, 2, 1, 1 };
//		dsaa::AVLTree<TestObject<int>> tree(allocator);
//		auto elements_iter(elements.begin());
//		auto heights_iter(heights.begin());
//
//		for (auto i(arg.begin()); i != arg.end(); ++i)
//		{
//			tree.insert(*i);
//		}
//
//		REQUIRE(elements.size() == tree.size());
//
//		tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>>*& value)
//			{
//				REQUIRE(*elements_iter++ == value->value());
//				REQUIRE(*heights_iter++ == value->height());
//			});
//	}
//}

TEST_CASE("Test AVLTree erase", "[AVLTree]")
{
    SECTION("With 1 element, erase root")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::DynamicArray<TestObject<int>> elements;
        dsaa::DynamicArray<bool> heights;
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 2 elements, erase with left child is null")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 700};
        std::initializer_list<TestObject<int>> elements{700};
        std::initializer_list<int> heights{1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 2 elements, erase with right child is null")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 400};
        std::initializer_list<TestObject<int>> elements{400};
        std::initializer_list<int> heights{1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 3 elements, erase with right child's parent is p_node")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 400, 700};
        std::initializer_list<TestObject<int>> elements{700, 400};
        std::initializer_list<int> heights{2, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 4 elements, erase with right child's parent is NOT p_node")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 400, 700, 650};
        std::initializer_list<TestObject<int>> elements{650, 400, 700};
        std::initializer_list<int> heights{2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 5 elements, erase with right child's parent is NOT p_node")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 400, 700, 650, 900};
        std::initializer_list<TestObject<int>> elements{650, 400, 700, 900};
        std::initializer_list<int> heights{3, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        tree.erase(tree.root());
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 15 elements, erase case 1")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 900, 100, 500, 800, 1200, 50, 400, 550, 700, 850, 1100, 350, 750};
        std::initializer_list<TestObject<int>> elements{600, 300, 100, 50, 400, 350, 500, 900, 800, 700, 750, 850, 1200, 1100};
        std::initializer_list<int> heights{5, 3, 2, 1, 2, 1, 1, 4, 3, 2, 1, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        pointer node = tree.iterative_search(tree.root(), 550);
        tree.erase(node);
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 14 elements, erase case 2")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 900, 100, 400, 800, 1200, 50, 350, 500, 700, 850, 1100, 750};
        std::initializer_list<TestObject<int>> elements{600, 300, 100, 50, 400, 350, 500, 900, 750, 700, 800, 1200, 1100};
        std::initializer_list<int> heights{4, 3, 2, 1, 2, 1, 1, 3, 2, 1, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        pointer node = tree.iterative_search(tree.root(), 850);
        tree.erase(node);
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 13 elements, only update height")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 900, 100, 400, 750, 1200, 50, 350, 500, 700, 800, 1100};
        std::initializer_list<TestObject<int>> elements{600, 300, 50, 400, 350, 500, 900, 750, 700, 800, 1200, 1100};
        std::initializer_list<int> heights{4, 3, 1, 2, 1, 1, 3, 2, 1, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        pointer node = tree.iterative_search(tree.root(), 100);
        tree.erase(node);
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 12 elements, erase case 3")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 900, 50, 400, 750, 1200, 350, 500, 700, 800, 1100};
        std::initializer_list<TestObject<int>> elements{600, 400, 300, 350, 500, 900, 750, 700, 800, 1200, 1100};
        std::initializer_list<int> heights{4, 3, 2, 1, 1, 3, 2, 1, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        for (auto i(arg.begin()); i != arg.end(); ++i)
        {
            tree.insert(*i);
        }

        pointer node = tree.iterative_search(tree.root(), 50);
        tree.erase(node);
        REQUIRE(tree.size() == arg.size() - 1);

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }
}

TEST_CASE("Test AVLTree copy constructor", "[AVLTree]")
{
    SECTION("With empty tree")
    {
        dsaa::AVLTree<TestObject<int>> tree;
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        REQUIRE(nullptr == tree.root());
        REQUIRE(0 == tree.size());

        REQUIRE(nullptr == tree2.root());
        REQUIRE(0 == tree2.size());
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        {
            dsaa::AVLTree<TestObject<int>> tree2(tree);

            dsaa::DynamicArray<value_type> arr(arg);
            dsaa::selection_sort(arr.begin(), arr.end());
            auto elements_iter(arr.begin());

            REQUIRE(arr.size() == tree.size());
            REQUIRE(arr.size() == tree2.size());

            tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                              { REQUIRE(*elements_iter++ == value->value()); });
        }
    }

    SECTION("With 5 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(tree);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test AVLTree copy constructor with allocator", "[AVLTree]")
{
    SECTION("With empty tree")
    {
        dsaa::AVLTree<TestObject<int>> tree;
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        REQUIRE(nullptr == tree.root());
        REQUIRE(0 == tree.size());

        REQUIRE(nullptr == tree2.root());
        REQUIRE(0 == tree2.size());
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree2(tree, allocator);

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());

        REQUIRE(arr.size() == tree.size());
        REQUIRE(arr.size() == tree2.size());

        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test AVLTree move constructor", "[AVLTree]")
{
    SECTION("With empty tree")
    {
        dsaa::AVLTree<TestObject<int>> tree;
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(nullptr == tree.root());
        REQUIRE(0 == tree.size());

        REQUIRE(nullptr == tree2.root());
        REQUIRE(0 == tree2.size());
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 elements, case 3 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 elements, case 1 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 elements, case 2 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 elements, case 6 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 elements, case 4 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 elements, case 5 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree));

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test AVLTree move constructor with allocator", "[AVLTree]")
{
    SECTION("With empty tree")
    {
        allocator_type allocator;
        dsaa::AVLTree<TestObject<int>> tree;
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(nullptr == tree.root());
        REQUIRE(0 == tree.size());

        REQUIRE(nullptr == tree2.root());
        REQUIRE(0 == tree2.size());
    }

    SECTION("With 1 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 2 elements")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 3 elements, case 3 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 4 elements, case 1 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 5 elements, case 2 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 6 elements")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 7 elements, case 6 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 8 elements, case 4 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }

    SECTION("With 9 elements, case 5 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1500};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        dsaa::AVLTree<TestObject<int>> tree2(std::move(tree), allocator);

        REQUIRE(0 == tree.size());
        REQUIRE(arg.size() == tree2.size());

        dsaa::DynamicArray<value_type> arr(arg);
        dsaa::selection_sort(arr.begin(), arr.end());
        auto elements_iter(arr.begin());
        tree2.recursive_inorder_tree_walk(tree2.root(), [&elements_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(*elements_iter++ == value->value()); });
    }
}

TEST_CASE("Test AVLTree constructor using initializer_list", "[AVLTree]")
{
    SECTION("With empty tree")
    {
        std::initializer_list<TestObject<int>> arg;
        dsaa::AVLTree<TestObject<int>> tree(arg);

        REQUIRE(nullptr == tree.root());
        REQUIRE(0 == tree.size());
    }

    SECTION("With 1 element")
    {
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::DynamicArray<TestObject<int>> elements{600};
        dsaa::DynamicArray<int> heights{1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 2 elements")
    {
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> elements{600, 300};
        std::initializer_list<int> heights{2, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 3 elements, case 1 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        std::initializer_list<TestObject<int>> elements{300, 100, 600};
        std::initializer_list<int> heights{2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 4 elements, Only update height")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        std::initializer_list<TestObject<int>> elements{300, 100, 50, 600};
        std::initializer_list<int> heights{3, 2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 5 elements, case 2 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600};
        std::initializer_list<int> heights{3, 2, 1, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 6 elements, only update height")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600, 900};
        std::initializer_list<int> heights{3, 2, 1, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 7 elements, case 3 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200};
        std::initializer_list<int> heights{3, 2, 1, 1, 2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 8 elements, only update height")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200, 1300};
        std::initializer_list<int> heights{4, 2, 1, 1, 3, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 9 elements, case 4 of insert")
    {
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1250, 1200, 1300};
        std::initializer_list<int> heights{4, 2, 1, 1, 3, 1, 2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }
}


TEST_CASE("Test AVLTree constructor using initializer_list and allocator", "[AVLTree]")
{
    SECTION("With empty tree")
    {
        std::initializer_list<TestObject<int>> arg;
        dsaa::AVLTree<TestObject<int>> tree(arg);

        REQUIRE(nullptr == tree.root());
        REQUIRE(0 == tree.size());
    }

    SECTION("With 1 element")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600};
        dsaa::DynamicArray<TestObject<int>> elements{600};
        dsaa::DynamicArray<int> heights{1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 2 elements")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300};
        std::initializer_list<TestObject<int>> elements{600, 300};
        std::initializer_list<int> heights{2, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 3 elements, case 1 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100};
        std::initializer_list<TestObject<int>> elements{300, 100, 600};
        std::initializer_list<int> heights{2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 4 elements, Only update height")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50};
        std::initializer_list<TestObject<int>> elements{300, 100, 50, 600};
        std::initializer_list<int> heights{3, 2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 5 elements, case 2 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600};
        std::initializer_list<int> heights{3, 2, 1, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 6 elements, only update height")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 600, 900};
        std::initializer_list<int> heights{3, 2, 1, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 7 elements, case 3 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200};
        std::initializer_list<int> heights{3, 2, 1, 1, 2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 8 elements, only update height")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1200, 1300};
        std::initializer_list<int> heights{4, 2, 1, 1, 3, 1, 2, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }

    SECTION("With 9 elements, case 4 of insert")
    {
        allocator_type allocator;
        std::initializer_list<TestObject<int>> arg{600, 300, 100, 50, 75, 900, 1200, 1300, 1250};
        std::initializer_list<TestObject<int>> elements{300, 75, 50, 100, 900, 600, 1250, 1200, 1300};
        std::initializer_list<int> heights{4, 2, 1, 1, 3, 1, 2, 1, 1};
        dsaa::AVLTree<TestObject<int>> tree(arg, allocator);
        auto elements_iter(elements.begin());
        auto heights_iter(heights.begin());

        REQUIRE(elements.size() == tree.size());

        tree.recursive_preorder_tree_walk(tree.root(), [&elements_iter, &heights_iter](dsaa::AVLTreeNode<TestObject<int>> *&value)
                                          {
                                              REQUIRE(*elements_iter++ == value->value());
                                              REQUIRE(*heights_iter++ == value->height());
                                          });
    }
}
