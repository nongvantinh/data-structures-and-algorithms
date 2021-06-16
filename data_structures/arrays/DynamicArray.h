#ifndef DSAA_ARRAY_H
#define DSAA_ARRAY_H

#include <memory>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iterator>

#include "dsaaTypedefs.h"

namespace dsaa
{
	template <typename Elem, typename Alloc = std::allocator<Elem>>
	class DynamicArray
	{
	public:
		class ConstIterator;
		class Iterator;

		using value_type = Elem;
		using allocator_type = Alloc;
		using reference = value_type &;
		using const_reference = value_type const &;
		using pointer = typename std::allocator_traits<allocator_type>::pointer;
		using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
		using const_iterator = ConstIterator; // A random access iterator to const value_type
		using iterator = Iterator;			  // A random access iterator to value_type.
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using difference_type = typename std::iterator_traits<iterator>::difference_type; // usually the same as ptrdiff_t.
		using size_type = size_t;

		// Returns an iterator pointing to the first element in the container.
		NODISCARD CONSTEXPR INLINE iterator begin() noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator begin() const noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator cbegin() const noexcept;
		// Returns an iterator referring to the past-the-end element in the container.
		NODISCARD CONSTEXPR INLINE iterator end() noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator end() const noexcept;
		NODISCARD CONSTEXPR INLINE const_iterator cend() const noexcept;
		// Returns a reverse_iterator pointing to the last element in the container.
		NODISCARD CONSTEXPR INLINE reverse_iterator rbegin() noexcept;
		NODISCARD CONSTEXPR INLINE const_reverse_iterator rbegin() const noexcept;
		NODISCARD CONSTEXPR INLINE const_reverse_iterator crbegin() const noexcept;
		// Returns a reverse iterator pointing to the theoretical element preceding the first element in the container.
		NODISCARD CONSTEXPR INLINE reverse_iterator rend() noexcept;
		NODISCARD CONSTEXPR INLINE const_reverse_iterator rend() const noexcept;
		NODISCARD CONSTEXPR INLINE const_reverse_iterator crend() const noexcept;

		// Creates a container with no element.
		CONSTEXPR DynamicArray(const allocator_type &p_allocator = allocator_type()) noexcept;
		// Creates a container's p_size elements with default value.
		CONSTEXPR explicit DynamicArray(const size_type &p_size, const allocator_type &p_allocator = allocator_type());
		// Creates a container's p_size elements and init its element by p_value.
		CONSTEXPR DynamicArray(const size_type &p_size, const_reference p_value, const allocator_type &p_allocator = allocator_type());
		// Creates a container's size equal to p_elements's size and init its elements by p_elements's element.
		CONSTEXPR DynamicArray(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type());
		// Creates a container and init its elements by content of IIterator in range (first, last].
		template <typename IIterator>
		CONSTEXPR DynamicArray(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator = allocator_type());
		// Creates a container and copy all emements from p_other.
		CONSTEXPR DynamicArray(const DynamicArray &p_other);
		// Creates a container and copy all emements from p_other.
		CONSTEXPR DynamicArray(const DynamicArray &p_other, const allocator_type &p_allocator);
		// Moves all elements from p_other into this.
		CONSTEXPR DynamicArray(DynamicArray &&p_other) noexcept;
		// Moves all elements from p_other into this.
		CONSTEXPR DynamicArray(DynamicArray &&p_other, const allocator_type &p_allocator) noexcept;
		// Destroys old elements and copy all emements from p_other into this.
		CONSTEXPR DynamicArray &operator=(const DynamicArray &p_other);
		// Destroys old elements and moves all emements from p_other into this.
		CONSTEXPR DynamicArray &operator=(DynamicArray &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value);
		// Destroys old elements and copy all elements from p_elements.
		CONSTEXPR DynamicArray &operator=(const std::initializer_list<value_type> &p_elements);
		// Destroys all elements and clean used space.
		virtual ~DynamicArray();

		// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		template <typename IIterator>
		CONSTEXPR void assign(const IIterator &p_first, const IIterator &p_last);
		CONSTEXPR void assign(const size_type &p_size, const value_type &p_value = value_type());
		CONSTEXPR void assign(const std::initializer_list<value_type> &p_elements);

		// Returns a reference to the element at position p_index in the container.
		NODISCARD CONSTEXPR INLINE reference operator[](const size_type &p_index) NOEXCEPT;
		NODISCARD CONSTEXPR INLINE const_reference operator[](const size_type &p_index) const NOEXCEPT;
		// Bounds checking that returns a reference to the element at position p_index in the container.
		NODISCARD CONSTEXPR INLINE reference at(const size_type &p_index);
		NODISCARD CONSTEXPR INLINE const_reference at(const size_type &p_index) const;
		// Returns a reference to the first element in the container.
		NODISCARD CONSTEXPR INLINE reference first() NOEXCEPT;
		NODISCARD CONSTEXPR INLINE const_reference first() const NOEXCEPT;
		// Returns a reference to the last element in the container.
		NODISCARD CONSTEXPR INLINE reference last() NOEXCEPT;
		NODISCARD CONSTEXPR INLINE const_reference last() const NOEXCEPT;
		// Returns a direct pointer to the memory array used internally by the container to store its owned elements.
		NODISCARD CONSTEXPR INLINE pointer data() noexcept;
		NODISCARD CONSTEXPR INLINE const_pointer data() const noexcept;
		// Returns a copy of the allocator object associated with the container.
		NODISCARD CONSTEXPR INLINE allocator_type get_allocator() const noexcept;

		// Test whether container is empty.
		NODISCARD CONSTEXPR INLINE bool empty() const noexcept;
		// Returns the size of the storage space currently allocated for the container.
		NODISCARD CONSTEXPR INLINE size_type capacity() const noexcept;
		// Returns the number of elements in the container.
		NODISCARD CONSTEXPR INLINE size_type size() const noexcept;
		// Returns the maximum number of elements that the container can hold.
		NODISCARD CONSTEXPR INLINE size_type max_size() const noexcept;
		// Gets the corresponding index for given iterator.
		NODISCARD CONSTEXPR INLINE size_type get_index(const const_iterator &p_position) NOEXCEPT;
		// Gets the corresponding iterator for given index.
		NODISCARD CONSTEXPR INLINE iterator get_iterator(const size_type &p_index) NOEXCEPT;
		// Resizes the container so that it contains p_size elements.
		CONSTEXPR void resize(const size_type &p_size, const_reference p_value = value_type());
		// Allocates new space and copy elements to new space.
		CONSTEXPR void reserve(const size_type &p_capacity);
		// Requests the container to reduce its capacity to fit its size.
		CONSTEXPR void shrink_to_fit();

		// Increase DynamicArray size by one, initialize new element with p_value.
		CONSTEXPR iterator insert_last(const_reference p_value);
		CONSTEXPR iterator insert_last(value_type &&p_value);
		CONSTEXPR iterator insert_last(const size_type &p_size, const_reference p_value);
		CONSTEXPR iterator insert_last(const std::initializer_list<value_type> &p_elements);
		template <class IIterator>
		CONSTEXPR iterator insert_last(const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		CONSTEXPR iterator emplace_last(Args &&...p_args);

		CONSTEXPR iterator insert_at(const const_iterator &p_position, const_reference p_value);
		CONSTEXPR iterator insert_at(const const_iterator &p_position, value_type &&p_value);
		CONSTEXPR iterator insert_at(const const_iterator &p_position, const size_type &p_size, const_reference p_value);
		CONSTEXPR iterator insert_at(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements);
		template <class IIterator>
		CONSTEXPR iterator insert_at(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last);
		template <class... Args>
		CONSTEXPR iterator emplace_at(const const_iterator &p_position, Args &&...p_args);

		// Destroy element at p_position and reduce size of container.
		CONSTEXPR void erase_at(const const_iterator &p_position) NOEXCEPT;
		// Destroy element in range (first,last] and reduce size of container.
		CONSTEXPR void erase(const const_iterator &p_first, const const_iterator &p_last) NOEXCEPT;
		// Removes the last element in the vector, effectively reducing the container size by one.
		CONSTEXPR INLINE void erase_last() noexcept;
		// Destroys all elements from the container, leaving the size of 0.
		CONSTEXPR INLINE void clear() noexcept;

		// Exchanges the content of the container by the content of p_other,
		// which is another DynamicArray object of the same type. Sizes may differ.
		CONSTEXPR void swap(DynamicArray &p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value || std::allocator_traits<allocator_type>::is_always_equal::value);

	protected:
		allocator_type m_allocator;
		size_type m_capacity;
		size_type m_size;
		pointer m_elements;
	};
}

template <typename Elem, typename Alloc>
class dsaa::DynamicArray<Elem, Alloc>::ConstIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = Elem;
	using difference_type = std::ptrdiff_t;
	using pointer = Elem *;
	using const_pointer = Elem const *;
	using reference = Elem &;

	CONSTEXPR ConstIterator() noexcept : m_pointer(nullptr) {}
	CONSTEXPR explicit ConstIterator(const_pointer p_pointer) noexcept : m_pointer(const_cast<pointer>(p_pointer)) {}
	CONSTEXPR ConstIterator(const ConstIterator &p_iterator) noexcept : m_pointer(p_iterator.m_pointer) {}

	CONSTEXPR ConstIterator &operator=(const ConstIterator &p_iterator) noexcept
	{
		m_pointer = p_iterator.m_pointer;
		return *this;
	}

	virtual ~ConstIterator() {}

	NODISCARD CONSTEXPR INLINE bool operator==(const ConstIterator &p_iterator) const noexcept { return m_pointer == p_iterator.m_pointer; }
	NODISCARD CONSTEXPR INLINE bool operator!=(const ConstIterator &p_iterator) const noexcept { return m_pointer != p_iterator.m_pointer; }

	CONSTEXPR INLINE ConstIterator &operator++()
	{
		++m_pointer;
		return *this;
	}

	CONSTEXPR INLINE ConstIterator operator++(int)
	{
		ConstIterator old(*this); // copy old value
		operator++();			  // prefix increment
		return old;				  // return old value
	}

	CONSTEXPR INLINE ConstIterator &operator--()
	{
		--m_pointer;
		return *this;
	}

	CONSTEXPR INLINE ConstIterator operator--(int)
	{
		ConstIterator old(*this);
		operator--();
		return old;
	}

	NODISCARD CONSTEXPR INLINE ConstIterator operator+(const int64_t &p_rhs) const
	{
		ConstIterator result;
		result.m_pointer = m_pointer + p_rhs;
		return result;
	}

	NODISCARD CONSTEXPR INLINE ConstIterator operator-(const int64_t &p_rhs) const
	{
		ConstIterator result;
		result.m_pointer = m_pointer - p_rhs;
		return result;
	}

	CONSTEXPR INLINE ConstIterator &operator+=(const int64_t &p_rhs)
	{
		m_pointer += p_rhs;
		return *this;
	}

	CONSTEXPR INLINE ConstIterator &operator-=(const int64_t &p_rhs)
	{
		m_pointer -= p_rhs;
		return *this;
	}

	NODISCARD CONSTEXPR INLINE int64_t operator-(const ConstIterator &p_rhs) const
	{
		int64_t result{m_pointer - p_rhs.m_pointer};
		return result;
	}

	NODISCARD CONSTEXPR INLINE bool operator<(const ConstIterator &p_rhs) const
	{
		return (m_pointer - p_rhs.m_pointer) < 0;
	}

	NODISCARD CONSTEXPR INLINE bool operator>(const ConstIterator &p_rhs) const
	{
		return 0 < (m_pointer - p_rhs.m_pointer);
	}

	NODISCARD CONSTEXPR INLINE bool operator<=(const ConstIterator &p_rhs) const
	{
		return (m_pointer - p_rhs.m_pointer) <= 0;
	}

	NODISCARD CONSTEXPR INLINE bool operator>=(const ConstIterator &p_rhs) const
	{
		return 0 <= (m_pointer - p_rhs.m_pointer);
	}

	NODISCARD CONSTEXPR INLINE const reference operator*() const { return *m_pointer; }
	NODISCARD CONSTEXPR INLINE const reference operator[](const int64_t &p_index) const { return m_pointer[p_index]; }
	NODISCARD CONSTEXPR INLINE const_pointer content() const noexcept { return m_pointer; }

protected:
	pointer m_pointer;
};

template <typename Elem, typename Alloc>
class dsaa::DynamicArray<Elem, Alloc>::Iterator : public dsaa::DynamicArray<Elem, Alloc>::ConstIterator
{
public:
	CONSTEXPR Iterator() noexcept : ConstIterator() {}
	CONSTEXPR Iterator(pointer p_pointer) noexcept : ConstIterator(p_pointer) {}
	CONSTEXPR Iterator(const Iterator &p_iterator) noexcept : ConstIterator(p_iterator) {}
	CONSTEXPR Iterator(const ConstIterator &p_iterator) noexcept : ConstIterator(p_iterator) {}

	CONSTEXPR Iterator &operator=(const Iterator &p_iterator) noexcept
	{
		content() = p_iterator.content();
		return *this;
	}

	virtual ~Iterator() {}

	NODISCARD CONSTEXPR INLINE bool operator==(const Iterator &p_iterator) const noexcept { return content() == p_iterator.content(); }
	NODISCARD CONSTEXPR INLINE bool operator!=(const Iterator &p_iterator) const noexcept { return content() != p_iterator.content(); }

	CONSTEXPR INLINE Iterator &operator++()
	{
		++content();
		return *this;
	}

	CONSTEXPR INLINE Iterator operator++(int)
	{
		Iterator old(*this); // copy old value
		operator++();		 // prefix increment
		return old;			 // return old value
	}

	CONSTEXPR INLINE Iterator &operator--()
	{
		--content();
		return *this;
	}

	CONSTEXPR INLINE Iterator operator--(int)
	{
		Iterator old(*this);
		operator--();
		return old;
	}

	NODISCARD CONSTEXPR INLINE Iterator operator+(const int64_t &p_rhs) const
	{
		Iterator result;
		result.content() = content() + p_rhs;
		return result;
	}

	NODISCARD CONSTEXPR INLINE Iterator operator-(const int64_t &p_rhs) const
	{
		Iterator result;
		result.content() = content() - p_rhs;
		return result;
	}

	CONSTEXPR INLINE Iterator &operator+=(const int64_t &p_rhs)
	{
		content() += p_rhs;
		return *this;
	}

	CONSTEXPR INLINE Iterator &operator-=(const int64_t &p_rhs)
	{
		content() -= p_rhs;
		return *this;
	}

	NODISCARD CONSTEXPR INLINE int64_t operator-(const Iterator &p_rhs) const
	{
		int64_t result{content() - p_rhs.content()};
		return result;
	}

	NODISCARD CONSTEXPR INLINE bool operator<(const Iterator &p_rhs) const
	{
		return (content() - p_rhs.content()) < 0;
	}

	NODISCARD CONSTEXPR INLINE bool operator>(const Iterator &p_rhs) const
	{
		return 0 < (content() - p_rhs.content());
	}

	NODISCARD CONSTEXPR INLINE bool operator<=(const Iterator &p_rhs) const
	{
		return (content() - p_rhs.content()) <= 0;
	}

	NODISCARD CONSTEXPR INLINE bool operator>=(const Iterator &p_rhs) const
	{
		return 0 <= (content() - p_rhs.content());
	}

	NODISCARD CONSTEXPR INLINE reference operator*() { return *ConstIterator::m_pointer; }
	NODISCARD CONSTEXPR INLINE reference operator[](const int64_t &p_index) { return ConstIterator::m_pointer[p_index]; }
	NODISCARD CONSTEXPR INLINE pointer &content() { return ConstIterator::m_pointer; }
	NODISCARD CONSTEXPR INLINE pointer content() const { return ConstIterator::m_pointer; }
};

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::begin() noexcept
{
	return size() ? iterator(&m_elements[0]) : iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_iterator dsaa::DynamicArray<Elem, Alloc>::begin() const noexcept
{
	return size() ? const_iterator(&m_elements[0]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_iterator dsaa::DynamicArray<Elem, Alloc>::cbegin() const noexcept
{
	return size() ? const_iterator(&m_elements[0]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::end() noexcept
{
	return size() ? iterator(&m_elements[size()]) : iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_iterator dsaa::DynamicArray<Elem, Alloc>::end() const noexcept
{
	return size() ? const_iterator(&m_elements[size()]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_iterator dsaa::DynamicArray<Elem, Alloc>::cend() const noexcept
{
	return size() ? const_iterator(&m_elements[size()]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::reverse_iterator dsaa::DynamicArray<Elem, Alloc>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reverse_iterator dsaa::DynamicArray<Elem, Alloc>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reverse_iterator dsaa::DynamicArray<Elem, Alloc>::crbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::reverse_iterator dsaa::DynamicArray<Elem, Alloc>::rend() noexcept
{
	return reverse_iterator(begin());
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reverse_iterator dsaa::DynamicArray<Elem, Alloc>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reverse_iterator dsaa::DynamicArray<Elem, Alloc>::crend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const allocator_type &p_allocator) noexcept
	: m_allocator(p_allocator), m_capacity(0), m_size(0), m_elements(nullptr) {}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const size_type &p_size, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_capacity(p_size), m_size(p_size), m_elements(nullptr)
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, i.content(), value_type());
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const size_type &p_size, const_reference p_value, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_capacity(p_size), m_size(p_size), m_elements(nullptr)
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, i.content(), p_value);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_capacity(p_elements.size()), m_size(p_elements.size()), m_elements(nullptr)
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	iterator iter(m_elements);
	for (auto i(p_elements.begin()); i != p_elements.end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);
}

template <typename Elem, typename Alloc>
template <typename IIterator>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_capacity(0), m_size(0), m_elements(nullptr)
{
	size_type count_size(0);
	for (auto iter(p_first); iter != p_last; ++iter)
		++count_size;

	reserve(count_size);

	for (auto iter(p_first); iter != p_last; ++iter)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], *iter);
		++m_size;
	}
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const DynamicArray &p_other)
	: m_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.get_allocator())),
	  m_capacity(p_other.size()), m_size(p_other.size()), m_elements(nullptr)
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	iterator iter(m_elements);
	for (const_iterator i(p_other.begin()); i != p_other.end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(const DynamicArray &p_other, const allocator_type &p_allocator)
	: m_allocator(p_allocator), m_capacity(p_other.size()), m_size(p_other.size()), m_elements(nullptr)
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	iterator iter(m_elements);
	for (const_iterator i(p_other.begin()); i != p_other.end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(DynamicArray &&p_other) noexcept
	: m_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.get_allocator())),
	  m_capacity(p_other.capacity()), m_size(p_other.size()), m_elements(p_other.m_elements)
{
	p_other.m_allocator = allocator_type();
	p_other.m_capacity = 0;
	p_other.m_size = 0;
	p_other.m_elements = nullptr;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc>::DynamicArray(DynamicArray &&p_other, const allocator_type &p_allocator) noexcept
	: m_allocator(p_allocator), m_capacity(p_other.capacity()), m_size(p_other.size()), m_elements(p_other.m_elements)
{
	p_other.m_allocator = allocator_type();
	p_other.m_capacity = 0;
	p_other.m_size = 0;
	p_other.m_elements = nullptr;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc> &dsaa::DynamicArray<Elem, Alloc>::operator=(const DynamicArray &p_other)
{
	// Avoid self-reference.
	if (this == &p_other)
		return *this;

	// No need to allocate new space if we already have enough capacity.
	if (p_other.size() <= capacity())
	{
		// Destroy old elements.
		for (iterator i(begin()); i != end(); ++i)
			std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());
		// Copy.
		iterator iter(m_elements);
		for (const_iterator i(p_other.begin()); i != p_other.end(); ++i, ++iter)
			std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);

		m_size = p_other.size();
		return *this;
	}

	// Quarantees elements are copies and no error happens before delete old elements.
	pointer elements(std::allocator_traits<allocator_type>::allocate(m_allocator, p_other.size()));
	iterator iter(elements);
	for (const_iterator i(p_other.begin()); i != p_other.end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);
	// Destroy old elements.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());
	m_capacity = m_size = p_other.size();
	m_elements = elements;
	return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc> &dsaa::DynamicArray<Elem, Alloc>::operator=(DynamicArray &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value)
{
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	// Difference allocator may throw...!
	m_allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.get_allocator());
	m_capacity = p_other.capacity();
	m_size = p_other.size();
	m_elements = p_other.m_elements;

	p_other.m_allocator = allocator_type();
	p_other.m_capacity = 0;
	p_other.m_size = 0;
	p_other.m_elements = nullptr;

	return *this;
}

template <typename Elem, typename Alloc>
CONSTEXPR dsaa::DynamicArray<Elem, Alloc> &dsaa::DynamicArray<Elem, Alloc>::operator=(const std::initializer_list<value_type> &p_elements)
{
	// Quarantees elements are copies and no error happens before delete old elements.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_elements.size());
	iterator iter(elements);
	for (auto i(p_elements.begin()); i != p_elements.end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);

	// Destroy old elements.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = m_size = p_elements.size();
	m_elements = elements;
	return *this;
}

template <typename Elem, typename Alloc>
dsaa::DynamicArray<Elem, Alloc>::~DynamicArray()
{
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());
}

// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
template <typename Elem, typename Alloc>
template <typename IIterator>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::assign(const IIterator &p_first, const IIterator &p_last)
{
	for (iterator i(begin()); end() != i; ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	m_size = 0;

	size_type count_size(0);
	for (auto iter(p_first); iter != p_last; ++iter)
		++count_size;

	reserve(count_size);

	for (auto iter(p_first); iter != p_last; ++iter)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], *iter);
		++m_size;
	}
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::assign(const size_type &p_size, const value_type &p_value)
{
	// Allocate new space.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_size);
	for (size_type i = 0; i < p_size; ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, &elements[i], p_value);

	// Clean up old allocated space.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = m_size = p_size;
	m_elements = elements;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::assign(const std::initializer_list<value_type> &p_elements)
{
	// Quarantees elements are copies and no error happens before delete old elements.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_elements.size());
	iterator iter(elements);
	for (auto i(p_elements.begin()); i != p_elements.end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);

	// Destroy old elements.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = m_size = p_elements.size();
	m_elements = elements;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::reference dsaa::DynamicArray<Elem, Alloc>::operator[](const size_type &p_index) NOEXCEPT
{
#ifdef PARAM_CHECK
	if (size() <= p_index)
		throw std::out_of_range("p_index out of range exception.\n;");
#endif

	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reference dsaa::DynamicArray<Elem, Alloc>::operator[](const size_type &p_index) const NOEXCEPT
{
#ifdef PARAM_CHECK
	if (size() <= p_index)
		throw std::out_of_range("p_index out of range exception.\n;");
#endif

	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::reference dsaa::DynamicArray<Elem, Alloc>::at(const size_type &p_index)
{
	if (size() <= p_index)
		throw std::out_of_range("p_index out of range exception.\n;");

	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reference dsaa::DynamicArray<Elem, Alloc>::at(const size_type &p_index) const
{
	if (size() <= p_index)
		throw std::out_of_range("p_index out of range exception.\n");

	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::reference dsaa::DynamicArray<Elem, Alloc>::first() NOEXCEPT
{
#ifdef PARAM_CHECK
	if (!size())
		throw std::runtime_error("size() is zero, which means DynamicArray currently empty.");
#endif

	return m_elements[0];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reference dsaa::DynamicArray<Elem, Alloc>::first() const NOEXCEPT
{
#ifdef PARAM_CHECK
	if (!size())
		throw std::runtime_error("size() is zero, which means DynamicArray currently empty.");
#endif

	return m_elements[0];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::reference dsaa::DynamicArray<Elem, Alloc>::last() NOEXCEPT
{
#ifdef PARAM_CHECK
	if (!size())
		throw std::runtime_error("size() is zero, which means DynamicArray currently empty.");
#endif

	return m_elements[size() - 1];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_reference dsaa::DynamicArray<Elem, Alloc>::last() const NOEXCEPT
{
#ifdef PARAM_CHECK
	if (!size())
		throw std::runtime_error("size() is zero, which means DynamicArray currently empty.");
#endif

	return m_elements[size() - 1];
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::pointer dsaa::DynamicArray<Elem, Alloc>::data() noexcept
{
	return m_elements;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::const_pointer dsaa::DynamicArray<Elem, Alloc>::data() const noexcept
{
	return m_elements;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::allocator_type dsaa::DynamicArray<Elem, Alloc>::get_allocator() const noexcept
{
	return m_allocator;
}

template <typename Elem, typename Alloc>
CONSTEXPR bool dsaa::DynamicArray<Elem, Alloc>::empty() const noexcept
{
	return size() == 0;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::size_type dsaa::DynamicArray<Elem, Alloc>::capacity() const noexcept
{
	return m_capacity;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::size_type dsaa::DynamicArray<Elem, Alloc>::size() const noexcept
{
	return m_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::size_type dsaa::DynamicArray<Elem, Alloc>::max_size() const noexcept
{
	return std::numeric_limits<value_type>::max() / sizeof(value_type);
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::resize(const size_type &p_size, const value_type &p_value)
{
	reserve(p_size);
	if (size() <= p_size)
	{
		iterator from(&m_elements[size()]), to(&m_elements[size() + p_size]);
		while (from != to)
		{
			std::allocator_traits<allocator_type>::construct(m_allocator, from.content(), p_value);
			++from;
		}
	}
	else
	{
		iterator from(get_iterator(p_size)), to(end());
		while (from != to)
		{
			std::allocator_traits<allocator_type>::destroy(m_allocator, from.content());
			++from;
		}
	}

	m_size = p_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::reserve(const size_type &p_capacity)
{
	// Never decrease allocation.
	if (p_capacity <= m_capacity)
		return;

	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_capacity);
	// Copy old element to new place.
	iterator iter(elements);
	for (iterator i(begin()); i != end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);
	// Clean up old allocated space.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = p_capacity;
	m_elements = elements;
}

// Requests the container to reduce its capacity to fit its size.
template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::shrink_to_fit()
{
	if (size() == capacity())
		return;
	// Allocate new space.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, size());
	// Copy old element to new place.
	iterator iter(elements);
	for (const_iterator i(begin()); i != end(); ++i, ++iter)
		std::allocator_traits<allocator_type>::construct(m_allocator, iter.content(), *i);
	// Clean up old allocated space.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = size();
	m_elements = elements;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::size_type dsaa::DynamicArray<Elem, Alloc>::get_index(const const_iterator &p_position) NOEXCEPT
{
#ifdef PARAM_CHECK
	if (!size())
		throw std::runtime_error("size() is zero, which means DynamicArray currently empty.");
	if (p_position < begin())
		throw std::range_error("Specified position is smaller than the index in array.\n");
	if (end() < p_position)
		throw std::range_error("Specified position is greater than the index in array.\n");
#endif

	return p_position - iterator(&m_elements[0]);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::get_iterator(const size_type &p_index) NOEXCEPT
{
#ifdef PARAM_CHECK
	if (!size())
		throw std::runtime_error("size() is zero, which means DynamicArray currently empty.");
	if (size() < p_index)
		throw std::range_error("Specified position is greater than the index in array.\n");
#endif

	return iterator(&m_elements[0]) + p_index;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_last(const_reference p_value)
{
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], p_value);
	++m_size;
	return iterator(end() - 1);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_last(value_type &&p_value)
{
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.
	std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], std::move(p_value));
	++m_size;
	return end() - 1;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_last(const size_type &p_size, const_reference p_value)
{
	if (capacity() < size() + p_size)
		reserve(size() + p_size);

	size_type num_elem(p_size);
	while (num_elem--)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], p_value);
		++m_size;
	}
	return end() - 1;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_last(const std::initializer_list<value_type> &p_elements)
{
	if (capacity() < size() + p_elements.size())
		reserve(size() + p_elements.size());

	for (auto iter(p_elements.begin()); iter != p_elements.end(); ++iter)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], *iter);
		++m_size;
	}
	return end() - 1;
}

template <typename Elem, typename Alloc>
template <class IIterator>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_last(const IIterator &p_first, const IIterator &p_last)
{
	size_type count_size(0);
	for (auto iter(p_first); iter != p_last; ++iter)
		++count_size;

	if (capacity() < size() + count_size)
		reserve(size() + count_size);

	for (auto iter(p_first); iter != p_last; ++iter)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], *iter);
		++m_size;
	}

	return end() - 1;
}

template <typename Elem, typename Alloc>
template <class... Args>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::emplace_last(Args &&...p_args)
{
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], p_args...);
	++m_size;
	return iterator(end() - 1);
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_at(const const_iterator &p_position, const_reference p_value)
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() < p_position)
		throw std::invalid_argument("p_position can not greater than end().\n");
#endif

	size_t index(get_index(p_position)); // reserve can make iterator to p_position become invalid.
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	// First copy last element into uninitialized space.
	std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], last());
	++m_size;

	iterator desired(get_iterator(index)); // The place to put value.
	for (iterator last_elem(&last()); last_elem != desired; --last_elem)
		*last_elem = *(last_elem - 1); // Copy element one position to the right.

	*desired = p_value; // Insert value;

	return desired;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_at(const const_iterator &p_position, value_type &&p_value)
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() < p_position)
		throw std::invalid_argument("p_position can not greater than end().\n");
#endif

	size_t index(get_index(p_position));
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	// First copy last element into uninitialized space.
	std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], last());
	++m_size;

	iterator position(get_iterator(index)); // The place to put value.
	for (iterator last_elem(end() - 1); last_elem != position; --last_elem)
		*last_elem = *(last_elem - 1); // Copy element one position to the right.

	*position = std::move(p_value); // Insert value;

	return position;
}
template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_at(const const_iterator &p_position, const size_type &p_size, const_reference p_value)
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() < p_position)
		throw std::invalid_argument("p_position can not greater than end().\n");
#endif

	size_type index(get_index(p_position));

	if (capacity() < size() + p_size)
		reserve(size() + p_size);

	iterator pivot(get_iterator(index));
	iterator convey(get_iterator(size() - 1));
	// Have to access element directly, get_iterator when add bound check will cause problem.
	iterator target(&m_elements[size() + p_size - 1]);

	while (pivot <= convey)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, target.content(), *convey);
		std::allocator_traits<allocator_type>::destroy(m_allocator, convey.content());
		--target;
		--convey;
	}
	++convey;
	++target;
	while (convey != target)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, convey.content(), p_value);
		++convey;
	}

	m_size += p_size;

	return --convey;
}

template <typename Elem, typename Alloc>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_at(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements)
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() < p_position)
		throw std::invalid_argument("p_position can not greater than end().\n");
#endif

	size_type index(get_index(p_position));

	if (capacity() < size() + p_elements.size())
		reserve(size() + p_elements.size());

	iterator pivot(get_iterator(index));
	iterator convey(get_iterator(size() - 1));
	// Have to access element directly, get_iterator when add bound check will cause problem.
	iterator target(&m_elements[size() + p_elements.size() - 1]);

	while (pivot <= convey)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, target.content(), *convey);
		std::allocator_traits<allocator_type>::destroy(m_allocator, convey.content());
		--target;
		--convey;
	}
	++convey;
	++target;
	for (auto iter(p_elements.begin()); iter != p_elements.end(); ++iter, ++convey)
		std::allocator_traits<allocator_type>::construct(m_allocator, convey.content(), *iter);

	m_size += p_elements.size();

	return --convey;
}

template <typename Elem, typename Alloc>
template <class IIterator>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::insert_at(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last)
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() < p_position)
		throw std::invalid_argument("p_position can not greater than end().\n");
#endif

	size_type index(get_index(p_position));
	size_type count_size(0);
	for (auto i(p_first); i != p_last; ++i)
		++count_size;
	if (capacity() < size() + count_size)
		reserve(size() + count_size);

	iterator pivot(get_iterator(index));
	iterator convey(get_iterator(size() - 1));
	// Have to access element directly, get_iterator when add bound check will cause problem.
	iterator target(&m_elements[size() + count_size - 1]);

	while (pivot <= convey)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, target.content(), *convey);
		std::allocator_traits<allocator_type>::destroy(m_allocator, convey.content());
		--target;
		--convey;
	}
	++convey;
	++target;
	for (auto first(p_first); first != p_last; ++first, ++convey)
	{
		std::allocator_traits<allocator_type>::construct(m_allocator, convey.content(), *first);
	}

	m_size += count_size;

	return --convey;
}

template <typename Elem, typename Alloc>
template <class... Args>
CONSTEXPR typename dsaa::DynamicArray<Elem, Alloc>::iterator dsaa::DynamicArray<Elem, Alloc>::emplace_at(const const_iterator &p_position, Args &&...p_args)
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() < p_position)
		throw std::invalid_argument("p_position can not greater than end().\n");
#endif

	size_t index(get_index(p_position)); // reserve can make iterator to p_position become invalid.
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	// First copy last element into uninitialized space.
	std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[m_size], last());
	++m_size;

	iterator desired(get_iterator(index)); // The place to put value.
	for (iterator last_elem(&last()); last_elem != desired; --last_elem)
		*last_elem = *(last_elem - 1); // Copy element one position to the right.

	std::allocator_traits<allocator_type>::destroy(m_allocator, desired.content());
	std::allocator_traits<allocator_type>::construct(m_allocator, desired.content(), p_args...);

	return desired;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::erase_at(const const_iterator &p_position) NOEXCEPT
{
#ifdef PARAM_CHECK
	if (p_position < begin())
		throw std::invalid_argument("p_position can not less than begin().\n");
	if (end() <= p_position)
		throw std::invalid_argument("p_position can not greater than last().\n");
#endif

	for (iterator position(p_position + 1); position != end(); ++position)
	{
		*(position - 1) = *position;
	}

	erase_last();
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::erase(const const_iterator &p_first, const const_iterator &p_last) NOEXCEPT
{
#ifdef PARAM_CHECK
	if (p_last < p_first)
		throw std::invalid_argument("p_first can not less than p_last.\n");
	if (p_first < begin())
		throw std::invalid_argument("p_first can not less than begin().\n");
	if (end() < p_last)
		throw std::invalid_argument("p_last can not greater than end().\n");
#endif

	iterator first(p_first), last(p_last);

	while (last != end())
	{
		*first = *last;
		++first;
		++last;
	}

	int offset(end() - first);
	while (first != end())
	{
		std::allocator_traits<allocator_type>::destroy(m_allocator, first.content());
		++first;
	}
	m_size -= offset;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::erase_last() noexcept
{
#ifdef PARAM_CHECK
	if (size() == 0)
		std::terminate();
		// throw std::runtime_error("size is 0, there is nothing to erase.\n");
#endif

	std::allocator_traits<allocator_type>::destroy(m_allocator, &m_elements[size() - 1]);
	--m_size;
}

template <typename Elem, typename Alloc>
CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::clear() noexcept
{
	// Clean up all elements.
	for (iterator i(begin()); i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i.content());

	m_size = 0;
}

// template <typename Elem, typename Alloc>
// CONSTEXPR void dsaa::DynamicArray<Elem, Alloc>::swap(DynamicArray &p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value || std::allocator_traits<allocator_type>::is_always_equal::value)
// {
// }

#endif // !DSAA_ARRAY_H