#ifndef DAAA_AVL_TREE_H
#define DAAA_AVL_TREE_H

#include <memory>
#include <functional>
#include <initializer_list>
#include <iostream>

#include "dsaaTypedefs.h"

namespace dsaa
{
	template <typename T>
	class AVLTreeNode;

	template <typename Elem, typename Alloc = std::allocator<AVLTreeNode<Elem>>>
	class AVLTree
	{
	public:
		using value_type = Elem;
		using allocator_type = Alloc;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = AVLTreeNode<value_type>*;
		using const_pointer = const AVLTreeNode<value_type>*;
		using difference_type = std::ptrdiff_t;
		using size_type = size_t;

		// Creates a container with no element.
		CONSTEXPR AVLTree(const allocator_type& p_allocator = allocator_type()) noexcept;
		CONSTEXPR AVLTree(const AVLTree& p_other) noexcept;
		CONSTEXPR AVLTree(const AVLTree& p_other, const allocator_type& p_allocator) noexcept;
		CONSTEXPR AVLTree(AVLTree&& p_other) noexcept;
		CONSTEXPR AVLTree(AVLTree&& p_other, const allocator_type& p_allocator) noexcept;
		CONSTEXPR AVLTree(const std::initializer_list<value_type>& p_elements, const allocator_type& p_allocator = allocator_type()) noexcept;

		CONSTEXPR AVLTree& operator=(const AVLTree& p_other);
		CONSTEXPR AVLTree& operator=(AVLTree&& p_other);
		CONSTEXPR AVLTree& operator=(const std::initializer_list<value_type>& p_elements);
		// Destroys all elements and clean used space.
		~AVLTree();

		CONSTEXPR INLINE allocator_type allocator() const noexcept;
		CONSTEXPR INLINE pointer& root() noexcept;
		CONSTEXPR INLINE const_pointer root() const noexcept;
		CONSTEXPR INLINE size_type size() const noexcept;
		// The value return in between [-1, 0, 1] is called AVL tree.
		CONSTEXPR INLINE int balance_factor(const_pointer p_node) const noexcept;
		CONSTEXPR INLINE int height(const_pointer p_node) noexcept;
		CONSTEXPR INLINE int height(const_pointer p_node) const noexcept;

		CONSTEXPR pointer iterative_minimum(pointer p_node) noexcept;
		CONSTEXPR pointer iterative_maximum(pointer p_node) noexcept;
		CONSTEXPR pointer recursive_minimum(pointer p_node) noexcept;
		CONSTEXPR pointer recursive_maximum(pointer p_node) noexcept;
		CONSTEXPR pointer successor(pointer p_node) noexcept;
		CONSTEXPR pointer predecessor(pointer p_node) noexcept;
		CONSTEXPR pointer iterative_search(pointer p_node, const_reference p_value) noexcept;
		CONSTEXPR pointer recursive_search(pointer p_node, const_reference p_value) noexcept;

		template <typename Action>
		CONSTEXPR void recursive_preorder_tree_walk(pointer& p_node, Action p_action);
		template <typename Action>
		CONSTEXPR void recursive_preorder_tree_walk(const_pointer p_node, Action p_action) const noexcept;
		template <typename Action>
		CONSTEXPR void recursive_inorder_tree_walk(pointer& p_node, Action p_action);
		template <typename Action>
		CONSTEXPR void recursive_inorder_tree_walk(const_pointer p_node, Action p_action) const noexcept;
		template <typename Action>
		CONSTEXPR void recursive_postorder_tree_walk(pointer& p_node, Action p_action);
		template <typename Action>
		CONSTEXPR void recursive_postorder_tree_walk(const_pointer p_node, Action p_action) const noexcept;

		CONSTEXPR void left_rotate(pointer p_node) noexcept;
		CONSTEXPR void right_rotate(pointer p_node) noexcept;

		CONSTEXPR void insert(const_reference p_value);
		CONSTEXPR void insert_fixup(pointer p_node);

		CONSTEXPR void erase(pointer& p_node);
		CONSTEXPR void erase_fixup(pointer p_node);
		// p_other will take place of p_node in tree.
		CONSTEXPR void transplant(pointer& p_node, pointer& p_other) noexcept;

	private:
		allocator_type m_allocator;
		pointer m_root;
		size_type m_size;
	};
} // namespace dsaa

template <typename T>
class dsaa::AVLTreeNode
{
public:
	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = size_t;

	CONSTEXPR AVLTreeNode(int p_height = 0, const_reference p_value = value_type()) noexcept : m_height(p_height), m_value(p_value), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
	CONSTEXPR AVLTreeNode(int p_height, value_type&& p_value) noexcept : m_height(p_height), m_value(std::move(p_value)), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
	CONSTEXPR AVLTreeNode(int p_height, const_reference p_value, AVLTreeNode* p_parent, AVLTreeNode* p_left, AVLTreeNode* p_right) noexcept : m_height(p_height), m_value(p_value), m_parent(p_parent), m_left(p_left), m_right(p_right) {}
	CONSTEXPR AVLTreeNode(int p_height, value_type&& p_value, AVLTreeNode* p_parent, AVLTreeNode* p_left, AVLTreeNode* p_right) noexcept : m_height(p_height), m_value(std::move(p_value)), m_parent(p_parent), m_left(p_left), m_right(p_right) { p_value = value_type(); }

	CONSTEXPR AVLTreeNode(const AVLTreeNode& p_other) noexcept : m_height(p_other.m_height), m_value(p_other.m_value), m_parent(p_other.m_parent), m_left(p_other.m_left), m_right(p_other.m_right) {}
	CONSTEXPR AVLTreeNode(AVLTreeNode&& p_other) noexcept : m_height(p_other.m_height), m_value(std::move(p_other.m_value)), m_parent(p_other.m_parent), m_left(p_other.m_left), m_right(p_other.m_right)
	{
		p_other.m_height = 0;
		p_other.m_value = value_type();
		p_other.m_parent = nullptr;
		p_other.m_left = nullptr;
		p_other.m_right = nullptr;
	}

	~AVLTreeNode() {}

	CONSTEXPR AVLTreeNode& operator=(const AVLTreeNode& p_other)
	{
		m_height = p_other.m_height;
		m_value = p_other.m_value;
		m_parent = p_other.m_parent;
		m_left = p_other.m_left;
		m_right = p_other.m_right;

		return *this;
	}

	CONSTEXPR AVLTreeNode& operator=(AVLTreeNode&& p_other)
	{
		m_height = p_other.m_height;
		m_value = std::move(p_other.m_value);
		m_parent = p_other.m_parent;
		m_left = p_other.m_left;
		m_right = p_other.m_right;

		p_other.m_height = 0;
		p_other.m_value = value_type();
		p_other.m_parent = nullptr;
		p_other.m_left = nullptr;
		p_other.m_right = nullptr;

		return *this;
	}

	// Dereference that allows us to write/read into m_value.
	CONSTEXPR INLINE reference operator*() { return m_value; }
	CONSTEXPR INLINE const_reference operator*() const { return m_value; }

	CONSTEXPR INLINE int& height() { return m_height; }
	CONSTEXPR INLINE int height() const { return m_height; }

	CONSTEXPR INLINE reference value() { return m_value; }
	CONSTEXPR INLINE const_reference value() const { return m_value; }

	CONSTEXPR INLINE AVLTreeNode*& parent() { return m_parent; }
	CONSTEXPR INLINE AVLTreeNode* const& parent() const { return m_parent; }

	CONSTEXPR INLINE AVLTreeNode*& left() { return m_left; }
	CONSTEXPR INLINE AVLTreeNode* const& left() const { return m_left; }

	CONSTEXPR INLINE AVLTreeNode*& right() { return m_right; }
	CONSTEXPR INLINE AVLTreeNode* const& right() const { return m_right; }

	CONSTEXPR INLINE bool operator==(const AVLTreeNode& p_other) const
	{
		return m_height == p_other.m_height && m_value == p_other.m_value && m_parent == p_other.m_parent && m_left == p_other.m_left && m_right == p_other.m_right;
	}
	CONSTEXPR INLINE bool operator!=(const AVLTreeNode& p_other) const { return !(*this == p_other); }

private:
	int m_height;          // The height of the tree.
	value_type m_value;    // The key that this node hold.
	AVLTreeNode* m_parent; // The parent node of this node.
	AVLTreeNode* m_left;   // The left child.
	AVLTreeNode* m_right;  // The right child.
};

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>::AVLTree(const allocator_type& p_allocator) noexcept
	: m_allocator(p_allocator), m_root(nullptr), m_size(0) {}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>::AVLTree(const AVLTree& p_other) noexcept
	: m_allocator(p_other.m_allocator), m_root(nullptr), m_size(0)
{
	p_other.recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
		{ insert(p_node->value()); });
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>::AVLTree(const AVLTree& p_other, const allocator_type& p_allocator) noexcept
	: m_allocator(p_allocator), m_root(nullptr), m_size(0)
{
	p_other.recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
		{ insert(p_node->value()); });
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>::AVLTree(AVLTree&& p_other) noexcept
	: m_allocator(p_other.m_allocator), m_root(p_other.m_root), m_size(p_other.m_size)
{
	p_other.m_allocator = allocator_type();
	p_other.m_root = nullptr;
	p_other.m_size = 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>::AVLTree(AVLTree&& p_other, const allocator_type& p_allocator) noexcept
	: m_allocator(p_allocator), m_root(p_other.m_root), m_size(p_other.m_size)
{
	p_other.m_allocator = allocator_type();
	p_other.m_root = nullptr;
	p_other.m_size = 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>::AVLTree(const std::initializer_list<value_type>& p_elements, const allocator_type& p_allocator) noexcept
	: m_allocator(p_allocator), m_root(nullptr), m_size(0)
{
	for (value_type item : p_elements)
		insert(item);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>& dsaa::AVLTree<Elem, Alloc>::operator=(const AVLTree& p_other)
{
	while (size())
		erase(m_root);

	p_other.recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
		{ insert(p_node->value()); });
	return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>& dsaa::AVLTree<Elem, Alloc>::operator=(AVLTree&& p_other)
{
	while (size())
		erase(m_root);

	m_allocator = p_other.m_allocator;
	m_root = p_other.m_root;
	m_size = p_other.m_size;

	p_other.m_allocator = allocator_type();
	p_other.m_root = nullptr;
	p_other.m_size = 0;

	return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::AVLTree<Elem, Alloc>& dsaa::AVLTree<Elem, Alloc>::operator=(const std::initializer_list<value_type>& p_elements)
{
	while (size())
		erase(m_root);

	for (auto i(p_elements.begin()); p_elements.end() != i; ++i)
		insert(*i);

	return *this;
}

template <typename Elem, typename Alloc>
dsaa::AVLTree<Elem, Alloc>::~AVLTree()
{
	while (size())
		erase(m_root);
}

template <typename Elem, typename Alloc>
CONSTEXPR INLINE typename dsaa::AVLTree<Elem, Alloc>::size_type dsaa::AVLTree<Elem, Alloc>::size() const noexcept
{
	return m_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer& dsaa::AVLTree<Elem, Alloc>::root() noexcept
{
	return m_root;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::const_pointer dsaa::AVLTree<Elem, Alloc>::root() const noexcept
{
	return m_root;
}

template <typename Elem, typename Alloc>
CONSTEXPR int dsaa::AVLTree<Elem, Alloc>::balance_factor(const_pointer p_node) const noexcept
{
	if (!p_node)
		return 0;

	return height(p_node->right()) - height(p_node->left());
}

template <typename Elem, typename Alloc>
CONSTEXPR int dsaa::AVLTree<Elem, Alloc>::height(const_pointer p_node) noexcept
{
	if (!p_node)
		return 0;

	return p_node->height();
}

template <typename Elem, typename Alloc>
CONSTEXPR int dsaa::AVLTree<Elem, Alloc>::height(const_pointer p_node) const noexcept
{
	if (!p_node)
		return 0;

	return p_node->height();
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::iterative_minimum(pointer p_node) noexcept
{
	while (p_node->left())
		p_node = p_node->left();

	return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::iterative_maximum(pointer p_node) noexcept
{
	while (p_node->right())
		p_node = p_node->right();

	return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::recursive_minimum(pointer p_node) noexcept
{
	if (p_node->left())
		return recursive_minimum(p_node->left());

	return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::recursive_maximum(pointer p_node) noexcept
{
	if (p_node->right())
		return recursive_maximum(p_node->right());

	return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::successor(pointer p_node) noexcept
{
	if (p_node->right())
		return iterative_minimum(p_node->right());

	pointer trailing = p_node->parent();
	while (nullptr != trailing && p_node == trailing->right())
	{
		p_node = trailing;
		trailing = trailing->parent();
	}

	return trailing;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::predecessor(pointer p_node) noexcept
{
	if (p_node->left())
		return iterative_maximum(p_node->left());

	pointer trailing = p_node->parent();
	while (nullptr != trailing && p_node == trailing->left())
	{
		p_node = trailing;
		trailing = trailing->parent();
	}

	return trailing;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::recursive_search(pointer p_node, const_reference p_value) noexcept
{
	if (!p_node || p_value == p_node->value())
		return p_node;

	if (p_value < p_node->value())
		return recursive_search(p_node->left(), p_value);
	else
		return recursive_search(p_node->right(), p_value);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::AVLTree<Elem, Alloc>::pointer dsaa::AVLTree<Elem, Alloc>::iterative_search(pointer p_node, const_reference p_value) noexcept
{
	while (p_node && p_value != p_node->value())
	{
		if (p_value < p_node->value())
			p_node = p_node->left();
		else
			p_node = p_node->right();
	}

	return p_node;
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::recursive_preorder_tree_walk(pointer& p_node, Action p_action)
{
	if (p_node)
	{
		p_action(p_node);
		recursive_preorder_tree_walk(p_node->left(), p_action);
		recursive_preorder_tree_walk(p_node->right(), p_action);
	}
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::recursive_preorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
	if (p_node)
	{
		p_action(p_node);
		recursive_preorder_tree_walk(p_node->left(), p_action);
		recursive_preorder_tree_walk(p_node->right(), p_action);
	}
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::recursive_inorder_tree_walk(pointer& p_node, Action p_action)
{
	if (p_node)
	{
		recursive_inorder_tree_walk(p_node->left(), p_action);
		p_action(p_node);
		recursive_inorder_tree_walk(p_node->right(), p_action);
	}
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::recursive_inorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
	if (p_node)
	{
		recursive_inorder_tree_walk(p_node->left(), p_action);
		p_action(p_node);
		recursive_inorder_tree_walk(p_node->right(), p_action);
	}
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::recursive_postorder_tree_walk(pointer& p_node, Action p_action)
{
	if (p_node)
	{
		recursive_postorder_tree_walk(p_node->left(), p_action);
		recursive_postorder_tree_walk(p_node->right(), p_action);
		p_action(p_node);
	}
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::recursive_postorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
	if (p_node)
	{
		recursive_postorder_tree_walk(p_node->left(), p_action);
		recursive_postorder_tree_walk(p_node->right(), p_action);
		p_action(p_node);
	}
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::left_rotate(pointer p_node) noexcept
{
	// I assumes right child is not null.
	// p_node can be any node in the tree whose right child is not null.
	pointer right_child(p_node->right());
	right_child->parent() = p_node->parent();
	if (nullptr == p_node->parent())
		m_root = right_child;
	else if (p_node->parent()->left() == p_node)
		p_node->parent()->left() = right_child;
	else
		p_node->parent()->right() = right_child;

	p_node->parent() = right_child;

	p_node->right() = right_child->left();
	if (nullptr != right_child->left())
		right_child->left()->parent() = p_node;

	right_child->left() = p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::right_rotate(pointer p_node) noexcept
{
	// I assumes left child is not null.
	// p_node can be any node in the tree whose right child is not null.
	pointer left_child(p_node->left());
	left_child->parent() = p_node->parent();
	if (nullptr == p_node->parent())
		m_root = left_child;
	else if (p_node->parent()->left() == p_node)
		p_node->parent()->left() = left_child;
	else
		p_node->parent()->right() = left_child;

	p_node->parent() = left_child;

	p_node->left() = left_child->right();
	if (nullptr != left_child->right())
		left_child->right()->parent() = p_node;

	left_child->right() = p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::insert(const_reference p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	// Height counted by node so value of height start from 1.
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, 1, p_value, nullptr, nullptr, nullptr);

	pointer direction = m_root;
	pointer trailing = nullptr;
	while (direction)
	{
		trailing = direction;
		if (p_value < direction->value())
			direction = direction->left();
		else
			direction = direction->right();
	}

	new_node->parent() = trailing;

	if (nullptr == m_root)
		m_root = new_node;
	else if (p_value < trailing->value())
		trailing->left() = new_node;
	else
		trailing->right() = new_node;
	++m_size;

	insert_fixup(new_node);
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::insert_fixup(pointer p_node)
{
	pointer tracing(p_node->parent());
	pointer child(p_node);
	pointer grand_child(nullptr);

	// Update height.
	while (tracing)
	{
		tracing->height() = std::max(height(tracing->left()), height(tracing->right())) + 1;

		// This subtree is balanced, get out.
		if (0 == balance_factor(tracing))
			return;

		// Exit and fix the height, the balance factor is not in between [-1, 0, 1] that makes an invalid AVL tree.
		if (balance_factor(tracing) < -1 || 1 < balance_factor(tracing))
			break;

		grand_child = child;
		child = tracing;
		tracing = tracing->parent();
	}

	// Fix height difference.
	while (tracing && balance_factor(tracing) < -1 || 1 < balance_factor(tracing))
	{
		if (child == tracing->left())
		{
			// Case 1: grandchild located on left side of tracing, and is left child of its parent.
			if (grand_child == child->left())
			{
				right_rotate(tracing);

				tracing->height() = std::max(height(tracing->left()), height(tracing->right())) + 1;
				child->height() = std::max(height(child->left()), height(child->right())) + 1;
			}
			// Case 2: grandchild located on left side of tracing, and is right child of its parent.
			// Convert it into case 1.
			else
			{
				left_rotate(child);

				child->height() = std::max(height(child->left()), height(child->right())) + 1;
				grand_child->height() = std::max(height(grand_child->left()), height(grand_child->right())) + 1;

				child = tracing->left();
				grand_child = tracing->left()->left();
			}
		}
		else
		{
			// Case 3: grandchild located on right side of tracing, and is right child of its parent.
			if (grand_child == child->right())
			{
				left_rotate(tracing);

				tracing->height() = std::max(height(tracing->left()), height(tracing->right())) + 1;
				child->height() = std::max(height(child->left()), height(child->right())) + 1;
			}
			// Case 4: grandchild located on right side of tracing, and is left child of its parent.
			// Convert it into case 3.
			else
			{
				right_rotate(child);
				child->height() = std::max(height(child->left()), height(child->right())) + 1;
				grand_child->height() = std::max(height(grand_child->left()), height(grand_child->right())) + 1;

				child = tracing->right();
				grand_child = tracing->right()->right();
			}
		}
	}
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::erase(pointer& p_node)
{
	// The moment p_node transplant with its child, p_node will become invalid.
	pointer substitute(p_node);
	pointer tracker(p_node->parent());


	if (nullptr == p_node->left())
		transplant(p_node, p_node->right());
	else if (nullptr == p_node->right())
		transplant(p_node, p_node->left());
	else
	{
		pointer succ = iterative_minimum(p_node->right());

		if (succ->parent() == p_node)
		{
			tracker = succ;
			tracker->parent() = nullptr;
		}
		else
		{
			tracker = succ->parent();

			transplant(succ, succ->right());
			succ->right() = p_node->right();
			succ->right()->parent() = succ;
		}
		transplant(p_node, succ);
		succ->left() = substitute->left();
		succ->left()->parent() = succ;
		succ->parent() = nullptr;
	}
	if (p_node == m_root && p_node)
		p_node->parent() = nullptr;

	std::allocator_traits<allocator_type>::destroy(m_allocator, substitute);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, substitute, 1);
	--m_size;

	if (tracker)
		erase_fixup(tracker);
}

// Only needs to do the invert things with insert.
template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::erase_fixup(pointer p_node)
{
	pointer child((height(p_node->left()) < height(p_node->right())) ? p_node->right() : p_node->left());
	pointer grand_child(nullptr);
	if (child)
	{
		// This only matters if rotations happen. Don't clarify this check will make
		// unnecessarily two or more rotations if child == p_node->right().
		if (child == p_node->left())
			grand_child = (height(child->left()) < height(child->right())) ? child->right() : child->left();
		else
			grand_child = (height(child->right()) < height(child->left())) ? child->left() : child->right();
	}

	// Update height.
	while (p_node)
	{
		p_node->height() = std::max(height(p_node->left()), height(p_node->right())) + 1;

		// Fix unbalance tree.
		while (balance_factor(p_node) < -1 || 1 < balance_factor(p_node))
		{
			if (child == p_node->left())
			{
				// Case 1: grandchild located on left side of p_node, and is left child of its parent.
				if (grand_child == child->left())
				{
					right_rotate(p_node);
					p_node->height() = std::max(height(p_node->left()), height(p_node->right())) + 1;
				}
				// Case 2: grandchild located on left side of p_node, and is right child of its parent.
				// Convert it into case 1.
				else
				{
					left_rotate(child);

					child->height() = std::max(height(child->left()), height(child->right())) + 1;
					grand_child->height() = std::max(height(grand_child->left()), height(grand_child->right())) + 1;

					child = p_node->left();
					grand_child = p_node->left()->left();
				}
			}
			else
			{
				// Case 3: grandchild located on right side of p_node, and is right child of its parent.
				if (grand_child == child->right())
				{
					left_rotate(p_node);

					p_node->height() = std::max(height(p_node->left()), height(p_node->right())) + 1;
				}
				// Case 4: grandchild located on right side of p_node, and is left child of its parent.
				// Convert it into case 3.
				else
				{
					right_rotate(child);
					child->height() = std::max(height(child->left()), height(child->right())) + 1;
					grand_child->height() = std::max(height(grand_child->left()), height(grand_child->right())) + 1;

					child = p_node->right();
					grand_child = p_node->right()->right();
				}
			}
		}

		grand_child = child;
		child = p_node;
		p_node = p_node->parent();
	}
}

// Auxiliary method for earsing node. This method does not handle child transplant.
template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::AVLTree<Elem, Alloc>::transplant(pointer& p_node, pointer& p_child) noexcept
{
	if (nullptr == p_node->parent())
		m_root = p_child;
	else if (p_node == p_node->parent()->left())
		p_node->parent()->left() = p_child;
	else
		p_node->parent()->right() = p_child;

	if (p_child)
		p_child->parent() = p_node->parent();
}

#endif //!DAAA_AVL_TREE_H
