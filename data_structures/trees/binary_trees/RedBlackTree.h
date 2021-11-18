/*
Red black tree properties:
    1/ Every node either red or black.
    2/ The root is black.
    3/ All leafs (nullptr or sentinel node) is black.
    4/ A red node don't have a red child (both of its children are black).
    5/ For each node, all simple paths from the node to decendant leaves
        contain the same number of black nodes.
*/

#ifndef DSAA_RED_BLACK_TREE_H
#define DSAA_RED_BLACK_TREE_H

#include <memory>

#include "dsaaTypedefs.h"
namespace dsaa
{
    template <typename T>
    class RedBlackTreeNode;

    template <typename Elem, typename Alloc = std::allocator<RedBlackTreeNode<Elem>>>
    class RedBlackTree
    {
    public:
        using value_type = Elem;
        using allocator_type = Alloc;
        using reference = value_type &;
        using const_reference = value_type const &;
        using pointer = RedBlackTreeNode<value_type> *;
        using const_pointer = RedBlackTreeNode<value_type> const *;
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;

        // Creates a container with no element.
        CONSTEXPR RedBlackTree(const allocator_type &p_allocator = allocator_type()) noexcept;
        CONSTEXPR RedBlackTree(const RedBlackTree &p_other) noexcept;
        CONSTEXPR RedBlackTree(const RedBlackTree &p_other, const allocator_type &p_allocator) noexcept;
        CONSTEXPR RedBlackTree(RedBlackTree &&p_other) noexcept;
        CONSTEXPR RedBlackTree(RedBlackTree &&p_other, const allocator_type &p_allocator) noexcept;
        CONSTEXPR RedBlackTree(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type()) noexcept;

        CONSTEXPR RedBlackTree &operator=(const RedBlackTree &p_other);
        CONSTEXPR RedBlackTree &operator=(RedBlackTree &&p_other);
        CONSTEXPR RedBlackTree &operator=(const std::initializer_list<value_type> &p_elements);
        // Destroys all elements and clean used space.
        ~RedBlackTree();

        CONSTEXPR INLINE allocator_type allocator() const noexcept;
        CONSTEXPR INLINE pointer &root() noexcept;
        CONSTEXPR INLINE const_pointer root() const noexcept;
        CONSTEXPR INLINE const_pointer sentinel() const noexcept;
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

        // The number of black nodes on any simple path from, but not including, a node x down to a leaf.
        CONSTEXPR INLINE size_type black_height(const_pointer &p_node) const;

        CONSTEXPR void left_rotate(pointer p_node) noexcept;
        CONSTEXPR void right_rotate(pointer p_node) noexcept;

        CONSTEXPR void insert(const_reference p_value);
        CONSTEXPR void insert_fixup(pointer p_node);

        CONSTEXPR void erase(pointer &p_node);
        CONSTEXPR void erase_fixup(pointer p_node);
        // p_other will take place of p_node in tree.
        CONSTEXPR void transplant(pointer &p_node, pointer &p_other) noexcept;

    private:
        allocator_type m_allocator;
        pointer m_root;
        const_pointer m_sentinel; // The only node that left child and right child is nullptr.
        size_type m_size;
    };
} // namespace dsaa

template <typename T>
class dsaa::RedBlackTreeNode
{
public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;

    CONSTEXPR RedBlackTreeNode(bool p_is_red = false, const_reference p_value = value_type()) noexcept : m_is_red(p_is_red), m_value(p_value), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
    CONSTEXPR RedBlackTreeNode(bool p_is_red, value_type &&p_value) noexcept : m_is_red(p_is_red), m_value(std::move(p_value)), m_parent(nullptr), m_left(nullptr), m_right(nullptr) {}
    CONSTEXPR RedBlackTreeNode(bool p_is_red, const_reference p_value, RedBlackTreeNode *p_parent, RedBlackTreeNode *p_left, RedBlackTreeNode *p_right) noexcept : m_is_red(p_is_red), m_value(p_value), m_parent(p_parent), m_left(p_left), m_right(p_right) {}
    CONSTEXPR RedBlackTreeNode(bool p_is_red, value_type &&p_value, RedBlackTreeNode *p_parent, RedBlackTreeNode *p_left, RedBlackTreeNode *p_right) noexcept : m_is_red(p_is_red), m_value(std::move(p_value)), m_parent(p_parent), m_left(p_left), m_right(p_right) { p_value = value_type(); }

    CONSTEXPR RedBlackTreeNode(const RedBlackTreeNode &p_other) noexcept : m_is_red(p_other.m_is_red), m_value(p_other.m_value), m_parent(p_other.m_parent), m_left(p_other.m_left), m_right(p_other.m_right) {}
    CONSTEXPR RedBlackTreeNode(RedBlackTreeNode &&p_other) noexcept : m_is_red(p_other.m_is_red), m_value(std::move(p_other.m_value)), m_parent(p_other.m_parent), m_left(p_other.m_left), m_right(p_other.m_right)
    {
        p_other.m_is_red = false;
        p_other.m_value = value_type();
        p_other.m_parent = nullptr;
        p_other.m_left = nullptr;
        p_other.m_right = nullptr;
    }

    ~RedBlackTreeNode() {}

    CONSTEXPR RedBlackTreeNode &operator=(const RedBlackTreeNode &p_other)
    {
        m_is_red = p_other.m_is_red;
        m_value = p_other.m_value;
        m_parent = p_other.m_parent;
        m_left = p_other.m_left;
        m_right = p_other.m_right;

        return *this;
    }

    CONSTEXPR RedBlackTreeNode &operator=(RedBlackTreeNode &&p_other)
    {
        m_is_red = p_other.m_is_red;
        m_value = std::move(p_other.m_value);
        m_parent = p_other.m_parent;
        m_left = p_other.m_left;
        m_right = p_other.m_right;

        p_other.m_is_red = false;
        p_other.m_value = value_type();
        p_other.m_parent = nullptr;
        p_other.m_left = nullptr;
        p_other.m_right = nullptr;

        return *this;
    }

    // Dereference that allows us to write/read into m_value.
    CONSTEXPR INLINE reference operator*() { return m_value; }
    CONSTEXPR INLINE const_reference operator*() const { return m_value; }

    CONSTEXPR INLINE bool &is_red() { return m_is_red; }
    CONSTEXPR INLINE bool is_red() const { return m_is_red; }

    CONSTEXPR INLINE reference value() { return m_value; }
    CONSTEXPR INLINE const_reference value() const { return m_value; }

    CONSTEXPR INLINE RedBlackTreeNode *&parent() { return m_parent; }
    CONSTEXPR INLINE RedBlackTreeNode *const &parent() const { return m_parent; }

    CONSTEXPR INLINE RedBlackTreeNode *&left() { return m_left; }
    CONSTEXPR INLINE RedBlackTreeNode *const &left() const { return m_left; }

    CONSTEXPR INLINE RedBlackTreeNode *&right() { return m_right; }
    CONSTEXPR INLINE RedBlackTreeNode *const &right() const { return m_right; }

    CONSTEXPR INLINE bool operator==(const RedBlackTreeNode &p_other) const
    {
        return m_is_red == p_other.m_is_red && m_value == p_other.m_value && m_parent == p_other.m_parent && m_left == p_other.m_left && m_right == p_other.m_right;
    }
    CONSTEXPR INLINE bool operator!=(const RedBlackTreeNode &p_other) const { return !(*this == p_other); }

private:
    bool m_is_red;            // The color of red black tree, either red or black.
    value_type m_value;       // The key that this node hold.
    RedBlackTreeNode *m_parent; // The parent node of this node.
    RedBlackTreeNode *m_left;   // The left child.
    RedBlackTreeNode *m_right;  // The right child.
};

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::RedBlackTree(const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(nullptr), m_sentinel(nullptr), m_size(0)
{
    m_root = m_sentinel = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
    std::allocator_traits<allocator_type>::construct(m_allocator, m_sentinel, false, value_type(), nullptr, nullptr, nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::RedBlackTree(const RedBlackTree &p_other) noexcept
    : m_allocator(p_other.m_allocator), m_root(nullptr), m_sentinel(nullptr), m_size(0)
{
    m_root = m_sentinel = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
    std::allocator_traits<allocator_type>::construct(m_allocator, m_sentinel, false, value_type(), nullptr, nullptr, nullptr);

    recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
                                 { insert(p_node->value()); });
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::RedBlackTree(const RedBlackTree &p_other, const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(nullptr), m_sentinel(nullptr), m_size(0)
{
    m_root = m_sentinel = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
    // Property 3 states: all leaf nodes(the sentinels) must be black.
    std::allocator_traits<allocator_type>::construct(m_allocator, m_sentinel, false, value_type(), nullptr, nullptr, nullptr);

    recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
                                 { insert(p_node->value()); });
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::RedBlackTree(RedBlackTree &&p_other) noexcept
    : m_allocator(p_other.m_allocator), m_root(p_other.m_root), m_sentinel(p_other.m_sentinel), m_size(p_other.m_size)
{
    p_other.m_allocator = allocator_type();
    p_other.m_root = nullptr;
    p_other.m_sentinel = nullptr;
    p_other.m_size = 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::RedBlackTree(RedBlackTree &&p_other, const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(p_other.m_root), m_sentinel(p_other.m_sentinel), m_size(p_other.m_size)
{
    p_other.m_allocator = allocator_type();
    p_other.m_root = nullptr;
    p_other.m_sentinel = nullptr;
    p_other.m_size = 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::RedBlackTree(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator) noexcept
    : m_allocator(p_allocator), m_root(nullptr), m_sentinel(nullptr), m_size(0)
{
    m_root = m_sentinel = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
    // Property 3 states: all leaf nodes(the sentinels) must be black.
    std::allocator_traits<allocator_type>::construct(m_allocator, m_sentinel, false, value_type(), nullptr, nullptr, nullptr);

    for (value_type item : p_elements)
        insert(item);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc> &dsaa::RedBlackTree<Elem, Alloc>::operator=(const RedBlackTree &p_other)
{
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });

    recursive_preorder_tree_walk(p_other.root(), [&](const_pointer p_node)
                                 { insert(p_node->value()); });
    return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc> &dsaa::RedBlackTree<Elem, Alloc>::operator=(RedBlackTree &&p_other)
{
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });
    std::allocator_traits<allocator_type>::destroy(m_allocator, m_sentinel);
    std::allocator_traits<allocator_type>::deallocate(m_allocator, m_sentinel, 1);

    m_allocator = p_other.m_allocator;
    m_root = p_other.m_root;
    m_sentinel = p_other.m_sentinel;
    m_size = p_other.m_size;

    p_other.m_allocator = allocator_type();
    p_other.m_root = nullptr;
    p_other.m_sentinel = nullptr;
    p_other.m_size = 0;

    return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc> &dsaa::RedBlackTree<Elem, Alloc>::operator=(const std::initializer_list<value_type> &p_elements)
{
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });

    for (auto i(p_elements.begin()); p_elements.end() != i; ++i)
        insert(*i);

    return *this;
}

template <typename Elem, typename Alloc>
dsaa::RedBlackTree<Elem, Alloc>::~RedBlackTree()
{
    // while (size())
    // erase(m_root);
    recursive_postorder_tree_walk(m_root, [&](pointer &p_node)
                                  { erase(p_node); });

    std::allocator_traits<allocator_type>::destroy(m_allocator, m_sentinel);
    std::allocator_traits<allocator_type>::deallocate(m_allocator, m_sentinel, 1);
}

template <typename Elem, typename Alloc>
CONSTEXPR INLINE dsaa::RedBlackTree<Elem, Alloc>::size_type dsaa::RedBlackTree<Elem, Alloc>::size() const noexcept
{
    return m_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer &dsaa::RedBlackTree<Elem, Alloc>::root() noexcept
{
    return m_root;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::const_pointer dsaa::RedBlackTree<Elem, Alloc>::root() const noexcept
{
    return m_root;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::const_pointer dsaa::RedBlackTree<Elem, Alloc>::sentinel() const noexcept
{
    return m_sentinel;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::iterative_minimum(pointer p_node) noexcept
{
    while (sentinel() != p_node->left())
        p_node = p_node->left();

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::iterative_maximum(pointer p_node) noexcept
{
    while (sentinel() != p_node->right())
        p_node = p_node->right();

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::recursive_minimum(pointer p_node) noexcept
{
    if (sentinel() != p_node->left())
        return recursive_minimum(p_node->left());

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::recursive_maximum(pointer p_node) noexcept
{
    if (sentinel() != p_node->right())
        return recursive_maximum(p_node->right());

    return p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::successor(pointer p_node) noexcept
{
    if (sentinel() != p_node->right())
        return iterative_minimum(p_node->right());

    pointer trailing = p_node->parent();
    while (sentinel() != trailing && p_node == trailing->right())
    {
        p_node = trailing;
        trailing = trailing->parent();
    }

    return trailing;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::predecessor(pointer p_node) noexcept
{
    if (sentinel() != p_node->left())
        return iterative_maximum(p_node->left());

    pointer trailing = p_node->parent();
    while (sentinel() != trailing && p_node == trailing->left())
    {
        p_node = trailing;
        trailing = trailing->parent();
    }

    return trailing;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::recursive_search(pointer p_node, const_reference p_value) noexcept
{
    if (!p_node || sentinel() == p_node || p_value == p_node->value())
        return p_node;

    if (p_value < p_node->value())
        return recursive_search(p_node->left(), p_value);
    else
        return recursive_search(p_node->right(), p_value);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::pointer dsaa::RedBlackTree<Elem, Alloc>::iterative_search(pointer p_node, const_reference p_value) noexcept
{
    while (sentinel() != p_node && p_value != p_node->value())
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
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::recursive_preorder_tree_walk(pointer &p_node, Action p_action)
{
    if (sentinel() != p_node)
    {
        p_action(p_node);
        recursive_preorder_tree_walk(p_node->left(), p_action);
        recursive_preorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::recursive_preorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
    if (sentinel() != p_node)
    {
        p_action(p_node);
        recursive_preorder_tree_walk(p_node->left(), p_action);
        recursive_preorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::recursive_inorder_tree_walk(pointer &p_node, Action p_action)
{
    if (sentinel() != p_node)
    {
        recursive_inorder_tree_walk(p_node->left(), p_action);
        p_action(p_node);
        recursive_inorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::recursive_inorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
    if (sentinel() != p_node)
    {
        recursive_inorder_tree_walk(p_node->left(), p_action);
        p_action(p_node);
        recursive_inorder_tree_walk(p_node->right(), p_action);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::recursive_postorder_tree_walk(pointer &p_node, Action p_action)
{
    if (sentinel() != p_node)
    {
        recursive_postorder_tree_walk(p_node->left(), p_action);
        recursive_postorder_tree_walk(p_node->right(), p_action);
        p_action(p_node);
    }
}

template <typename Elem, typename Alloc>
template <typename Action>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::recursive_postorder_tree_walk(const_pointer p_node, Action p_action) const noexcept
{
    if (sentinel() != p_node)
    {
        recursive_postorder_tree_walk(p_node->left(), p_action);
        recursive_postorder_tree_walk(p_node->right(), p_action);
        p_action(p_node);
    }
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::RedBlackTree<Elem, Alloc>::size_type dsaa::RedBlackTree<Elem, Alloc>::black_height(const_pointer &p_node) const
{
    size_type count(0);
    while (p_node != sentinel())
    {
        p_node = p_node->left();
        if (!p_node->is_red())
            ++count;
    }

    return count;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::left_rotate(pointer p_node) noexcept
{
    // I assumes right child is not null.
    // p_node can be any node in the tree whose right child is not null.
    pointer right_child(p_node->right());
    right_child->parent() = p_node->parent();
    if (sentinel() == p_node->parent())
        m_root = right_child;
    else if (p_node->parent()->left() == p_node)
        p_node->parent()->left() = right_child;
    else
        p_node->parent()->right() = right_child;

    p_node->parent() = right_child;

    p_node->right() = right_child->left();
    if (sentinel() != right_child->left())
        right_child->left()->parent() = p_node;

    right_child->left() = p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::right_rotate(pointer p_node) noexcept
{
    // I assumes left child is not null.
    // p_node can be any node in the tree whose right child is not null.
    pointer left_child(p_node->left());
    left_child->parent() = p_node->parent();
    if (sentinel() == p_node->parent())
        m_root = left_child;
    else if (p_node->parent()->left() == p_node)
        p_node->parent()->left() = left_child;
    else
        p_node->parent()->right() = left_child;

    p_node->parent() = left_child;

    p_node->left() = left_child->right();
    if (sentinel() != left_child->right())
        left_child->right()->parent() = p_node;

    left_child->right() = p_node;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::insert(const_reference p_value)
{
    pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
    // Paint red by default, to fulfill property 4 of red black tree.
    std::allocator_traits<allocator_type>::construct(m_allocator, new_node, true, p_value, sentinel(), sentinel(), sentinel());

    pointer direction = m_root;
    pointer trailing = sentinel();
    while (direction != sentinel())
    {
        trailing = direction;
        if (p_value < direction->value())
            direction = direction->left();
        else
            direction = direction->right();
    }

    new_node->parent() = trailing;

    if (sentinel() == m_root)
        m_root = new_node;
    else if (p_value < trailing->value())
        trailing->left() = new_node;
    else
        trailing->right() = new_node;

    ++m_size;

    insert_fixup(new_node);
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::insert_fixup(pointer p_node)
{
    while (sentinel() != p_node->parent() && p_node->parent()->is_red())
    {
        // A root node always have black color.
        // That's why p_node->parent()->parent() always valid.
        if (p_node->parent() == p_node->parent()->parent()->left())
        {
            pointer uncle = p_node->parent()->parent()->right();
            // Case 1.
            if (uncle->is_red())
            {
                p_node->parent()->is_red() = false;
                uncle->is_red() = false;
                p_node->parent()->parent()->is_red() = true;
                p_node = p_node->parent()->parent();
            }
            // Case 2.
            else if (p_node == p_node->parent()->right())
            {
                p_node = p_node->parent();
                left_rotate(p_node);
            }
            // Case 3.
            else
            {
                p_node->parent()->is_red() = false;
                p_node->parent()->parent()->is_red() = true;
                right_rotate(p_node->parent()->parent());
            }
        }
        else
        {
            pointer uncle = p_node->parent()->parent()->left();
            // Case 4.
            if (uncle->is_red())
            {
                p_node->parent()->is_red() = false;
                uncle->is_red() = false;
                p_node->parent()->parent()->is_red() = true;
                p_node = p_node->parent()->parent();
            }
            // Case 5.
            else if (p_node == p_node->parent()->left())
            {
                p_node = p_node->parent();
                right_rotate(p_node);
            }
            // Case 6.
            else
            {
                p_node->parent()->is_red() = false;
                p_node->parent()->parent()->is_red() = true;
                left_rotate(p_node->parent()->parent());
            }
        }
    }

    m_root->is_red() = false;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::erase(pointer &p_node)
{
    // The moment p_node transplant with its child, p_node will become invalid.
    pointer substitute(p_node);
    pointer tracker(nullptr);
    // Keeps track violation of red black propteries. It's p_node or p_node's successor.
    bool original_color(substitute->is_red());

    if (sentinel() == p_node->left())
    {
        tracker = p_node->right();
        transplant(p_node, p_node->right());
    }
    else if (sentinel() == p_node->right())
    {
        tracker = p_node->left();
        transplant(p_node, p_node->left());
    }
    else
    {
        pointer succ = iterative_minimum(p_node->right());
        original_color = succ->is_red();
        tracker = succ->right(); // The sentinel node.

        // Whenever transplant gets called the parent of sentinel is changed.
        if (succ->parent() == p_node)
        {
            tracker->parent() = succ;
        }
        else
        {
            pointer temp(succ); // Avoid change value of "succ" itself.
            transplant(temp, succ->right());
            succ->right() = p_node->right();
            succ->right()->parent() = succ;
        }

        transplant(p_node, succ);
        succ->left() = substitute->left();
        succ->left()->parent() = succ;
        succ->is_red() = substitute->is_red();
    }

    std::allocator_traits<allocator_type>::destroy(m_allocator, substitute);
    std::allocator_traits<allocator_type>::deallocate(m_allocator, substitute, 1);
    --m_size;

    // Was the original color of "succ" painted black?
    if (!original_color)
        erase_fixup(tracker);
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::erase_fixup(pointer p_node)
{
    while (m_root != p_node && !p_node->is_red())
    {
        if (p_node == p_node->parent->left())
        {
            // Sibling of a black node can not be nullptr because it will violate property 5.
            pointer sibling(p_node->parent()->right());
            // Case 1.
            if (sibling->is_red())
            {
                sibling->is_red() = false;
                p_node->parent()->is_red() = true;
                left_rotate(p_node->parent());
                sibling = p_node->parent()->right();
            }
            // Case 2.
            if (!sibling->left()->is_red() && !sibling->right()->is_red())
            {
                sibling->is_red() = true;
                p_node = p_node->parent();
            }
            // Case 3.
            else if (!sibling->right()->is_red())
            {
                sibling->left()->is_red() = false;
                sibling->is_red() = true;
                right_rotate(sibling);
                sibling = p_node->parent()->right();
            }
            // Case 4.
            else
            {
                sibling->is_red() = p_node->parent()->is_red();
                p_node->parent()->is_red() = false;
                sibling->right()->is_red() = false;
                left_rotate(p_node->parent());
                p_node = m_root;
            }
        }
        else
        {
            // Sibling of a black node can not be nullptr because it will violate property 5.
            pointer sibling(p_node->parent()->left());
            // Case 5.
            if (sibling->is_red())
            {
                sibling->is_red() = false;
                p_node->parent()->is_red() = true;
                right_rotate(p_node->parent());
                sibling = p_node->parent()->left();
            }
            // Case 6.
            if (!sibling->left()->is_red() && !sibling->right()->is_red())
            {
                sibling->is_red() = true;
                p_node = p_node->parent();
            }
            // Case 7.
            else if (!sibling->left()->is_red())
            {
                sibling->right()->is_red() = false;
                sibling->is_red() = true;
                left_rotate(sibling);
                sibling = p_node->parent()->left();
            }
            // Case 8.
            {
                sibling->is_red() = p_node->parent()->is_red();
                p_node->parent()->is_red() = false;
                sibling->left()->is_red() = false;
                right_rotate(p_node->parent());
                p_node = m_root;
            }
        }
    }
    p_node->is_red() = false;
}

// Auxiliary method for earsing node. This method does not handle child transplant.
template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::RedBlackTree<Elem, Alloc>::transplant(pointer &p_node, pointer &p_child) noexcept
{
    if (sentinel() == p_node->parent())
        m_root = p_child;
    else if (p_node == p_node->parent()->left())
        p_node->parent()->left() = p_child;
    else
        p_node->parent()->right() = p_child;

    p_child->parent() = p_node->parent();
}

#endif //!DSAA_RED_BLACK_TREE_H