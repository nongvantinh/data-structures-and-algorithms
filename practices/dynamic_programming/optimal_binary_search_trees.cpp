#include "Catch2/Catch.hpp"
#include <vector>
#include <iostream>
#include <stack>

class Matrix
{
public:
	Matrix(size_t p_rows, size_t p_columns, int p_value = 0) : m_matrix(p_rows)
	{
		for (auto& row : m_matrix)
		{
			row.resize(p_columns);
			for (auto& i : row)
			{
				i = p_value;
			}
		}
	}

	Matrix(const std::vector<std::vector<double>>& p_args) : m_matrix(p_args.size())
	{
		for (size_t i(0); i != rows(); ++i)
		{
			m_matrix[i] = p_args[i];
		}
	}

	size_t rows() const { return m_matrix.size(); }
	size_t columns() const { return 0 == rows() ? 0 : m_matrix[0].size(); }

	std::vector<double>& operator[](size_t p_index)
	{
		if (0 == rows())
			throw std::runtime_error("Matrix is empty");
		if (p_index < 0 || rows() <= p_index)
			throw std::runtime_error("Index out of range");

		return m_matrix[p_index];
	}

	const std::vector<double>& operator[](size_t p_index) const
	{
		if (0 == rows())
			throw std::runtime_error("Matrix is empty");
		if (p_index < 0 || rows() <= p_index)
			throw std::runtime_error("Index out of range");

		return m_matrix[p_index];
	}

private:
	std::vector<std::vector<double>> m_matrix;
};

class BinaryTreeNode
{
public:
	BinaryTreeNode(double p_value = 0.0) noexcept : m_value(p_value), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
	BinaryTreeNode*& parent() { return m_parent; }
	BinaryTreeNode* const& parent() const { return m_parent; }

	BinaryTreeNode*& left() { return m_left; }
	BinaryTreeNode* const left() const { return m_left; }

	BinaryTreeNode*& right() { return m_right; }
	BinaryTreeNode* const right() const { return m_right; }

	double& value() { return m_value; }
	double value() const { return m_value; }

	double m_value;       // The key that this node hold.
	BinaryTreeNode* m_parent; // The parent node of this node.
	BinaryTreeNode* m_left;   // The left child.
	BinaryTreeNode* m_right;  // The right child.
};

template <typename Action>
void recursive_preorder_tree_walk(BinaryTreeNode*& p_node, Action p_action)
{
	if (nullptr != p_node)
	{
		p_action(p_node);
		recursive_preorder_tree_walk(p_node->left(), p_action);
		recursive_preorder_tree_walk(p_node->right(), p_action);
	}
}

template <typename Action>
void recursive_postorder_tree_walk(BinaryTreeNode*& p_node, Action p_action)
{
	if (nullptr != p_node)
	{
		recursive_postorder_tree_walk(p_node->left(), p_action);
		recursive_postorder_tree_walk(p_node->right(), p_action);
		p_action(p_node);
	}
}
class BinaryTree
{
public:
	BinaryTree() noexcept
		: m_root(nullptr), m_size(0) {}

	BinaryTree& operator=(BinaryTree& p_other)
	{
		recursive_postorder_tree_walk(m_root, [&](BinaryTreeNode*& p_node)
			{ erase(p_node); });

		recursive_preorder_tree_walk(p_other.root(), [&](BinaryTreeNode*& p_node)
			{ insert(p_node->value()); });
		return *this;
	}

	BinaryTreeNode*& root() noexcept
	{
		return m_root;
	}

	const BinaryTreeNode* root() const noexcept
	{
		return m_root;
	}

	void insert(double p_value)
	{
		BinaryTreeNode* new_node = new BinaryTreeNode(p_value);

		BinaryTreeNode* direction = m_root;
		BinaryTreeNode* trailing = nullptr;
		while (direction)
		{
			trailing = direction;
			if (p_value < direction->m_value)
				direction = direction->m_left;
			else
				direction = direction->m_right;
		}

		new_node->m_parent = trailing;

		if (nullptr == m_root)
			m_root = new_node;
		else if (p_value < trailing->m_value)
			trailing->m_left = new_node;
		else
			trailing->m_right = new_node;

		++m_size;
	}

	BinaryTreeNode* iterative_minimum(BinaryTreeNode* p_node) noexcept
	{
		while (p_node->m_left)
			p_node = p_node->m_left;

		return p_node;
	}

	// Auxiliary method for erasing node. This method does not handle child transplant.
	void transplant(BinaryTreeNode*& p_node, BinaryTreeNode*& p_child) noexcept
	{
		if (!p_node->m_parent)
			m_root = p_child;
		else if (p_node == p_node->m_parent->m_left)
			p_node->m_parent->m_left = p_child;
		else
			p_node->m_parent->m_right = p_child;

		if (p_child)
			p_child->m_parent = p_node->m_parent;
	}

	void erase(BinaryTreeNode*& p_node)
	{
		// The moment p_node transplant with its child, p_node will become invalid.
		BinaryTreeNode* substitute(p_node);

		if (!p_node->m_left)
			transplant(p_node, p_node->m_right);
		else if (!p_node->m_right)
			transplant(p_node, p_node->m_left);
		else
		{
			BinaryTreeNode* succ = iterative_minimum(p_node->m_right);

			if (succ->m_parent != p_node)
			{
				transplant(succ, succ->m_right);
				succ->m_right = p_node->m_right;
				succ->m_right->m_parent = succ;
			}
			transplant(p_node, succ);
			succ->m_left = substitute->m_left;
			succ->m_left->m_parent = succ;
		}

		delete substitute;
		--m_size;
	}


	~BinaryTree()
	{
		//recursive_postorder_tree_walk(m_root, [&](BinaryTreeNode*& p_node)
		//	{ erase(p_node); });
	}

	BinaryTreeNode* m_root;
	size_t m_size;
};




/*
	- p_keys: The array contains the probabilities of the keys that were searched.
	- p_dummys: The array contains the probabilities of the searched's keys that do not exist.

	- Returns 2 matrices contains expected searched cost and the root node where we split the array in two.
*/
std::tuple<Matrix, Matrix> optimal_BST(const std::vector<double>& p_keys, const std::vector<double>& p_dummys)
{
	// Even if the key is NULL, we still have probability when searching for a key that does not exist.
	assert(p_keys.size() == p_dummys.size() - 1);

	if (0 == p_keys.size())
	{
		Matrix e(1, 1);
		e[0][0] = p_dummys[0];

		return std::tuple<Matrix, Matrix>(e, Matrix(1, 1));
	}

	// One for dummy key in left subtree, one for dummy key in right subtree.
	constexpr size_t offset(2);
	const size_t size(p_keys.size() + offset);

	Matrix esc(size, size); // Expected search cost for range [left bound, right bound].
	Matrix total(size, size); // Sum of probabilities in range [left bound, right bound].
	Matrix root(size - 1, size - 1); // The index where array split in half [left bound : r - 1, r + 1 : right bound]

	for (size_t r(1); r != size; ++r)
	{
		esc[r][r - 1] = p_dummys[r - 1];
		total[r][r - 1] = p_dummys[r - 1];
	}

	for (size_t length(1); length <= size - offset; ++length)
	{
		for (size_t left_bound(1); left_bound <= size - length - offset + 1; ++left_bound)
		{
			size_t right_bound(left_bound + length - 1);
			esc[left_bound][right_bound] = INT_MAX;
			total[left_bound][right_bound] = total[left_bound][right_bound - 1] + p_keys[right_bound - 1] + p_dummys[right_bound];
			for (size_t root_index(left_bound); root_index <= right_bound; ++root_index)
			{
				double cost = esc[left_bound][root_index - 1] + esc[root_index + 1][right_bound] + total[left_bound][right_bound];
				if (cost < esc[left_bound][right_bound])
				{
					esc[left_bound][right_bound] = cost;
					root[left_bound][right_bound] = root_index;
				}
			}
		}
	}

	return std::tuple<Matrix, Matrix>(esc, root);
}

struct Location
{
	Location(size_t p_parent_x, size_t p_parent_y, size_t p_position_x, size_t p_position_y)
		: parent_x(p_parent_x), parent_y(p_parent_y), position_x(p_position_x), position_y(p_position_y) {}

	size_t get_parent_index(const Matrix& p_root) const
	{
		return p_root[parent_x][parent_y];
	}

	size_t get_index(const Matrix& p_root) const
	{
		return p_root[position_x][position_y];
	}

	size_t parent_x;
	size_t parent_y;

	size_t position_x;
	size_t position_y;
};

BinaryTree construct_optimal_BST(const Matrix& root, size_t size)
{
	BinaryTree tree;
	if (0 == size)
	{
		std::cout << "There is nothing to contruct!\n";
		return tree;
	}


	std::stack<Location> right_childs;
	Location trace(1, size, 1, size);

	while (true)
	{
		tree.insert(trace.get_index(root));

		// Preserve right child.
		if (trace.position_y != trace.get_index(root))
		{
			right_childs.push(Location(trace.position_x, trace.position_y, trace.get_index(root) + 1, trace.position_y));
		}

		// Goto left.
		if (trace.position_x != trace.get_index(root))
		{
			trace = Location(trace.position_x, trace.position_y, trace.position_x, trace.get_index(root) - 1);
			right_childs.push(trace);
		}

		if (right_childs.size())
		{
			trace = right_childs.top();
			right_childs.pop();
		}
		else
		{
			break;
		}
	}

	double value(0.5);

	for (size_t i(0); i <= size; ++i)
	{
		tree.insert(value);
		++value;
	}

	return tree;
}

TEST_CASE("Optimal binary search trees.", "[optimal_binary_search_trees]")
{
	SECTION("Zero key.")
	{
		std::vector<double> keys_probabilities;
		std::vector<double> dummys_probabilities{ 1 };

		Matrix root = std::get<1>(optimal_BST(keys_probabilities, dummys_probabilities));
		std::cout << "CONTRUCT BINARY SEARCH TREE WITH ZERO KEY\n";
		std::cout << "-----------------------------------------\n";
		BinaryTree tree = construct_optimal_BST(root, keys_probabilities.size());
		recursive_preorder_tree_walk(tree.root(), [&](const BinaryTreeNode* p_node)
			{
				bool flag = (static_cast<int>(p_node->value()) == p_node->value());
				if (nullptr == p_node->m_parent)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is the root\n";
				}
				else if (p_node == p_node->m_parent->m_left)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is left child of k-" << p_node->m_parent->m_value << "\n";
				}
				else
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is right child of k-" << p_node->m_parent->m_value << "\n";
				}
			});

		std::cout << "-----------------------------------------\n\n";
	}

	SECTION("One key.")
	{
		std::vector<double> keys_probabilities{ 0.7 };
		std::vector<double> dummys_probabilities{ 0.1, 0.2 };

		Matrix root = std::get<1>(optimal_BST(keys_probabilities, dummys_probabilities));
		std::cout << "CONTRUCT BINARY SEARCH TREE WITH ONE KEY\n";
		std::cout << "-----------------------------------------\n";
		BinaryTree tree = construct_optimal_BST(root, keys_probabilities.size());
		recursive_preorder_tree_walk(tree.root(), [&](const BinaryTreeNode* p_node)
			{
				bool flag = (static_cast<int>(p_node->value()) == p_node->value());
				if (nullptr == p_node->m_parent)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is the root\n";
				}
				else if (p_node == p_node->m_parent->m_left)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is left child of k-" << p_node->m_parent->m_value << "\n";
				}
				else
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is right child of k-" << p_node->m_parent->m_value << "\n";
				}
			});

		std::cout << "-----------------------------------------\n\n";
	}

	SECTION("Two keys.")
	{
		std::vector<double> keys_probabilities{ 0.2, 0.4 };
		std::vector<double> dummys_probabilities{ 0.1, 0.1, 0.2 };

		Matrix root = std::get<1>(optimal_BST(keys_probabilities, dummys_probabilities));
		std::cout << "CONTRUCT BINARY SEARCH TREE WITH TWO KEYS\n";
		std::cout << "-----------------------------------------\n";
		BinaryTree tree = construct_optimal_BST(root, keys_probabilities.size());
		recursive_preorder_tree_walk(tree.root(), [&](const BinaryTreeNode* p_node)
			{
				bool flag = (static_cast<int>(p_node->value()) == p_node->value());
				if (nullptr == p_node->m_parent)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is the root\n";
				}
				else if (p_node == p_node->m_parent->m_left)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is left child of k-" << p_node->m_parent->m_value << "\n";
				}
				else
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is right child of k-" << p_node->m_parent->m_value << "\n";
				}
			});

		std::cout << "-----------------------------------------\n\n";
	}

	SECTION("Three keys.")
	{
		std::vector<double> keys_probabilities{ 0.3, 0.2, 0.1 };
		std::vector<double> dummys_probabilities{ 0.1, 0.1, 0.1, 0.1 };

		Matrix root = std::get<1>(optimal_BST(keys_probabilities, dummys_probabilities));
		std::cout << "CONTRUCT BINARY SEARCH TREE WITH THREE KEYS\n";
		std::cout << "-----------------------------------------\n";
		BinaryTree tree = construct_optimal_BST(root, keys_probabilities.size());
		recursive_preorder_tree_walk(tree.root(), [&](const BinaryTreeNode* p_node)
			{
				bool flag = (static_cast<int>(p_node->value()) == p_node->value());
				if (nullptr == p_node->m_parent)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is the root\n";
				}
				else if (p_node == p_node->m_parent->m_left)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is left child of k-" << p_node->m_parent->m_value << "\n";
				}
				else
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is right child of k-" << p_node->m_parent->m_value << "\n";
				}
			});

		std::cout << "-----------------------------------------\n\n";
	}

	SECTION("CLRS figure 14.9b keys.")
	{
		std::vector<double> keys_probabilities{ 0.15, 0.10, 0.05, 0.10, 0.20 };
		std::vector<double> dummys_probabilities{ 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };

		Matrix root = std::get<1>(optimal_BST(keys_probabilities, dummys_probabilities));
		std::cout << "CONTRUCT BINARY SEARCH TREE WITH CLRS figure 14.9b KEYS\n";
		std::cout << "-----------------------------------------\n";
		BinaryTree tree = construct_optimal_BST(root, keys_probabilities.size());
		recursive_preorder_tree_walk(tree.root(), [&](const BinaryTreeNode* p_node)
			{
				bool flag = (static_cast<int>(p_node->value()) == p_node->value());
				if (nullptr == p_node->m_parent)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is the root\n";
				}
				else if (p_node == p_node->m_parent->m_left)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is left child of k-" << p_node->m_parent->m_value << "\n";
				}
				else
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is right child of k-" << p_node->m_parent->m_value << "\n";
				}
			});

		std::cout << "-----------------------------------------\n\n";
	}
	SECTION("CLRS 14.5-2 n=7 keys.")
	{
		std::vector<double> keys_probabilities{ 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14 };
		std::vector<double> dummys_probabilities{ 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05 };

		Matrix root = std::get<1>(optimal_BST(keys_probabilities, dummys_probabilities));
		std::cout << "CONTRUCT BINARY SEARCH TREE WITH n=7 KEYS\n";
		std::cout << "-----------------------------------------\n";
		BinaryTree tree = construct_optimal_BST(root, keys_probabilities.size());
		recursive_preorder_tree_walk(tree.root(), [&](const BinaryTreeNode* p_node)
			{
				bool flag = (static_cast<int>(p_node->value()) == p_node->value());
				if (nullptr == p_node->m_parent)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is the root\n";
				}
				else if (p_node == p_node->m_parent->m_left)
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is left child of k-" << p_node->m_parent->m_value << "\n";
				}
				else
				{
					std::cout << (flag ? "k-" : "d-") << p_node->m_value << " is right child of k-" << p_node->m_parent->m_value << "\n";
				}
			});

		std::cout << "-----------------------------------------\n\n";
	}
}
