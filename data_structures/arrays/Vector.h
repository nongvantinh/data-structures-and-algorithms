#ifndef VECTOR_H
#define VECTOR_H

#include <memory> 
#include <initializer_list>
#include <algorithm> 
#include <stdexcept>
#include <iterator>

namespace dsaa
{
	namespace array
	{
		template <typename Elem, typename Alloc = std::allocator<Elem>>
		class Vector
		{
		public:
			using value_type = Elem;
			using const_value_type = const value_type;
			using reference = value_type&;
			using const_reference = const value_type&;
			using allocator_type = Alloc;
			using size_type = size_t;
			using pointer = typename std::allocator_traits<allocator_type>::pointer; // Equivalent to: value_type*
			using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer; // Equivalent to: const value_type*
			using iterator = value_type*; // A random access iterator to value_type.
			using const_iterator = const value_type*; // A random access iterator to const value_type
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;
			// An unsigned integral type that can represent any non-negative value of difference_type usually the same as size_t.
			using difference_type = typename std::iterator_traits<iterator>::difference_type; // usually the same as ptrdiff_t.

			// Returns an iterator pointing to the first element in the vector.
			iterator begin() noexcept;
			const_iterator begin() const noexcept;
			// Returns an iterator referring to the past-the-end element in the vector container.
			iterator end() noexcept;
			const_iterator end() const noexcept;
			// Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator rbegin() const noexcept;
			// Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
			// (which is considered its reverse end).
			reverse_iterator rend() noexcept;
			const_reverse_iterator rend() const noexcept;
			// Returns a const_iterator pointing to the first element in the container.
			const_iterator cbegin() const noexcept;
			// Returns a const_iterator pointing to the past-the-end element in the container.
			const_iterator cend() const noexcept;
			// Returns a const_reverse_iterator pointing to the last element in the container (i.e., its reverse beginning).
			const_reverse_iterator crbegin() const noexcept;
			// Returns a const_reverse_iterator pointing to the theoretical element preceding the first element in the container
			// (which is considered its reverse end).
			const_reverse_iterator crend() const noexcept;

			Vector(const allocator_type& p_allocator = allocator_type());
			explicit Vector(const size_type& p_size, const allocator_type& p_allocator = allocator_type());
			Vector(const size_type& p_size, const_reference p_value, const allocator_type& p_allocator = allocator_type());
			Vector(const Vector& p_other);
			Vector(const Vector& p_other, const allocator_type& p_allocator);
			Vector(Vector&& p_other);
			Vector(Vector&& p_other, const allocator_type& p_allocator);
			Vector& operator=(const Vector& p_other);
			Vector& operator=(Vector&& p_other);
			Vector& operator= (std::initializer_list<value_type> p_elements);
			Vector(std::initializer_list<value_type> p_elements, const allocator_type& p_allocator = allocator_type());
			template<typename IIterator>
			Vector(IIterator p_first, IIterator p_last, const allocator_type& p_allocator = allocator_type());
			~Vector();

			// Returns a reference to the element at position p_index in the vector container.
			reference operator[](size_type p_index);
			const_reference operator[](size_type p_index) const;
			// Returns a reference to the element at position p_index in the vector.
			reference at(const size_type& p_index);
			const_reference at(const size_type& p_index) const;
			// Returns a reference to the first element in the vector.
			reference front();
			const_reference front() const;
			// Returns a reference to the last element in the vector.
			reference back();
			const_reference back() const;
			// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
			pointer data() noexcept;
			const_pointer data() const noexcept;
			// Returns a copy of the allocator object associated with the vector.
			allocator_type get_allocator() const noexcept;
			// Test whether vector is empty.
			bool empty() const noexcept;
			// Returns the size of the storage space currently allocated for the Vector.
			size_type capacity() const noexcept;
			// Returns the number of elements in the Vector.
			size_type size() const noexcept;
			// Returns the maximum number of elements that the Vector can hold.
			size_type max_size() const noexcept;
			// Resizes the container so that it contains p_size elements.
			void resize(const size_type& p_size, const value_type& p_value = value_type());
			// Allocates new space and copy elements to new space.
			void reserve(const size_type& p_capacity);
			// Requests the container to reduce its capacity to fit its size.
			void shrink_to_fit();
			// Increase Vector size by one, initialize new element with p_value.
			void push_back(const_reference p_value = value_type());
			void push_back(value_type&& p_value);
			// Removes the last element in the vector, effectively reducing the container size by one.
			void pop_back();
			iterator insert(const_iterator p_position, const_reference p_value);
			// Inserts p_size elements and init it with value p_value start from p_position.
			iterator insert(const_iterator p_position, size_type p_size, const_reference p_value);
			// Copies of the elements in the range [first,last) are inserted at position (in the same order).
			template <class IIterator>
			iterator insert(const_iterator p_position, IIterator p_first, IIterator p_last);
			iterator insert(const_iterator p_position, value_type&& p_value);
			iterator insert(const_iterator p_position, std::initializer_list<value_type> p_list);
			// Removes from the vector a single element (position).
			// This effectively reduces the container size by the number of elements removed, which are destroyed.
			iterator erase(const_iterator p_position);
			// Removes from the vector a range of elements ([first,last)).
			// This effectively reduces the container size by the number of elements removed, which are destroyed.    
			iterator erase(const_iterator p_first, const_iterator p_last);
			// Exchanges the content of the container by the content of p_other,
			// which is another vector object of the same type. Sizes may differ.
			void swap(Vector& p_other);
			// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
			void clear() noexcept;
			// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			template <typename BIterator>
			void assign(BIterator p_first, BIterator p_last);
			void assign(size_type p_size, const value_type& p_value = value_type());
			void assign(std::initializer_list<value_type> p_list);
		private:
			allocator_type m_allocator;
			size_type m_capacity;
			size_type m_size;
			pointer m_elements;
		};
	}
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::iterator dsaa::array::Vector<Elem, Alloc>::begin() noexcept
{
	return m_elements ? iterator(&m_elements[0]) : iterator(nullptr);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_iterator dsaa::array::Vector<Elem, Alloc>::begin() const noexcept
{
	return m_elements ? const_iterator(&m_elements[0]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::iterator dsaa::array::Vector<Elem, Alloc>::end() noexcept
{
	return m_elements ? iterator(&m_elements[size()]) : iterator(nullptr);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_iterator dsaa::array::Vector<Elem, Alloc>::end() const noexcept
{
	return m_elements ? const_iterator(&m_elements[size()]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::reverse_iterator dsaa::array::Vector<Elem, Alloc>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reverse_iterator dsaa::array::Vector<Elem, Alloc>::rbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::reverse_iterator dsaa::array::Vector<Elem, Alloc>::rend() noexcept
{
	return reverse_iterator(begin());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reverse_iterator dsaa::array::Vector<Elem, Alloc>::rend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_iterator dsaa::array::Vector<Elem, Alloc>::cbegin() const noexcept
{
	return m_elements ? const_iterator(&m_elements[0]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_iterator dsaa::array::Vector<Elem, Alloc>::cend() const noexcept
{
	return m_elements ? const_iterator(&m_elements[size()]) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reverse_iterator dsaa::array::Vector<Elem, Alloc>::crbegin() const noexcept
{
	return const_reverse_iterator(end());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reverse_iterator dsaa::array::Vector<Elem, Alloc>::crend() const noexcept
{
	return const_reverse_iterator(begin());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(const allocator_type& p_allocator)
	: m_allocator{ p_allocator }, m_capacity{ 0 }, m_size{ 0 }, m_elements{ nullptr } {}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(const size_type& p_size, const allocator_type& p_allocator)
	: m_allocator{ p_allocator }, m_capacity{ p_size }, m_size{ p_size }, m_elements{ nullptr }
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, i, value_type());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(const size_type& p_size, const_reference p_value, const allocator_type& p_allocator)
	: m_allocator{ p_allocator }, m_capacity{ p_size }, m_size{ p_size }, m_elements{ nullptr }
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());

	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, i, p_value);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(const Vector& p_other)
	:m_allocator{ std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator) },
	m_capacity{ p_other.size() }, m_size{ p_other.size() }, m_elements{ nullptr }
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	pointer temp_p{ m_elements };
	for (const_iterator i{ p_other.begin() }; i != p_other.end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(const Vector& p_other, const allocator_type& p_allocator)
	:m_allocator{ p_allocator }, m_capacity{ p_other.size() }, m_size{ p_other.size() }, m_elements{ nullptr }
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	pointer temp_p{ m_elements };
	for (const_iterator i{ p_other.begin() }; i != p_other.end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(Vector&& p_other)
	: m_capacity{ p_other.capacity() }, m_size{ p_other.size() }, m_elements{ p_other.m_elements }
{
	m_allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator);

	p_other.m_allocator = allocator_type();
	p_other.m_capacity = 0;
	p_other.m_size = 0;
	p_other.m_elements = nullptr;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(Vector&& p_other, const allocator_type& p_allocator)
	:m_allocator{ p_allocator }, m_capacity{ p_other.capacity() }, m_size{ p_other.size() }, m_elements{ p_other.m_elements }
{
	p_other.m_allocator = allocator_type();
	p_other.m_capacity = 0;
	p_other.m_size = 0;
	p_other.m_elements = nullptr;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>& dsaa::array::Vector<Elem, Alloc>::operator=(const Vector& p_other)
{
	// Avoid self-reference.
	if (this == &p_other)
		return *this;

	// No need to allocate new space if we already have enough capacity.
	if (p_other.size() <= capacity())
	{
		// Destroy old elements.
		for (iterator i{ begin() }; i != end(); ++i)
			std::allocator_traits<allocator_type>::destroy(m_allocator, i);
		// Copy.
		pointer temp_p{ m_elements };
		for (const_iterator i{ p_other.begin() }; i != p_other.end(); ++i, ++temp_p)
			std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);

		m_size = p_other.size();
		return *this;
	}

	// Quarantees elements are copies and no error happens before delete old elements.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_other.size());
	pointer temp_p = elements;
	for (const_iterator i{ p_other.begin() }; i != p_other.end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
	// Destroy old elements.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());
	m_capacity = m_size = p_other.size();
	m_elements = elements;
	return *this;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>& dsaa::array::Vector<Elem, Alloc>::operator=(Vector&& p_other)
{
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(p_other.m_allocator);
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
dsaa::array::Vector<Elem, Alloc>& dsaa::array::Vector<Elem, Alloc>::operator=(std::initializer_list<value_type> p_elements)
{
	// Quarantees elements are copies and no error happens before delete old elements.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_elements.size());
	pointer temp_p = elements;
	for (auto i{ p_elements.begin() }; i != p_elements.end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);

	// Destroy old elements.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = m_size = p_elements.size();
	m_elements = elements;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::Vector(std::initializer_list<value_type> p_list, const allocator_type& p_allocator)
	: m_allocator{ p_allocator }, m_capacity{ p_list.size() }, m_size{ p_list.size() }, m_elements{ nullptr }
{
	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	pointer temp_p = m_elements;
	for (auto i{ p_list.begin() }; i != p_list.end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
}

template <typename Elem, typename Alloc>
template<typename IIterator>
dsaa::array::Vector<Elem, Alloc>::Vector(IIterator p_first, IIterator p_last, const allocator_type& p_allocator)
	:m_allocator{ p_allocator }, m_capacity{ 0 }, m_size{ 0 }, m_elements{ nullptr }
{
	resize(10);
	for (size_type index{ 0 }, count{ 0 }; p_first != p_last; ++p_first, ++index, ++count)
	{
		if (capacity() == count)
			resize(size() * 2);

		std::allocator_traits<allocator_type>::construct(m_allocator, &m_elements[index], *p_first);
	}
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::~Vector()
{
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);

	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::reference dsaa::array::Vector<Elem, Alloc>::operator[](size_type p_index)
{
	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reference dsaa::array::Vector<Elem, Alloc>::operator[](size_type p_index) const
{
	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::reference dsaa::array::Vector<Elem, Alloc>::at(const size_type& p_index)
{
	if (p_index < 0 || size() <= p_index)
		throw std::out_of_range("p_index out of range exception.\n;");

	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reference dsaa::array::Vector<Elem, Alloc>::at(const size_type& p_index) const
{
	if (p_index < 0 || size() <= p_index)
		throw std::out_of_range("p_index out of range exception.\n");

	return m_elements[p_index];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::reference dsaa::array::Vector<Elem, Alloc>::front()
{
	return m_elements[0];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reference dsaa::array::Vector<Elem, Alloc>::front() const
{
	return m_elements[0];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::reference dsaa::array::Vector<Elem, Alloc>::back()
{
	return m_elements[size() - 1];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_reference dsaa::array::Vector<Elem, Alloc>::back() const
{
	return m_elements[size() - 1];
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::pointer dsaa::array::Vector<Elem, Alloc>::data() noexcept
{
	return m_elements;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::const_pointer dsaa::array::Vector<Elem, Alloc>::data() const noexcept
{
	return m_elements;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::allocator_type dsaa::array::Vector<Elem, Alloc>::get_allocator() const noexcept
{
	return m_allocator;
}

template <typename Elem, typename Alloc>
bool dsaa::array::Vector<Elem, Alloc>::empty() const noexcept
{
	return begin() == end();
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::size_type dsaa::array::Vector<Elem, Alloc>::capacity() const noexcept
{
	return m_capacity;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::size_type dsaa::array::Vector<Elem, Alloc>::size() const noexcept
{
	return m_size;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::size_type dsaa::array::Vector<Elem, Alloc>::max_size() const noexcept
{
	return std::numeric_limits<value_type>::max() / sizeof(value_type);
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::resize(const size_type& p_size, const value_type& p_value)
{
	reserve(p_size);

	if (size() <= p_size)
	{
		iterator begin(iterator(size())), end(iterator(p_size));
		for (iterator i(begin); i != end; ++i)
			std::iterator_traits<allocator_type>::construct(m_allocator, i, p_value);
	}
	else
	{
		iterator begin(iterator(p_size)), end(iterator(size()));
		for (iterator i(begin); i != end; ++i)
			std::iterator_traits<allocator_type>::destroy(m_allocator, i);
	}

	m_size = p_size;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::reserve(const size_type& p_capacity)
{
	// Never decrease allocation.
	if (p_capacity <= m_capacity)
		return;

	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_capacity);
	// Copy old element to new place.
	pointer temp_p{ elements };
	for (const_iterator i{ begin() }; i != end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
	// Clean up old allocated space.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = p_capacity;
	m_elements = elements;
}

// Requests the container to reduce its capacity to fit its size.
template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::shrink_to_fit()
{
	if (size() == capacity())
		return;
	// Allocate new space.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, size());
	// Copy old element to new place.
	pointer temp_p{ elements };
	for (const_iterator i{ begin() }; i != end(); ++i, ++temp_p)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
	// Clean up old allocated space.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = size();
	m_elements = elements;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::push_back(const_reference p_value)
{
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	std::allocator_traits<allocator_type>::construct(m_allocator, end(), p_value);
	++m_size;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::push_back(value_type&& p_value)
{
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.
	*end() = p_value;
	p_value = value_type();
	++m_size;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::pop_back()
{
	std::allocator_traits<allocator_type>::destroy(m_allocator, end());
	--m_size;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::iterator dsaa::array::Vector<Elem, Alloc>::insert(const_iterator p_position, const_reference p_value)
{
	size_t index{ p_position - begin() };
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size()); // Make sure we have enough space.

	// First copy last element into uninitialized space.
	std::allocator_traits<allocator_type>::construct(m_allocator, end(), back());
	++m_size;

	iterator pp = begin() + index; // The place to put value.
	for (iterator pos{ end() - 1 }; pos != pp; --pos)
		*pos = *(pos - 1); // Copy element one position to the right.

	*pp = p_value; // Insert value;

	return pp;
}

template <typename Elem, typename Alloc>
dsaa::array::Vector<Elem, Alloc>::iterator dsaa::array::Vector<Elem, Alloc>::erase(const_iterator p_position)
{
	if (p_position == end())
		return p_position;

	for (auto pos{ p_position + 1 }; pos != end(); ++pos)
	{
		*(pos - 1) = *pos; // Copy element "one position to the left".
	}

	pop_back();

	return p_position;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::clear() noexcept
{
	// Clean up all elements.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);

	m_size = 0;
}

// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
template <typename Elem, typename Alloc>
template <typename BIterator>
void dsaa::array::Vector<Elem, Alloc>::assign(BIterator p_first, BIterator p_last)
{
	if (capacity() < (p_last - p_first))
		reserve(p_last - p_first);

	// Clean up old allocated space.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);

	pointer temp_p{ m_elements };
	for (BIterator i{ p_first }; i != p_last; ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, temp_p, *i);
	m_size = p_last - p_first;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::assign(size_type p_size, const value_type& p_value)
{
	// Allocate new space.
	pointer elements = std::allocator_traits<allocator_type>::allocate(m_allocator, p_size);
	for (size_type i = 0; i < p_size; ++i)
		std::allocator_traits<allocator_type>::construct(m_allocator, &elements[i], p_value);

	// Clean up old allocated space.
	for (iterator i{ begin() }; i != end(); ++i)
		std::allocator_traits<allocator_type>::destroy(m_allocator, i);
	std::allocator_traits<allocator_type>::deallocate(m_allocator, m_elements, capacity());

	m_capacity = m_size = p_size;
	m_elements = elements;
}

template <typename Elem, typename Alloc>
void dsaa::array::Vector<Elem, Alloc>::assign(std::initializer_list<value_type> p_list)
{
	m_allocator = allocator_type();
	m_capacity = m_size = p_list.size();

	m_elements = std::allocator_traits<allocator_type>::allocate(m_allocator, capacity());
	pointer temp_p = m_elements;
	for (auto i{ p_list.begin() }; i != p_list.end(); ++i, ++temp_p)
		*temp_p = *i;
}
#endif