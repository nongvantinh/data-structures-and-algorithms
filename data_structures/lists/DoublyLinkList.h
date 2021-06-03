#ifndef DSAA_DOUBLY_LINK_LIST_H
#define DSAA_DOUBLY_LINK_LIST_H

#include <memory>			// std::allocator
#include <initializer_list> // std::initializer_list
#include <algorithm>		// std::copy
#include <stdexcept>		// std::out_of_range.
#include <iterator>			// std::iterator_traits
#include <cassert>

namespace dsaa
{
	template <typename T>
	class DoublyLinkListNode;

	template <typename Elem, typename Alloc = std::allocator<DoublyLinkListNode<Elem>>>
	class DoublyLinkList
	{
	public:
		class ConstIterator;
		class Iterator;

		using value_type = Elem;
		using allocator_type = Alloc;
		using reference = value_type &;
		using const_reference = value_type const &;
		using pointer = DoublyLinkListNode<value_type> *;
		using const_pointer = DoublyLinkListNode<value_type> const *;
		using const_iterator = ConstIterator;
		using iterator = Iterator;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using difference_type = std::ptrdiff_t;
		using size_type = size_t;

		// Returns an iterator pointing to the first element in the container.
		[[nodiscard]] constexpr inline iterator begin() noexcept;
		[[nodiscard]] constexpr inline const_iterator begin() const noexcept;
		[[nodiscard]] constexpr inline const_iterator cbegin() const noexcept;
		// Returns an iterator referring to the past-the-end element in the container.
		[[nodiscard]] constexpr inline iterator end() noexcept;
		[[nodiscard]] constexpr inline const_iterator end() const noexcept;
		[[nodiscard]] constexpr inline const_iterator cend() const noexcept;
		// Returns a reverse_iterator pointing to the last element in the container.
		// [[nodiscard]] constexpr inline reverse_iterator rbegin() noexcept;
		// [[nodiscard]] constexpr inline const_reverse_iterator rbegin() const noexcept;
		// [[nodiscard]] constexpr inline const_reverse_iterator crbegin() const noexcept;
		// // Returns a reverse iterator pointing to the theoretical element preceding the first element in the container.
		// [[nodiscard]] constexpr inline reverse_iterator rend() noexcept;
		// [[nodiscard]] constexpr inline const_reverse_iterator rend() const noexcept;
		// [[nodiscard]] constexpr inline const_reverse_iterator crend() const noexcept;

		// Creates a container with no element.
		constexpr DoublyLinkList(const allocator_type &p_allocator = allocator_type()) noexcept;
		// Creates a container's p_size elements with default value.
		constexpr explicit DoublyLinkList(const size_type &p_size, const allocator_type &p_allocator = allocator_type());
		// Creates a container's p_size elements and init its element by p_value.
		constexpr DoublyLinkList(const size_type &p_size, const_reference p_value, const allocator_type &p_allocator = allocator_type());
		// Creates a container's size eual to p_elements's size and init its elements by p_elements's element.
		constexpr DoublyLinkList(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type());
		// Creates a container and init its elements by content of IIterator in range (first, last].
		template <typename IIterator>
		constexpr DoublyLinkList(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator = allocator_type());
		// Creates a container and copy all emements from p_other.
		constexpr DoublyLinkList(const DoublyLinkList &p_other);
		// Creates a container and copy all emements from p_other.
		constexpr DoublyLinkList(const DoublyLinkList &p_other, const allocator_type &p_allocator);
		// Moves all elements from p_other into this.
		constexpr DoublyLinkList(DoublyLinkList &&p_other) noexcept;
		// Moves all elements from p_other into this.
		constexpr DoublyLinkList(DoublyLinkList &&p_other, const allocator_type &p_allocator) noexcept;
		// Destroys old elements and copy all emements from p_other into this.
		constexpr DoublyLinkList &operator=(const DoublyLinkList &p_other);
		// Destroys old elements and moves all emements from p_other into this.
		constexpr DoublyLinkList &operator=(DoublyLinkList &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value);
		// Destroys old elements and copy all elements from p_elements.
		constexpr DoublyLinkList &operator=(const std::initializer_list<value_type> &p_elements);
		// Destroys all elements and clean used space.
		virtual ~DoublyLinkList();

		// Assigns new contents to the DoublyLinkList container, replacing its current contents, and modifying its size accordingly.
		template <typename IIterator>
		constexpr void assign(const IIterator &p_first, const IIterator &p_last);
		constexpr void assign(const size_type &p_size, const_reference p_value = value_type());
		constexpr void assign(const std::initializer_list<value_type> &p_elements);

		// Returns a reference to the first element in the DoublyLinkList container.
		[[nodiscard]] constexpr inline DoublyLinkListNode<value_type> &first();
		[[nodiscard]] constexpr inline DoublyLinkListNode<value_type> const &first() const;
		// Returns a reference to the last element in the DoublyLinkList container.
		[[nodiscard]] constexpr inline DoublyLinkListNode<value_type> &last();
		[[nodiscard]] constexpr inline DoublyLinkListNode<value_type> const &last() const;
		// Returns a copy of the allocator object associated with the DoublyLinkList container.
		[[nodiscard]] constexpr inline allocator_type get_allocator() const noexcept;
		// Test whether container is empty.
		[[nodiscard]] constexpr inline bool empty() const noexcept;
		// Returns the number of elements in the DoublyLinkList container.
		[[nodiscard]] constexpr inline size_type size() const noexcept;
		// Returns the maximum number of elements that the DoublyLinkList container can hold.
		[[nodiscard]] constexpr inline size_type max_size() const noexcept;
		[[nodiscard]] constexpr inline size_type get_index(const_iterator p_iterator);
		[[nodiscard]] constexpr inline iterator get_iterator(size_type p_index);
		// Resizes the container so that it contains n elements.
		constexpr void resize(const size_type &p_size, const_reference p_value = value_type());

		// Insert new element(s) at the begining.
		constexpr iterator insert_first(const_reference p_value);
		constexpr iterator insert_first(value_type &&p_value);
		constexpr iterator insert_first(const size_type &p_size, const_reference p_value);
		constexpr iterator insert_first(const std::initializer_list<value_type> &p_elements);
		template <class IIterator>
		constexpr iterator insert_first(const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		constexpr iterator emplace_first(Args &&...p_args);

		// Insert new element(s) at the ends.
		constexpr iterator insert_last(const_reference p_value);
		constexpr iterator insert_last(value_type &&p_value);
		constexpr iterator insert_last(const size_type &p_size, const_reference p_value);
		constexpr iterator insert_last(const std::initializer_list<value_type> &p_elements);
		template <class IIterator>
		constexpr iterator insert_last(const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		constexpr iterator emplace_last(Args &&...p_args);

		// Insert new element(s) before the specified position.
		constexpr iterator insert_before(const const_iterator &p_position, const_reference p_value);
		constexpr iterator insert_before(const const_iterator &p_position, value_type &&p_value);
		constexpr iterator insert_before(const const_iterator &p_position, const size_type &p_size, const_reference p_value);
		constexpr iterator insert_before(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements);
		template <class IIterator>
		constexpr iterator insert_before(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		constexpr iterator emplace_before(const const_iterator &p_position, Args &&...p_args);

		// Insert new element(s) after the specified position.
		constexpr iterator insert_after(const const_iterator &p_position, const_reference p_value);
		constexpr iterator insert_after(const const_iterator &p_position, value_type &&p_value);
		constexpr iterator insert_after(const const_iterator &p_position, const size_type &p_size, const_reference p_value);
		constexpr iterator insert_after(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements);
		template <typename IIterator>
		constexpr iterator insert_after(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		constexpr iterator emplace_after(const const_iterator &p_position, Args &&...p_args);

		// Deletes the first element.
		constexpr inline void erase_first();
		// Deletes the last element.
		constexpr inline void erase_last();
		// Deletes the element at specified position.
		constexpr inline void erase(const const_iterator &p_position);
		// Deletes elements in range [first, last)
		constexpr void erase(const const_iterator &p_first, const const_iterator &p_last);
		// Cleans all elements and deallocate allocated space.
		constexpr inline void clean() noexcept;

		// Exchanges the content of the container by the content of p_other,
		// which is another DoublyLinkList of the same type. Sizes may differ.
		void swap(DoublyLinkList &p_other);

	protected:
		allocator_type m_allocator;
		size_type m_size;
		pointer m_first;
		pointer m_last;
	};
}

template <typename T>
class dsaa::DoublyLinkListNode
{
public:
	using value_type = T;
	using reference = value_type &;
	using const_reference = const value_type &;
	using size_type = size_t;

	constexpr DoublyLinkListNode(const_reference p_value = value_type()) noexcept : m_value(p_value), m_prev(nullptr), m_next(nullptr) {}
	constexpr DoublyLinkListNode(value_type &&p_value) noexcept : m_value(std::move(p_value)), m_prev(nullptr), m_next(nullptr) {}
	constexpr DoublyLinkListNode(const_reference p_value, DoublyLinkListNode *p_prev, DoublyLinkListNode *p_next) noexcept : m_value(p_value), m_prev(p_prev), m_next(p_next) {}
	constexpr DoublyLinkListNode(value_type &&p_value, DoublyLinkListNode *p_prev, DoublyLinkListNode *p_next) noexcept : m_value(std::move(p_value)), m_prev(p_prev), m_next(p_next) { p_value = value_type(); }

	constexpr DoublyLinkListNode(const DoublyLinkListNode &p_other) noexcept : m_value(p_other.m_value), m_prev(p_other.m_prev), m_next(p_other.m_next) {}
	constexpr DoublyLinkListNode(DoublyLinkListNode &&p_other) noexcept : m_value(std::move(p_other.m_value)), m_prev(p_other.m_prev), m_next(p_other.m_next)
	{
		p_other.m_value = value_type();
		p_other.m_prev = nullptr;
		p_other.m_next = nullptr;
	}

	virtual ~DoublyLinkListNode() {}

	constexpr DoublyLinkListNode &operator=(const DoublyLinkListNode &p_other)
	{
		m_value = p_other.m_value;
		m_prev = p_other.m_prev;
		m_next = p_other.m_next;
	}

	constexpr DoublyLinkListNode &operator=(DoublyLinkListNode &&p_other)
	{
		m_value = p_other.m_value;
		m_prev = p_other.m_prev;
		m_next = p_other.m_next;

		p_other.m_value = value_type();
		p_other.m_prev = nullptr;
		p_other.m_next = nullptr;
	}

	constexpr inline DoublyLinkListNode &operator++()
	{
		*this = *m_next;
		return *this;
	}

	constexpr inline DoublyLinkListNode operator++(int)
	{
		DoublyLinkListNode old(*this); // copy old value
		operator++();				   // prefix increment
		return old;					   // return old value
	}

	constexpr inline DoublyLinkListNode &operator--()
	{
		*this = *m_prev;
		return *this;
	}

	constexpr inline DoublyLinkListNode operator--(int)
	{
		DoublyLinkListNode old(*this); // copy old value
		operator--();				   // prefix increment
		return old;					   // return old value
	}

	// Dereference that allows us to write/read into m_value.
	constexpr inline reference operator*() { return m_value; }
	constexpr inline const_reference operator*() const { return m_value; }

	constexpr inline DoublyLinkListNode *&previous() { return m_prev; }
	constexpr inline DoublyLinkListNode *const &previous() const { return m_prev; }

	constexpr inline DoublyLinkListNode *&next() { return m_next; }
	constexpr inline DoublyLinkListNode *const &next() const { return m_next; }

	constexpr inline reference value() { return m_value; }
	constexpr inline const_reference value() const { return m_value; }

	constexpr inline bool operator==(const DoublyLinkListNode &p_other) const
	{
		return m_prev == p_other.m_prev && m_next == p_other.m_next && m_value == p_other.m_value;
	}
	constexpr inline bool operator!=(const DoublyLinkListNode &p_other) const { return !(*this == p_other); }

protected:
	value_type m_value;
	DoublyLinkListNode *m_prev; // previous content.
	DoublyLinkListNode *m_next; // succesor (next) content.
};

template <typename Elem, typename Alloc>
class dsaa::DoublyLinkList<Elem, Alloc>::ConstIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = DoublyLinkList::value_type;
	using reference = DoublyLinkList::reference;
	using const_reference = DoublyLinkList::const_reference;
	using pointer = DoublyLinkList::pointer;
	using difference_type = DoublyLinkList::difference_type;

	constexpr ConstIterator() noexcept : m_link{nullptr} {}
	constexpr ConstIterator(pointer p_link) noexcept : m_link{p_link} {}
	constexpr ConstIterator(const ConstIterator &p_iterator) noexcept : m_link{p_iterator.content()} {}

	constexpr ConstIterator &operator=(const ConstIterator &p_iterator)
	{
		m_link = p_iterator.content();
		return *this;
	}

	virtual ~ConstIterator() {}

	constexpr inline ConstIterator &operator++()
	{
		m_link = m_link->next();
		return *this;
	}
	constexpr inline ConstIterator operator++(int)
	{
		ConstIterator old(*this);
		operator++();
		return old;
	}

	constexpr inline ConstIterator &operator--()
	{
		m_link = m_link->previous();
		return *this;
	}

	constexpr inline ConstIterator operator--(int)
	{
		ConstIterator old(*this);
		operator--();
		return old;
	}

	constexpr inline reference operator*() const { return m_link->value(); }
	constexpr inline pointer content() const { return m_link; }

	constexpr inline bool operator==(const ConstIterator &p_iterator) const { return m_link == p_iterator.m_link; }
	constexpr inline bool operator!=(const ConstIterator &p_iterator) const { return m_link != p_iterator.m_link; }

protected:
	pointer m_link;
};

template <typename Elem, typename Alloc>
class dsaa::DoublyLinkList<Elem, Alloc>::Iterator : public dsaa::DoublyLinkList<Elem, Alloc>::ConstIterator
{
public:
	constexpr Iterator() noexcept : ConstIterator() {}
	constexpr Iterator(pointer p_link) noexcept : ConstIterator(p_link) {}
	constexpr Iterator(const Iterator &p_iterator) noexcept : ConstIterator(p_iterator) {}
	constexpr Iterator(const ConstIterator &p_iterator) noexcept : ConstIterator(p_iterator) {}

	constexpr Iterator &operator=(const Iterator &p_iterator)
	{
		content() = p_iterator.content();
		return *this;
	}

	~Iterator() {}

	constexpr inline Iterator &operator++()
	{
		content() = content()->next();
		return *this;
	}

	constexpr inline Iterator operator++(int)
	{
		Iterator old(*this);
		operator++();
		return old;
	}

	constexpr inline Iterator &operator--()
	{
		content() = content()->previous();
		return *this;
	}

	constexpr inline Iterator operator--(int)
	{
		Iterator old(*this);
		operator--();
		return old;
	}

	constexpr inline bool operator==(const Iterator &other) const noexcept { return content() == other.content(); }
	constexpr inline bool operator!=(const Iterator &other) const noexcept { return content() != other.content(); }

	constexpr inline reference operator*() { return ConstIterator::m_link->value(); }
	constexpr inline pointer &content() { return ConstIterator::m_link; }
	constexpr inline pointer content() const { return ConstIterator::m_link; }
};

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::begin() noexcept
{
	return iterator(m_first);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_iterator dsaa::DoublyLinkList<Elem, Alloc>::begin() const noexcept
{
	return const_iterator(m_first);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_iterator dsaa::DoublyLinkList<Elem, Alloc>::cbegin() const noexcept
{
	return const_iterator(m_first);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::end() noexcept
{
	return size() ? iterator(m_last->next()) : iterator(nullptr);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_iterator dsaa::DoublyLinkList<Elem, Alloc>::end() const noexcept
{
	return size() ? const_iterator(m_last->next()) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_iterator dsaa::DoublyLinkList<Elem, Alloc>::cend() const noexcept
{
	return size() ? const_iterator(m_last->next()) : const_iterator(nullptr);
}

// template <typename Elem, typename Alloc>
// constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::reverse_iterator dsaa::DoublyLinkList<Elem, Alloc>::rbegin() noexcept
// {
// 	return reverse_iterator(end());
// }

// template <typename Elem, typename Alloc>
// constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_reverse_iterator dsaa::DoublyLinkList<Elem, Alloc>::rbegin() const noexcept
// {
// 	return const_reverse_iterator(end());
// }

// template <typename Elem, typename Alloc>
// constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_reverse_iterator dsaa::DoublyLinkList<Elem, Alloc>::crbegin() const noexcept
// {
// 	return rbegin();
// }

// template <typename Elem, typename Alloc>
// constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::reverse_iterator dsaa::DoublyLinkList<Elem, Alloc>::rend() noexcept
// {
// 	return reverse_iterator(begin());
// }

// template <typename Elem, typename Alloc>
// constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_reverse_iterator dsaa::DoublyLinkList<Elem, Alloc>::rend() const noexcept
// {
// 	return const_reverse_iterator(begin());
// }

// template <typename Elem, typename Alloc>
// constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::const_reverse_iterator dsaa::DoublyLinkList<Elem, Alloc>::crend() const noexcept
// {
// 	return rend();
// }

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const allocator_type &p_allocator) noexcept
	: m_allocator(p_allocator), m_size(0), m_first(nullptr), m_last(nullptr) {}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const size_type &p_size, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr), m_last(nullptr)
{
	for (size_type i(0); i < p_size; ++i)
		insert_last(value_type());
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const size_type &p_size, const_reference p_value, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr), m_last(nullptr)
{
	for (size_type i(0); i < p_size; ++i)
		insert_last(p_value);
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr), m_last(nullptr)
{
	for (auto i(p_elements.begin()); i != p_elements.end(); ++i)
		insert_last(*i);
}

template <typename Elem, typename Alloc>
template <typename IIterator>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr), m_last(nullptr)
{
	for (auto i(p_first); p_last != i; ++i)
		insert_last(*i);
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const DoublyLinkList &p_other)
	: m_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator)),
	  m_size(0), m_first(nullptr), m_last(nullptr)
{
	for (auto i(p_other.begin()); i != p_other.end(); ++i)
		insert_last(*i);
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(const DoublyLinkList &p_other, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_size(0), m_first(nullptr), m_last(nullptr)
{
	for (auto i(p_other.begin()); i != p_other.end(); ++i)
		insert_last(*i);
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(DoublyLinkList &&p_other) noexcept
	: m_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator)),
	  m_size(p_other.size()), m_first(p_other.m_first), m_last(p_other.m_last)
{
	p_other.m_allocator = allocator_type();
	p_other.m_size = 0;
	p_other.m_first = nullptr;
	p_other.m_last = nullptr;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc>::DoublyLinkList(DoublyLinkList &&p_other, const allocator_type &p_allocator) noexcept
	: m_allocator{p_allocator}, m_size(p_other.size()), m_first(p_other.m_first), m_last(p_other.m_last)
{
	p_other.m_allocator = allocator_type();
	p_other.m_size = 0;
	p_other.m_first = nullptr;
	p_other.m_last = nullptr;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc> &dsaa::DoublyLinkList<Elem, Alloc>::operator=(const DoublyLinkList &p_other)
{
	// Avoid self-reference.
	if (this == &p_other)
		return *this;

	clean();

	for (auto i(p_other.begin()); i != p_other.end(); ++i)
		insert_last(*i);

	return *this;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc> &dsaa::DoublyLinkList<Elem, Alloc>::operator=(DoublyLinkList &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value)
{
	clean();

	m_allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator);
	m_size = p_other.size();
	m_first = p_other.m_first;
	m_last = p_other.m_last;

	p_other.m_allocator = allocator_type();
	p_other.m_size = 0;
	p_other.m_first = nullptr;
	p_other.m_last = nullptr;

	return *this;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkList<Elem, Alloc> &dsaa::DoublyLinkList<Elem, Alloc>::operator=(const std::initializer_list<value_type> &p_elements)
{
	clean();
	for (auto i(p_elements.begin()); i != p_elements.end(); ++i)
		insert_last(*i);
	return *this;
}

template <typename Elem, typename Alloc>
dsaa::DoublyLinkList<Elem, Alloc>::~DoublyLinkList()
{
	for (auto i(begin()); i != end(); ++i)
	{
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());
		std::allocator_traits<allocator_type>::deallocate(m_allocator, i.content(), 1);
	}

	m_first = m_last = nullptr;
	m_size = 0;
}

template <typename Elem, typename Alloc>
template <typename IIterator>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::assign(const IIterator &p_first, const IIterator &p_last)
{
	clean();
	insert_last(p_first, p_last);
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::assign(const size_type &p_size, const_reference p_value)
{
	clean();
	insert_last(p_size, p_value);
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::assign(const std::initializer_list<value_type> &p_elements)
{
	clean();
	insert_last(p_elements);
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkListNode<Elem> &dsaa::DoublyLinkList<Elem, Alloc>::first()
{
	return *m_first;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkListNode<Elem> const &dsaa::DoublyLinkList<Elem, Alloc>::first() const
{
	return *m_first;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkListNode<Elem> &dsaa::DoublyLinkList<Elem, Alloc>::last()
{
	return *m_last;
}

template <typename Elem, typename Alloc>
constexpr dsaa::DoublyLinkListNode<Elem> const &dsaa::DoublyLinkList<Elem, Alloc>::last() const
{
	return *m_last;
}

// Returns a copy of the allocator object associated with the DoublyLinkList container.
template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::allocator_type dsaa::DoublyLinkList<Elem, Alloc>::get_allocator() const noexcept
{
	return m_allocator;
}

template <typename Elem, typename Alloc>
constexpr bool dsaa::DoublyLinkList<Elem, Alloc>::empty() const noexcept
{
	return !size();
}

// Returns the number of elements in the DoublyLinkList container.
template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::size_type dsaa::DoublyLinkList<Elem, Alloc>::size() const noexcept
{
	return m_size;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::size_type dsaa::DoublyLinkList<Elem, Alloc>::max_size() const noexcept
{
	return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::size_type dsaa::DoublyLinkList<Elem, Alloc>::get_index(const_iterator p_iterator)
{
	size_type index(0);
	for (auto i(begin()); i != end(); ++i, ++index)
		if (i == p_iterator)
			break;
	return index;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::get_iterator(size_type p_index)
{
	iterator iter(begin());
	for (size_type i(0); i != size(); ++i, ++iter)
		if (i == p_index)
			break;
	return iter;
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::resize(const size_type &p_size, const_reference p_value)
{
	if (size() < p_size)
	{
		size_type num_elements{p_size - size()};
		while (num_elements--)
			insert_last(p_value);
	}
	else
	{
		while (size() != p_size)
			erase_last();
	}
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_first(const_reference p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_value);
	if (m_first)
	{
		m_first->previous() = new_node;
		new_node->next() = m_first;
	}
	else
		m_last = new_node;

	m_first = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_first(value_type &&p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, std::move(p_value));
	if (m_first)
	{
		m_first->previous() = new_node;
		new_node->next() = m_first;
	}
	else
		m_last = new_node;

	m_first = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_first(const size_type &p_size, const_reference p_value)
{
	size_type num_elem(p_size);
	iterator result(insert_first(p_value));
	--num_elem;
	while (num_elem--)
		result = insert_after(result, p_value);
	return result;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_first(const std::initializer_list<value_type> &p_elements)
{
	auto iter(p_elements.begin());
	iterator result(insert_first(*iter));
	++iter;

	for (; iter != p_elements.end(); ++iter)
		result = insert_after(result, *iter);
	return result;
}

template <typename Elem, typename Alloc>
template <class IIterator>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_first(const IIterator &p_first, const IIterator &p_last)
{
	auto iter(p_first);
	iterator result(insert_first(*iter));
	++iter;

	for (; iter != p_last; ++iter)
		result = insert_after(result, *iter);
	return result;
}

template <typename Elem, typename Alloc>
template <class... Args>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::emplace_first(Args &&...p_args)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_args...);
	if (m_first)
	{
		m_first->previous() = new_node;
		new_node->next() = m_first;
	}
	else
		m_last = new_node;

	m_first = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_last(const_reference p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_value);

	if (m_last)
	{
		m_last->next() = new_node;
		new_node->previous() = m_last;
	}
	else
		m_first = new_node;

	m_last = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_last(value_type &&p_value)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, std::move(p_value));

	if (m_last)
	{
		m_last->next() = new_node;
		new_node->previous() = m_last;
	}
	else
		m_first = new_node;

	m_last = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_last(const size_type &p_size, const_reference p_value)
{
	size_type num_elem(p_size);
	iterator result;
	while (num_elem--)
		result = insert_last(p_value);
	return result;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_last(const std::initializer_list<value_type> &p_elements)
{
	iterator result;
	for (auto iter(p_elements.begin()); p_elements.end() != iter; ++iter)
	{
		result = insert_last(*iter);
	}
	return result;
}

template <typename Elem, typename Alloc>
template <class IIterator>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_last(const IIterator &p_first, const IIterator &p_last)
{
	iterator result;
	for (auto iter(p_first); p_last != iter; ++iter)
		result = insert_last(*iter);
	return result;
}

template <typename Elem, typename Alloc>
template <class... Args>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::emplace_last(Args &&...p_args)
{
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_args...);
	if (m_last)
	{
		m_last->next() = new_node;
		new_node->previous() = m_last;
	}
	else
		m_first = new_node;

	m_last = new_node;

	++m_size;
	return iterator(new_node);
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_before(const const_iterator &p_position, const_reference p_value)
{
	iterator iter(p_position);
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_value);
	new_node->previous() = iter.content()->previous();
	new_node->next() = iter.content();

	iter.content()->previous() = new_node;

	if (iter.content() == m_first)
		m_first = new_node;
	++m_size;
	return --iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_before(const const_iterator &p_position, value_type &&p_value)
{
	iterator iter(p_position);
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, std::move(p_value));
	new_node->previous() = iter.content()->previous();
	new_node->next() = iter.content();

	iter.content()->previous() = new_node;

	if (iter.content() == m_first)
		m_first = new_node;
	++m_size;
	return --iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_before(const const_iterator &p_position, const size_type &p_size, const_reference p_value)
{
	iterator iter = insert_before(p_position, p_value);
	size_type size(p_size - 1);

	while (size--)
		iter = insert_after(iter, p_value);

	return iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_before(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements)
{
	iterator iter(p_position);
	auto i(p_elements.begin());

	iter = insert_before(iter, *i);
	++i;

	while (i != p_elements.end())
	{
		iter = insert_after(iter, *i);
		++i;
	}

	return iter;
}

template <typename Elem, typename Alloc>
template <class IIterator>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_before(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last)
{
	iterator iter(p_position);
	IIterator i(p_first);
	iter = insert_before(iter, *i);
	++i;

	while (i != p_last)
	{
		iter = insert_after(iter, *i);
		++i;
	}

	return iter;
}

template <typename Elem, typename Alloc>
template <class... Args>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::emplace_before(const const_iterator &p_position, Args &&...p_args)
{
	iterator iter(p_position);
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_args...);
	new_node->previous() = iter.content()->previous();
	new_node->next() = iter.content();

	iter.content()->previous() = new_node;

	if (iter.content() == m_first)
		m_first = new_node;
	++m_size;
	return --iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_after(const const_iterator &p_position, const_reference p_value)
{
	iterator iter(p_position);
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_value);
	new_node->previous() = iter.content();
	new_node->next() = iter.content()->next();

	iter.content()->next() = new_node;

	if (iter.content() == m_last)
		m_last = new_node;

	++m_size;

	return ++iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_after(const const_iterator &p_position, value_type &&p_value)
{
	iterator iter(p_position);
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, std::move(p_value));
	new_node->previous() = iter.content();
	new_node->next() = iter.content()->next();

	iter.content()->next() = new_node;

	if (iter.content() == m_last)
		m_last = new_node;

	++m_size;

	return ++iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_after(const const_iterator &p_position, const size_type &p_size, const_reference p_value)
{
	size_type size(p_size);
	iterator iter(p_position);
	while (size--)
		iter = insert_after(iter, p_value);
	return iter;
}

template <typename Elem, typename Alloc>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_after(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements)
{
	iterator iter(p_position);

	for (auto i{p_elements.begin()}; i != p_elements.end(); ++i)
		iter = insert_after(iter, *i);

	return iter;
}

template <typename Elem, typename Alloc>
template <typename IIterator>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::insert_after(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last)
{
	iterator iter(p_position);
	IIterator i(p_first);
	while (i != p_last)
	{
		iter = insert_after(iter, *i);
		++i;
	}

	return iter;
}

template <typename Elem, typename Alloc>
template <class... Args>
constexpr typename dsaa::DoublyLinkList<Elem, Alloc>::iterator dsaa::DoublyLinkList<Elem, Alloc>::emplace_after(const const_iterator &p_position, Args &&...p_args)
{
	iterator iter(p_position);
	pointer new_node = std::allocator_traits<allocator_type>::allocate(m_allocator, 1);
	std::allocator_traits<allocator_type>::construct(m_allocator, new_node, p_args...);
	new_node->previous() = iter.content();
	new_node->next() = iter.content()->next();

	iter.content()->next() = new_node;

	if (iter.content() == m_last)
		m_last = new_node;

	++m_size;

	return ++iter;
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::erase_first()
{
	iterator iter(first().next());
	std::allocator_traits<allocator_type>::destroy(m_allocator, m_first);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_first, 1);
	--m_size;
	if (nullptr == iter.content())
	{
		assert(0 == size());
		m_first = m_last = nullptr;
	}
	else
	{
		m_first = iter.content();
		m_first->previous() = nullptr;
	}
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::erase_last()
{
	iterator iter(last().previous());

	std::allocator_traits<allocator_type>::destroy(m_allocator, m_last);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_last, 1);
	--m_size;
	if (nullptr == iter.content())
	{
		assert(0 == size());
		m_first = m_last = nullptr;
	}
	else
	{
		m_last = iter.content();
		m_last->next() = nullptr;
	}
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::erase(const const_iterator &p_position)
{
	if (p_position.content() == m_first)
	{
		erase_first();
		return;
	}
	else if (p_position.content() == m_last)
	{
		erase_last();
		return;
	}

	Iterator iter(p_position);
	iter.content()->next()->previous() = iter.content()->previous();
	iter.content()->previous()->next() = iter.content()->next();

	std::allocator_traits<allocator_type>::destroy(m_allocator, p_position.content());
	std::allocator_traits<allocator_type>::deallocate(m_allocator, p_position.content(), 1);
	--m_size;
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::erase(const const_iterator &p_first, const const_iterator &p_last)
{
	iterator i(p_first);
	while (i != p_last)
	{
		erase(i++);
	}
}

template <typename Elem, typename Alloc>
constexpr void dsaa::DoublyLinkList<Elem, Alloc>::clean() noexcept
{
	while (size())
		erase_first();
}
#endif // !DSAA_DOUBLY_LINK_LIST_H