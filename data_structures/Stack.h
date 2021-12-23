/*class: Stack.
Purpose: - Serve as FILO container.
*/

#ifndef DSAA_STACK_H
#define DSAA_STACK_H

#include <memory>			// std::allocator
#include <initializer_list> // std::initializer_list
#include <algorithm>		// std::copy
#include <stdexcept>		// std::out_of_range.
#include <iterator>			// std::iterator_traits
#include <cassert>
#include <limits>

#include "dsaaTypedefs.h"

namespace dsaa
{
	template <typename T>
	class StackNode;

	template <typename Elem, typename Alloc = std::allocator<StackNode<Elem>>>
	class Stack
	{
	public:
		class ConstIterator;
		class Iterator;

		using value_type = Elem;
		using allocator_type = Alloc;
		using reference = value_type &;
		using const_reference = value_type const &;
		using pointer = StackNode<value_type> *;
		using const_pointer = StackNode<value_type> const *;
		using const_iterator = ConstIterator;
		using iterator = Iterator;
		using difference_type = std::ptrdiff_t;
		using size_type = size_t;

		// Returns an iterator pointing to the first element in the container.
		NODISCARD CONSTEXPR INLINE iterator begin() noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator begin() const noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator cbegin() const noexcept;
		// Returns an iterator referring to the past-the-end element in the container.
		NODISCARD CONSTEXPR INLINE iterator end() noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator end() const noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator cend() const noexcept;

		// Creates a container with no element.
		CONSTEXPR Stack(const allocator_type &p_allocator = allocator_type()) noexcept;
		// Creates a container's size eual to p_elements's size and init its elements by p_elements's element.
		CONSTEXPR Stack(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type());
		// Creates a container and init its elements by content of IIterator in range (first, last].
		template <typename IIterator>
		CONSTEXPR Stack(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator = allocator_type());
		CONSTEXPR Stack(Stack &p_other) noexcept = delete;
		CONSTEXPR Stack(Stack &p_other, const allocator_type &p_allocator) noexcept = delete;

		// Moves all elements from p_other into this.
		CONSTEXPR Stack(Stack &&p_other) noexcept;
		// Moves all elements from p_other into this.
		CONSTEXPR Stack(Stack &&p_other, const allocator_type &p_allocator) noexcept;
		CONSTEXPR Stack &operator=(Stack &p_other) = delete;
		// Destroys old elements and moves all emements from p_other into this.
		CONSTEXPR Stack &operator=(Stack &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value);
		// Destroys old elements and copy all elements from p_elements.
		CONSTEXPR Stack &operator=(const std::initializer_list<value_type> &p_elements);
		// Destroys all elements and clean used space.
		virtual ~Stack();

		// Assigns new contents to the Stack container, replacing its current contents, and modifying its size accordingly.
		template <typename IIterator>
		CONSTEXPR void assign(const IIterator &p_first, const IIterator &p_last);
		CONSTEXPR void assign(const std::initializer_list<value_type> &p_elements);

		// Returns a reference to the element to extract.
		NODISCARD CONSTEXPR INLINE StackNode<value_type> &peek();
		NODISCARD CONSTEXPR INLINE StackNode<value_type> const &peek() const;
		// Returns a copy of the allocator object associated with the Stack container.
		NODISCARD CONSTEXPR INLINE allocator_type get_allocator() const noexcept;
		// Test whether container is empty.
		NODISCARD CONSTEXPR INLINE bool empty() const noexcept;
		// Returns the number of elements in the Stack container.
		NODISCARD CONSTEXPR INLINE size_type size() const noexcept;
		// Returns the maximum number of elements that the Stack container can hold.
		NODISCARD CONSTEXPR INLINE size_type max_size() const noexcept;
		NODISCARD CONSTEXPR INLINE size_type get_index(const_iterator p_iterator);
		NODISCARD CONSTEXPR INLINE iterator get_iterator(size_type p_index);

		// Insert new element(s).
		CONSTEXPR iterator insert(const_reference p_value);
		CONSTEXPR iterator insert(value_type &&p_value);
		CONSTEXPR iterator insert(const std::initializer_list<value_type> &p_elements);
		template <class IIterator>
		CONSTEXPR iterator insert(const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		CONSTEXPR iterator emplace(Args &&...p_args);

		// Deletes the first element.
		CONSTEXPR INLINE value_type extract();
		// Cleans all elements and deallocate allocated space.
		CONSTEXPR INLINE void clean() noexcept;

	protected:
		allocator_type m_allocator;
		size_type m_size;
		pointer m_first;
	};
}

template <typename T>
class dsaa::StackNode
{
public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const value_type &;
	using size_type = size_t;

	CONSTEXPR StackNode(const_reference p_value = value_type()) noexcept : m_value(p_value), m_next(nullptr) {}
	CONSTEXPR StackNode(value_type &&p_value) noexcept : m_value(std::move(p_value)), m_next(nullptr) {}
	CONSTEXPR StackNode(const_reference p_value, StackNode *p_next) noexcept : m_value(p_value), m_next(p_next) {}
	CONSTEXPR StackNode(value_type &&p_value, StackNode *p_next) noexcept : m_value(std::move(p_value)), m_next(p_next) {}

	CONSTEXPR StackNode(const StackNode &p_other) noexcept : m_value(p_other.m_value), m_next(p_other.m_next) {}
	CONSTEXPR StackNode(StackNode &&p_other) noexcept : m_value(std::move(p_other.m_value)), m_next(p_other.m_next)
	{
		p_other.m_value = value_type();
		p_other.m_next = nullptr;
	}

	virtual ~StackNode() {}

	CONSTEXPR StackNode &operator=(const StackNode &p_other)
	{
		m_value = p_other.m_value;
		m_next = p_other.m_next;
		return *this;
	}

	CONSTEXPR StackNode &operator=(StackNode &&p_other)
	{
		m_value = std::move(p_other.m_value);
		m_next = p_other.m_next;

		p_other.m_value = value_type();
		p_other.m_next = nullptr;
		return *this;
	}

	CONSTEXPR INLINE StackNode &operator++()
	{
		*this = *m_next;
		return *this;
	}

	CONSTEXPR INLINE StackNode operator++(int)
	{
		StackNode old(*this); // copy old value
		operator++();		  // prefix increment
		return old;			  // return old value
	}

	// Dereference that allows us to write/read into m_value.
	CONSTEXPR INLINE reference operator*() { return m_value; }
	CONSTEXPR INLINE const_reference operator*() const { return m_value; }

	CONSTEXPR INLINE StackNode *&next() { return m_next; }
	CONSTEXPR INLINE StackNode *const &next() const { return m_next; }

	CONSTEXPR INLINE reference value() { return m_value; }
	CONSTEXPR INLINE const_reference value() const { return m_value; }

	CONSTEXPR INLINE bool operator==(const StackNode &p_other) const
	{
		return m_value == p_other.m_value && m_next == p_other.m_next;
	}
	CONSTEXPR INLINE bool operator!=(const StackNode &p_other) const { return !(*this == p_other); }

protected:
	value_type m_value;
	StackNode *m_next; // succesor (next) content.
};

template <typename Elem, typename Alloc>
class dsaa::Stack<Elem, Alloc>::ConstIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = Stack::value_type;
	using reference = Stack::reference;
	using const_reference = Stack::const_reference;
	using pointer = Stack::pointer;
	using const_pointer = Stack::const_pointer;
	using difference_type = Stack::difference_type;

	CONSTEXPR ConstIterator() noexcept : m_link(nullptr) {}
	CONSTEXPR ConstIterator(const_pointer p_link) noexcept : m_link(const_cast<pointer>(p_link)) {}
	CONSTEXPR ConstIterator(const ConstIterator &p_iterator) noexcept : m_link(p_iterator.m_link) {}

	CONSTEXPR ConstIterator &operator=(const ConstIterator &p_iterator)
	{
		m_link = p_iterator.m_link;
		return *this;
	}

	virtual ~ConstIterator() {}

	CONSTEXPR INLINE ConstIterator &operator++()
	{
#ifdef PARAM_CHECK
		if (nullptr == m_link)
			throw std::runtime_error("m_link is nullptr, Do not try to dereference a nullptr.");
#endif

		m_link = m_link->next();
		return *this;
	}
	CONSTEXPR INLINE ConstIterator operator++(int)
	{
		ConstIterator old(*this);
		operator++();
		return old;
	}

	CONSTEXPR INLINE const_reference operator*() const { return m_link->value(); }
	CONSTEXPR INLINE const_pointer content() const { return m_link; }

	CONSTEXPR INLINE bool operator==(const ConstIterator &p_iterator) const { return m_link == p_iterator.m_link; }
	CONSTEXPR INLINE bool operator!=(const ConstIterator &p_iterator) const { return m_link != p_iterator.m_link; }

protected:
	pointer m_link;
};

template <typename Elem, typename Alloc>
class dsaa::Stack<Elem, Alloc>::Iterator : public dsaa::Stack<Elem, Alloc>::ConstIterator
{
public:
	CONSTEXPR Iterator() noexcept : ConstIterator() {}
	CONSTEXPR Iterator(pointer p_link) noexcept : ConstIterator(p_link) {}
	CONSTEXPR Iterator(const Iterator &p_iterator) noexcept : ConstIterator(p_iterator) {}
	CONSTEXPR Iterator(const ConstIterator &p_iterator) noexcept : ConstIterator(p_iterator) {}

	CONSTEXPR Iterator &operator=(const Iterator &p_iterator)
	{
		ConstIterator::m_link = p_iterator.ConstIterator::m_link;
		return *this;
	}

	virtual ~Iterator() {}

	CONSTEXPR INLINE Iterator &operator++()
	{
#ifdef PARAM_CHECK
		if (nullptr == content())
			throw std::runtime_error("content() is nullptr, Do not try to dereference a nullptr.");
#endif

		content() = content()->next();
		return *this;
	}

	CONSTEXPR INLINE Iterator operator++(int)
	{
		Iterator old(*this);
		operator++();
		return old;
	}

	CONSTEXPR INLINE bool operator==(const Iterator &p_other) const noexcept { return ConstIterator::m_link == p_other.ConstIterator::m_link; }
	CONSTEXPR INLINE bool operator!=(const Iterator &p_other) const noexcept { return ConstIterator::m_link != p_other.ConstIterator::m_link; }

	CONSTEXPR INLINE reference operator*() { return ConstIterator::m_link->value(); }
	CONSTEXPR INLINE const_reference operator*() const { return ConstIterator::m_link->value(); }
	CONSTEXPR INLINE pointer &content() { return ConstIterator::m_link; }
	CONSTEXPR INLINE pointer const &content() const { return ConstIterator::m_link; }
};

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::begin() noexcept
{
	return iterator(m_first);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::const_iterator dsaa::Stack<Elem, Alloc>::begin() const noexcept
{
	return const_iterator(m_first);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::const_iterator dsaa::Stack<Elem, Alloc>::cbegin() const noexcept
{
	return const_iterator(m_first);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::end() noexcept
{
	return size() ? iterator(nullptr) : iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::const_iterator dsaa::Stack<Elem, Alloc>::end() const noexcept
{
	return size() ? const_iterator(nullptr) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::const_iterator dsaa::Stack<Elem, Alloc>::cend() const noexcept
{
	return size() ? const_iterator(nullptr) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::Stack<Elem, Alloc>::Stack(const allocator_type &p_allocator) noexcept
	: m_allocator(p_allocator), m_size(0), m_first(nullptr) {}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::Stack<Elem, Alloc>::Stack(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr)
{
	for (auto i(p_elements.begin()); i != p_elements.end(); ++i)
		insert(*i);
}

template <typename Elem, typename Alloc>
template <typename IIterator>
CONSTEXPR dsaa::Stack<Elem, Alloc>::Stack(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr)
{
	for (auto i(p_first); p_last != i; ++i)
		insert(*i);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::Stack<Elem, Alloc>::Stack(Stack &&p_other) noexcept
	: m_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator)),
	  m_size(p_other.size()), m_first(p_other.m_first)
{
	p_other.m_allocator = allocator_type();
	p_other.m_size = 0;
	p_other.m_first = nullptr;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::Stack<Elem, Alloc>::Stack(Stack &&p_other, const allocator_type &p_allocator) noexcept
	: m_allocator(p_allocator), m_size(p_other.size()), m_first(p_other.m_first)
{
	p_other.m_allocator = allocator_type();
	p_other.m_size = 0;
	p_other.m_first = nullptr;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::Stack<Elem, Alloc> &dsaa::Stack<Elem, Alloc>::operator=(Stack &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value)
{
	clean();

	m_allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator);
	m_size = p_other.size();
	m_first = p_other.m_first;

	p_other.m_allocator = allocator_type();
	p_other.m_size = 0;
	p_other.m_first = nullptr;

	return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::Stack<Elem, Alloc> &dsaa::Stack<Elem, Alloc>::operator=(const std::initializer_list<value_type> &p_elements)
{
	clean();
	for (auto i(p_elements.begin()); p_elements.end() != i; ++i)
		insert(*i);
	return *this;
}

template <typename Elem, typename Alloc>
dsaa::Stack<Elem, Alloc>::~Stack()
{
	if (0 == size())
		return;

	for (iterator iter(m_first->next()); end() != iter; ++iter)
	{
		std::allocator_traits<allocator_type>::destroy(m_allocator, m_first);
		std::allocator_traits<allocator_type>::deallocate(m_allocator, m_first, 1);
		m_first = iter.content();
	}
	std::allocator_traits<allocator_type>::destroy(m_allocator, m_first);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_first, 1);

	m_first = nullptr;
	m_size = 0;
}

template <typename Elem, typename Alloc>
template <typename IIterator>
CONSTEXPR void dsaa::Stack<Elem, Alloc>::assign(const IIterator &p_first, const IIterator &p_last)
{
	clean();
	insert(p_first, p_last);
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::Stack<Elem, Alloc>::assign(const std::initializer_list<value_type> &p_elements)
{
	clean();
	insert(p_elements);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::StackNode<Elem> &dsaa::Stack<Elem, Alloc>::peek()
{
#ifdef PARAM_CHECK
	if (nullptr == m_first)
		throw std::runtime_error("m_first is nullptr.\n");
#endif

	return *m_first;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::StackNode<Elem> const &dsaa::Stack<Elem, Alloc>::peek() const
{
#ifdef PARAM_CHECK
	if (nullptr == m_first)
		throw std::runtime_error("m_first is nullptr.\n");
#endif

	return *m_first;
}

// Returns a copy of the allocator object associated with the Stack container.
template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::allocator_type dsaa::Stack<Elem, Alloc>::get_allocator() const noexcept
{
	return m_allocator;
}

template <typename Elem, typename Alloc>
CONSTEXPR bool dsaa::Stack<Elem, Alloc>::empty() const noexcept
{
	return !size();
}

// Returns the number of elements in the Stack container.
template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::size_type dsaa::Stack<Elem, Alloc>::size() const noexcept
{
	return m_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::size_type dsaa::Stack<Elem, Alloc>::max_size() const noexcept
{
	return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::size_type dsaa::Stack<Elem, Alloc>::get_index(const_iterator p_iterator)
{
	size_type index(0);
	for (auto i(cbegin()); cend() != i; ++i, ++index)
		if (i == p_iterator)
			break;
	return index;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::get_iterator(size_type p_index)
{
	iterator iter(begin());
	for (size_type i(0); size() != i; ++i, ++iter)
		if (i == p_index)
			break;
	return iter;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::insert(const_reference p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_value);
	if (m_first)
	{
		new_node->next() = m_first;
	}

	m_first = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::insert(value_type &&p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, std::move(p_value));
	if (m_first)
	{
		new_node->next() = m_first;
	}

	m_first = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::insert(const std::initializer_list<value_type> &p_elements)
{
	for (auto i(p_elements.begin()); p_elements.end() != i; ++i)
	{
		pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
		std::allocator_traits<allocator_type>::construct(m_allocator, new_node, *i);
		if (m_first)
		{
			new_node->next() = m_first;
		}

		m_first = new_node;

		++m_size;
	}

	return begin();
}

template <typename Elem, typename Alloc>
template <class IIterator>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::insert(const IIterator &p_first, const IIterator &p_last)
{
	for (auto i(p_first); p_last != i; ++i)
	{
		pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
		std::allocator_traits<allocator_type>::construct(m_allocator, new_node, *i);
		if (m_first)
		{
			new_node->next() = m_first;
		}

		m_first = new_node;

		++m_size;
	}

	return begin();
}

template <typename Elem, typename Alloc>
template <class... Args>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::iterator dsaa::Stack<Elem, Alloc>::emplace(Args &&...p_args)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_args...);
	if (m_first)
	{
		new_node->next() = m_first;
	}

	m_first = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::Stack<Elem, Alloc>::value_type dsaa::Stack<Elem, Alloc>::extract()
{
#ifdef PARAM_CHECK
	if (0 == size())
		throw std::runtime_error("size is zero, there is nothing to extract.\n");
#endif

	iterator iter(m_first->next());
	value_type result(std::move(**m_first));
	std::allocator_traits<allocator_type>::destroy(m_allocator, m_first);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_first, 1);
	--m_size;
	if (nullptr == iter.content())
	{
		assert(0 == size());
		m_first = nullptr;
	}
	else
	{
		m_first = iter.content();
	}
	return result;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::Stack<Elem, Alloc>::clean() noexcept
{
	if (0 == size())
		return;

	for (iterator iter(m_first->next()); end() != iter; ++iter)
	{
		std::allocator_traits<allocator_type>::destroy(m_allocator, m_first);
		std::allocator_traits<allocator_type>::deallocate(m_allocator, m_first, 1);
		m_first = iter.content();
	}
	std::allocator_traits<allocator_type>::destroy(m_allocator, m_first);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_first, 1);

	m_first = nullptr;
	m_size = 0;
}
#endif // !DSAA_STACK_H
