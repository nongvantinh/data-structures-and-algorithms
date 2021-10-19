// #ifndef DSAA_TEST_SEARCH_H
// #define DSAA_TEST_SEARCH_H

// #include "Catch2/Catch.hpp"

// #include <iostream>

// #include "algorithms/Generic.h"
// #include "binary_trees/BinaryTree.h"
// #include "test/TestObject.h"

// TEST_CASE("Test recursive_inorder_tree_walk.", "[Generic]")
// {
//     SECTION("An ordinary sequence.")
//     {
//         dsaa::BinaryTree<TestObject<int>> tree{6, 5, 7, 2, 5, 8};
//         std::cout << "tree.size(): " << tree.size() << std::endl;

//         std::cout << "recursive_inorder_tree_walk: [";

//         dsaa::recursive_inorder_tree_walk(tree.root(), [](dsaa::BinaryTreeNode<TestObject<int>> *&value)
//                                           { std::cout << value->value() << " "; });
//         std::cout << "]\n";
//     }

//     SECTION("An ordinary sequence.")
//     {
//         dsaa::BinaryTree<TestObject<int>> tree{12, 5, 18, 2, 9, 15, 19, 13, 17};
//         std::cout << "tree.size(): " << tree.size() << std::endl;

//         std::cout << "recursive_inorder_tree_walk: [";
//         dsaa::recursive_inorder_tree_walk(tree.root(), [](dsaa::BinaryTreeNode<TestObject<int>> *&value)
//                                           { std::cout << value->value() << " "; });
//         std::cout << "]\n";
//     }
// }

// #endif //!DSAA_TEST_SEARCH_H