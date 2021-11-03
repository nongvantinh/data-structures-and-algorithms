#ifndef DAAA_BINARY_TREE_H
#define DAAA_BINARY_TREE_H

#include <memory>
#include <functional>
#include <initializer_list>
#include <iostream>

#include "dsaaTypedefs.h"

namespace dsaa
{
    template <typename T>
    class BinaryTreeNode;

    template <typename Elem, typename Alloc = std::allocator<BinaryTreeNode<Elem>>>
    class BinaryTree
    {
    public:
        using value_type = Elem;
        using allocator_type = Alloc;
        using reference = value_type &;
        using const_reference = value_type const &;
        using pointer = BinaryTreeNode<value_type> *;
        using const_pointer = BinaryTreeNode<value_type> const *;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;

        // Creates a container with no element.
        CONSTEXPR BinaryTree(const allocator_type &p_allocator = allocator_type()) noexcept;

        CONSTEXPR BinaryTree(const BinaryTree &p_other) noexcept;
        CONSTEXPR BinaryTree(const BinaryTree &p_other, const allocator_type &p_allocator) noexcept;
        CONSTEXPR BinaryTree(BinaryTree &&p_other) noexcept;
        CONSTEXPR BinaryTree(BinaryTree &&p_other, const allocator_type &p_allocator) noexcept;
        CONSTEXPR BinaryTree(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type()) noexcept;

        CONSTEXPR BinaryTree &operator=(const BinaryTree &p_other);
        CONSTEXPR BinaryTree &operator=(BinaryTree &&p_other);
        CONSTEXPR BinaryTree &operator=(const std::initializer_list<value_type> &p_elements);
        // Destroys all elements and clean used space.
        ~BinaryTree();

        CONSTEXPR INLINE pointer &root() noexcept;
        CONSTEXPR INLINE const_pointer root() const noexcept;
        CONSTEXPR INLINE size_type size() const noexcept;

        CONSTEXPR pointer iterative_minimum(pointer p_node) noexcept;
        CONSTEXPR pointer iterative_maximum(pointer p_node) noexcept;
        CONSTEXPR pointer recursive_minimum(pointer p_node) noexcept;
        CONSTEXPR pointer recursive_maximum(pointer p_node) noexcept;
        CONSTEXPR pointer successor(pointer p_node) noexcept;
        CONSTEXPR pointer predecessor(pointer p_node) noexcept;
        CONSTEXPR pointer iterative_search(pointer p_node, const_reference p_value) noexcept;
        CONSTEXPR pointer recursive_search(pointer p_node, const_reference p_value) noexcept;
        template <typename Action>
        CONSTEXPR void recursive_preorder_tree_walk(pointer &p_node, Action p_action);
        template <typename Action>
        CONSTEXPR void recursive_preorder_tree_walk(const_pointer p_node, Action p_action) const noexcept;
        template <typename Action>
        CONSTEXPR void recursive_inorder_tree_walk(pointer &p_node, Action p_action);
        template <typename Action>
        CONSTEXPR void recursive_inorder_tree_walk(const_pointer p_node, Action p_action) const noexcept;
        template <typename Action>
        CONSTEXPR void recursive_postorder_tree_walk(pointer &p_node, Action p_action);
        template <typename Action>
        CONSTEXPR void recursive_postorder_tree_walk(const_pointer p_node, Action p_action) const noexcept;

        // p_other will take place of p_node in tree.
        CONSTEXPR void transplant(pointer &p_node, pointer &p_other) noexcept;

        CONSTEXPR void insert(const_reference p_value);
        CONSTEXPR void erase(pointer &p_node);

    protected:
        allocator_type m_allocator;
        pointer m_root;
        size_type m_size;
    };
}

template <typename T>
class dsaa::BinaryTreeNode
{
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

    CONSTEXPR BinaryTreeNode(const_reference p_value = value_type()) noexcept : m_value(p_value), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
    CONSTEXPR BinaryTreeNode(value_type &&p_value) noexcept : m_value(std::move(p_value)), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
    CONSTEXPR BinaryTreeNode(const_reference p_value, BinaryTreeNode *p_parent, BinaryTreeNode *p_left, BinaryTreeNode *p_right) noexcept : m_value(p_value), m_parent(p_parent), m_left(p_left), m_right(p_right) {}
    CONSTEXPR BinaryTreeNode(value_type &&p_value, BinaryTreeNode *p_parent, BinaryTreeNode *p_left, BinaryTreeNode *p_right) noexcept : m_value(std::move(p_value)), m_parent(p_parent), m_left(p_left), m_right(p_right) { p_value = value_type(); }

    CONSTEXPR BinaryTreeNode(const BinaryTreeNode &p_other) noexcept : m_value(p_other.m_value), m_parent(p_other.m_parent), m_left(p_other.m_left), m_right(p_other.m_right) {}
    CONSTEXPR BinaryTreeNode(BinaryTreeNode &&p_other) noexcept : m_value(std::move(p_other.m_value)), m_parent(p_other.m_parent), m_left(p_other.m_left), m_right(p_other.m_right)
    {
        p_other.m_value = value_type();
        p_other.m_parent = nullptr;
        p_other.m_left = nullptr;
        p_other.m_right = nullptr;
    }

    ~BinaryTreeNode() {}

    CONSTEXPR BinaryTreeNode &operator=(const BinaryTreeNode &p_other)
    {
        m_value = p_other.m_value;
        m_parent = p_other.m_parent;
        m_left = p_other.m_left;
        m_right = p_other.m_right;

        return *this;
    }

    CONSTEXPR BinaryTreeNode &operator=(BinaryTreeNode &&p_other)
    {
        m_value = std::move(p_other.m_value);
        m_parent = p_other.m_parent;
        m_left = p_other.m_left;
        m_right = p_other.m_right;

        p_other.m_value = value_type();
        p_other.m_parent = nullptr;
        p_other.m_left = nullptr;
        p_other.m_right = nullptr;

        return *this;
    }

    // Dereference that allows us to write/read into m_value.
    CONSTEXPR INLINE reference operator*() { return m_value; }
    CONSTEXPR INLINE const_reference operator*() const { return m_value; }

    CONSTEXPR INLINE BinaryTreeNode *&parent() { return m_parent; }
    CONSTEXPR INLINE BinaryTreeNode *const &parent() const { return m_parent; }

    CONSTEXPR INLINE BinaryTreeNode *&left() { return m_left; }
    CONSTEXPR INLINE BinaryTreeNode *const &left() const { return m_left; }

    CONSTEXPR INLINE BinaryTreeNode *&right() { return m_right; }
    CONSTEXPR INLINE BinaryTreeNode *const &right() const { return m_right; }

    CONSTEXPR INLINE reference value() { return m_value; }
    CONSTEXPR INLINE const_reference value() const { return m_value; }

    CONSTEXPR INLINE bool operator==(const BinaryTreeNode &p_other) const
    {
        return m_parent == p_other.m_parent && m_left == p_other.m_left && m_right == p_other.m_right && m_value == p_other.m_value;
    }
    CONSTEXPR INLINE bool operator!=(const BinaryTreeNode &p_other) const { return !(*this == p_other); }

protected:
    value_type m_value;       // The key that this node hold.
    BinaryTreeNode *m_parent; // The parent node of this node.
    BinaryTreeNode *m_left;   // The left child.
    BinaryTreeNode *m_right;  // The right child.
};

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::BinaryTree(const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(nullptr), m_size(0) {}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::BinaryTree(const BinaryTree &p_other) noexcept
    : m_allocator(p_other.m_allocator), m_root(nullptr), m_size(0)
{
    recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
                                 { insert(p_node->value()); });
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::BinaryTree(const BinaryTree &p_other, const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(nullptr), m_size(0)
{
    recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
                                 { insert(p_node->value()); });
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::BinaryTree(BinaryTree &&p_other) noexcept
    : m_allocator(p_other.m_allocator), m_root(p_other.m_root), m_size(p_other.m_size)
{
    p_other.m_allocator = allocator_type();
    p_other.m_root = nullptr;
    p_other.m_size = 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::BinaryTree(BinaryTree &&p_other, const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(p_other.m_root), m_size(p_other.m_size)
{
    p_other.m_allocator = allocator_type();
    p_other.m_root = nullptr;
    p_other.m_size = 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::BinaryTree(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(nullptr), m_size(0)
{
    for (value_type item : p_elements)
        insert(item);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc> &dsaa::BinaryTree<Elem, Alloc>::operator=(const BinaryTree &p_other)
{
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });

    recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
                                 { insert(p_node->value()); });
    return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc> &dsaa::BinaryTree<Elem, Alloc>::operator=(BinaryTree &&p_other)
{
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });

    m_allocator = p_other.m_allocator;
    m_root = p_other.m_root;
    m_size = p_other.m_size;

    p_other.m_allocator = allocator_type();
    p_other.m_root = nullptr;
    p_other.m_size = 0;

    return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc> &dsaa::BinaryTree<Elem, Alloc>::operator=(const std::initializer_list<value_type> &p_elements)
{
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });

    for (auto i(p_elements.begin()); p_elements.end() != i; ++i)
        insert(*i);

    return *this;
}

template <typename Elem, typename Alloc>
dsaa::BinaryTree<Elem, Alloc>::~BinaryTree()
{
    // while (size())
    // erase(m_root);
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });
}

template <typename Elem, typename Alloc>
CONSTEXPR INLINE dsaa::BinaryTree<Elem, Alloc>::size_type dsaa::BinaryTree<Elem, Alloc>::size() const noexcept
{
    return m_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer &dsaa::BinaryTree<Elem, Alloc>::root() noexcept
{
    return m_root;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::const_pointer dsaa::BinaryTree<Elem, Alloc>::root() const noexcept
{
    return m_root;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::iterative_minimum(pointer p_node) noexcept
{
    while (p_node->left())
        p_node = p_node->left();

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::iterative_maximum(pointer p_node) noexcept
{
    while (p_node->right())
        p_node = p_node->right();

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::recursive_minimum(pointer p_node) noexcept
{
    if (p_node->left())
        return recursive_minimum(p_node->left());

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::recursive_maximum(pointer p_node) noexcept
{
    if (p_node->right())
        return recursive_maximum(p_node->right());

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::successor(pointer p_node) noexcept
{
    if (p_node->right())
        return iterative_minimum(p_node->right());

    pointer trailing = p_node->parent();
    while (trailing && p_node == trailing->right())
    {
        p_node = trailing;
        trailing = trailing->parent();
    }

    return trailing;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::predecessor(pointer p_node) noexcept
{
    if (p_node->left())
        return iterative_maximum(p_node->left());

    pointer trailing = p_node->parent();
    while (trailing && p_node == trailing->left())
    {
        p_node = trailing;
        trailing = trailing->parent();
    }

    return trailing;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::recursive_search(pointer p_node, const_reference p_value) noexcept
{
    if (!p_node || p_value == p_node->value())
        return p_node;

    if (p_value < p_node->value())
        return recursive_search(p_node->left(), p_value);
    else
        return recursive_search(p_node->right(), p_value);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::BinaryTree<Elem, Alloc>::pointer dsaa::BinaryTree<Elem, Alloc>::iterative_search(pointer p_node, const_reference p_value) noexcept
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
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::recursive_preorder_tree_walk(pointer &p_node, Action p_action)
{
    if (nullptr != p_node)
    {
        p_action(p_node);
        recursive_preorder_tree_walk(p_node->left(), p_action);
        recursive_preorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::recursive_preorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
    if (nullptr != p_node)
    {
        p_action(p_node);
        recursive_preorder_tree_walk(p_node->left(), p_action);
        recursive_preorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::recursive_inorder_tree_walk(pointer &p_node, Action p_action)
{
    if (nullptr != p_node)
    {
        recursive_inorder_tree_walk(p_node->left(), p_action);
        p_action(p_node);
        recursive_inorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::recursive_inorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
    if (nullptr != p_node)
    {
        recursive_inorder_tree_walk(p_node->left(), p_action);
        p_action(p_node);
        recursive_inorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::recursive_postorder_tree_walk(pointer &p_node, Action p_action)
{
    if (nullptr != p_node)
    {
        recursive_postorder_tree_walk(p_node->left(), p_action);
        recursive_postorder_tree_walk(p_node->right(), p_action);
        p_action(p_node);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::recursive_postorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
    if (nullptr != p_node)
    {
        recursive_postorder_tree_walk(p_node->left(), p_action);
        recursive_postorder_tree_walk(p_node->right(), p_action);
        p_action(p_node);
    }
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::insert(const_reference p_value)
{
    pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
    std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_value);

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
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::erase(pointer &p_node)
{
    // The moment p_node transplant with its child, p_node will become invalid.
    pointer substitute(p_node);
    if (!p_node->left())
        transplant(p_node, p_node->right());
    else if (!p_node->right())
        transplant(p_node, p_node->left());
    else
    {
        pointer succ = iterative_minimum(p_node->right());

        if (succ->parent() != p_node)
        {
            transplant(succ, succ->right());
            succ->right() = p_node->right();
            succ->right()->parent() = succ;
        }
        transplant(p_node, succ);
        succ->left() = p_node->left();
        succ->left()->parent() = succ;
    }
    std::allocator_traits<allocator_type>::destroy(m_allocator, substitute);
    std::allocator_traits<allocator_type>::deallocate(m_allocator, substitute, 1);
    --m_size;
}

// Auxiliary method for earsing node. This method does not handle child transplant.
template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::BinaryTree<Elem, Alloc>::transplant(pointer &p_node, pointer &p_child) noexcept
{
    if (!p_node->parent())
        m_root = p_child;
    else if (p_node == p_node->parent()->left())
        p_node->parent()->left() = p_child;
    else
        p_node->parent()->right() = p_child;

    if (p_child)
        p_child->parent() = p_node->parent();
}

#endif //!DAAA_BINARY_TREE_H