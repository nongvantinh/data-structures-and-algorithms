#ifndef DSAA_TEST_SEARCH_H
#define DSAA_TEST_SEARCH_H

#include "Catch2/Catch.hpp"

#include <iostream>

#include "algorithms/Generic.h"
#include "binary_trees/BinaryTree.h"
#include "test/TestObject.h"

TEST_CASE("Test recursive_inorder_tree_walk.", "[Generic]")
{
    SECTION("An ordinary sequence.")
    {
        dsaa::BinaryTree<TestObject<int>> tree{6, 5, 7, 2, 5, 8};

        TestObject<int> prev;
        dsaa::recursive_inorder_tree_walk(tree.root(), [prev](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(prev <= value->value()); });
    }

    SECTION("An ordinary sequence.")
    {
        dsaa::BinaryTree<TestObject<int>> tree{12, 5, 18, 2, 9, 15, 19, 13, 17};
        TestObject<int> prev;
        dsaa::recursive_inorder_tree_walk(tree.root(), [prev](dsaa::BinaryTreeNode<TestObject<int>> *&value)
                                          { REQUIRE(prev <= value->value()); });
    }
}

#endif //!DSAA_TEST_SEARCH_H