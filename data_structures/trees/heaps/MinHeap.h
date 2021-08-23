/*
Class: MinHeap.
Purpose: Implement min heap data structure, this class fully support min priority queue.
        - First parameter Elem will be the element in heap, it must be an Element type.
        - Second parameter Alloc is the allocator type use to allocate element in memmory.
        - Third parameter Compare define how min heap mantains its property,
        - it must be std::less_equal<Elem> or std::less<Elem>, other comparer is undefined behavious.
*/

#ifndef DSAA_MIN_HEAP_H
#define DSAA_MIN_HEAP_H

#include "DynamicArray.h"
#include "dsaaTypedefs.h"

namespace dsaa
{
    template <typename Elem, typename Alloc = std::allocator<Elem>, typename Compare = std::less_equal<Elem>>
    class MinHeap
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
        using iterator = Iterator;            // A random access iterator to value_type.
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using difference_type = typename std::iterator_traits<iterator>::difference_type; // usually the same as ptrdiff_t.
        using size_type = size_t;

        using compare = Compare;

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
        CONSTEXPR MinHeap(const allocator_type &p_allocator = allocator_type()) noexcept;
        // Creates a container's p_size elements with default value.
        CONSTEXPR explicit MinHeap(const size_type &p_size, const allocator_type &p_allocator = allocator_type());
        // Creates a container's p_size elements and init its element by p_value.
        CONSTEXPR MinHeap(const size_type &p_size, const_reference p_value, const allocator_type &p_allocator = allocator_type());
        // Creates a container's size equal to p_elements's size and init its elements using p_elements's element.
        CONSTEXPR MinHeap(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type());
        // Creates a container and init its elements using content of IIterator in range (first, last].
        template <typename IIterator>
        CONSTEXPR MinHeap(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator = allocator_type());
        // Creates a container and copy all emements from p_other.
        CONSTEXPR MinHeap(const MinHeap &p_other);
        // Creates a container and copy all emements from p_other.
        CONSTEXPR MinHeap(const MinHeap &p_other, const allocator_type &p_allocator);
        // Moves all elements from p_other into this.
        CONSTEXPR MinHeap(MinHeap &&p_other) noexcept;
        // Moves all elements from p_other into this.
        CONSTEXPR MinHeap(MinHeap &&p_other, const allocator_type &p_allocator) noexcept;
        // Destroys old elements and copy all emements from p_other into this.
        CONSTEXPR MinHeap &operator=(const MinHeap &p_other);
        // Destroys old elements and moves all emements from p_other into this.
        CONSTEXPR MinHeap &operator=(MinHeap &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value);
        // Destroys old elements and copy all elements from p_elements.
        CONSTEXPR MinHeap &operator=(const std::initializer_list<value_type> &p_elements);
        // Destroys all elements and clean/free used space.
        virtual ~MinHeap();

        // Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
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
        // Return underlying data container.
        NODISCARD CONSTEXPR INLINE dsaa::DynamicArray<value_type> &data() noexcept;
        NODISCARD CONSTEXPR INLINE dsaa::DynamicArray<value_type> const &data() const noexcept;

        // Test whether container is empty.
        NODISCARD CONSTEXPR INLINE bool empty() const noexcept;
        // Returns size that heap can hold.
        NODISCARD CONSTEXPR INLINE size_type size() const noexcept;
        // Returns current heap size.
        NODISCARD CONSTEXPR INLINE size_type heap_size() const noexcept;
        // Is given index a leaf node, which have no children.
        NODISCARD CONSTEXPR INLINE bool is_leaf(size_type p_index) const noexcept;
        // Gets the corresponding index for given iterator.
        NODISCARD CONSTEXPR INLINE size_type get_index(const const_iterator &p_position) NOEXCEPT;
        // Gets the corresponding iterator for given index.
        NODISCARD CONSTEXPR INLINE iterator get_iterator(const size_type &p_index) NOEXCEPT;
        // Shrink size the container so that it contains p_size elements.
        CONSTEXPR void shrink_size(const size_type &p_size);

        // get parent index of the given index.
        NODISCARD CONSTEXPR INLINE size_type parent(size_type p_index) const NOEXCEPT;
        // get left child index of the given index.
        NODISCARD CONSTEXPR INLINE size_type left_child(size_type p_index) const NOEXCEPT;
        // get right child index of the given index.
        NODISCARD CONSTEXPR INLINE size_type right_child(size_type p_index) const NOEXCEPT;
        // Check for given index satisfy heap property define by Compare.
        NODISCARD CONSTEXPR INLINE bool min_heap_property(size_type p_index) const NOEXCEPT;
        // Key function to maintaining min heap properties define by Compare.
        CONSTEXPR void recursive_min_heapify(size_type p_parent_index) NOEXCEPT;
        CONSTEXPR void iterative_min_heapify(size_type p_parent_index) NOEXCEPT;
        // Build a min heap from an input array.
        CONSTEXPR void build_min_heap() NOEXCEPT;
        NODISCARD CONSTEXPR value_type extract_min() NOEXCEPT;
        NODISCARD CONSTEXPR INLINE value_type get_min() NOEXCEPT;

        CONSTEXPR iterator insert(const_reference p_value) NOEXCEPT;
        CONSTEXPR iterator insert(value_type &&p_value) NOEXCEPT;
        CONSTEXPR void insert(const size_type &p_size, const_reference p_value) NOEXCEPT;
        CONSTEXPR void insert(const std::initializer_list<value_type> &p_elements) NOEXCEPT;
        template <class IIterator>
        CONSTEXPR void insert(const IIterator &p_first, const IIterator &p_last) NOEXCEPT;
        template <class... Args>
        CONSTEXPR iterator emplace(Args &&...p_args) NOEXCEPT;

        CONSTEXPR iterator decrease_key(int64_t p_index, const_reference p_value) NOEXCEPT;
        CONSTEXPR iterator decrease_key(int64_t p_index, value_type &&p_value) NOEXCEPT;
        template <class... Args>
        CONSTEXPR iterator decrease_key(int64_t p_index, Args &&...p_args) NOEXCEPT;

        CONSTEXPR void erase_at(const const_iterator &p_position) NOEXCEPT;
        // Destroy element in range (first,last] and reduce size of container.
        CONSTEXPR void erase(const const_iterator &p_first, const const_iterator &p_last) NOEXCEPT;
        // Destroys all elements from the container, leaving the size 0.
        CONSTEXPR INLINE void clear() noexcept;

    protected:
        dsaa::DynamicArray<Elem, Alloc> m_data;
        Compare m_comparer;
    };
}

template <typename Elem, typename Alloc, typename Compare>
class dsaa::MinHeap<Elem, Alloc, Compare>::ConstIterator
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
        operator++();             // prefix increment
        return old;               // return old value
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
        int64_t result(m_pointer - p_rhs.m_pointer);
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

    NODISCARD CONSTEXPR INLINE reference operator*() const { return *m_pointer; }
    NODISCARD CONSTEXPR INLINE reference operator[](const int64_t &p_index) const { return m_pointer[p_index]; }
    NODISCARD CONSTEXPR INLINE const_pointer content() const noexcept { return m_pointer; }

protected:
    pointer m_pointer;
};

template <typename Elem, typename Alloc, typename Compare>
class dsaa::MinHeap<Elem, Alloc, Compare>::Iterator : public dsaa::MinHeap<Elem, Alloc, Compare>::ConstIterator
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
        operator++();        // prefix increment
        return old;          // return old value
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
        int64_t result(content() - p_rhs.content());
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

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::begin() noexcept
{
    return heap_size() ? iterator(m_data.begin().content()) : iterator(nullptr);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_iterator dsaa::MinHeap<Elem, Alloc, Compare>::begin() const noexcept
{
    return heap_size() ? const_iterator(m_data.begin().content()) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_iterator dsaa::MinHeap<Elem, Alloc, Compare>::cbegin() const noexcept
{
    return heap_size() ? const_iterator(m_data.begin().content()) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::end() noexcept
{
    return heap_size() ? iterator(m_data.end().content()) : iterator(nullptr);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_iterator dsaa::MinHeap<Elem, Alloc, Compare>::end() const noexcept
{
    return heap_size() ? const_iterator(m_data.end().content()) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_iterator dsaa::MinHeap<Elem, Alloc, Compare>::cend() const noexcept
{
    return heap_size() ? const_iterator(m_data.end().content()) : const_iterator(nullptr);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::reverse_iterator dsaa::MinHeap<Elem, Alloc, Compare>::rbegin() noexcept
{
    return reverse_iterator(end());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_reverse_iterator dsaa::MinHeap<Elem, Alloc, Compare>::rbegin() const noexcept
{
    return const_reverse_iterator(end());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_reverse_iterator dsaa::MinHeap<Elem, Alloc, Compare>::crbegin() const noexcept
{
    return const_reverse_iterator(end());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::reverse_iterator dsaa::MinHeap<Elem, Alloc, Compare>::rend() noexcept
{
    return reverse_iterator(begin());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_reverse_iterator dsaa::MinHeap<Elem, Alloc, Compare>::rend() const noexcept
{
    return const_reverse_iterator(begin());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_reverse_iterator dsaa::MinHeap<Elem, Alloc, Compare>::crend() const noexcept
{
    return const_reverse_iterator(begin());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const allocator_type &p_allocator) noexcept
    : m_data(p_allocator), m_comparer() {}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const size_type &p_size, const allocator_type &p_allocator)
    : m_data(p_size, p_allocator), m_comparer()
{
#ifdef PARAM_CHECK
    if (std::is_same<std::less<value_type>, Compare>::value)
        throw std::runtime_error("Priority queue can only accept element has difference priority, because Compare is std::less type.\n");
#endif
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const size_type &p_size, const_reference p_value, const allocator_type &p_allocator)
    : m_data(p_size, p_value, p_allocator), m_comparer()
{
#ifdef PARAM_CHECK
    if (std::is_same<std::less<value_type>, Compare>::value)
        throw std::runtime_error("Priority queue can only accept element has difference priority, because Compare is std::less type.\n");
#endif
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator)
    : m_data(p_elements, p_allocator), m_comparer() { build_min_heap(); }

template <typename Elem, typename Alloc, typename Compare>
template <typename IIterator>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator)
    : m_data(p_first, p_last, p_allocator), m_comparer() { build_min_heap(); }

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const MinHeap &p_other)
    : m_data(p_other.m_data), m_comparer() {}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(const MinHeap &p_other, const allocator_type &p_allocator)
    : m_data(p_other.m_data, p_allocator), m_comparer() {}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(MinHeap &&p_other) noexcept
    : m_data(std::move(p_other.m_data)), m_comparer() {}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare>::MinHeap(MinHeap &&p_other, const allocator_type &p_allocator) noexcept
    : m_data(std::move(p_other.m_data), p_allocator), m_comparer() {}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare> &dsaa::MinHeap<Elem, Alloc, Compare>::operator=(const MinHeap &p_other)
{
    // Avoid self-reference.
    if (this == &p_other)
        return *this;

    m_data = p_other.m_data;

    return *this;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare> &dsaa::MinHeap<Elem, Alloc, Compare>::operator=(MinHeap &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value)
{
    m_data = std::move(p_other.m_data);

    return *this;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::MinHeap<Elem, Alloc, Compare> &dsaa::MinHeap<Elem, Alloc, Compare>::operator=(const std::initializer_list<value_type> &p_elements)
{
    m_data = p_elements;
    build_min_heap();

    return *this;
}

template <typename Elem, typename Alloc, typename Compare>
dsaa::MinHeap<Elem, Alloc, Compare>::~MinHeap()
{
}

// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
template <typename Elem, typename Alloc, typename Compare>
template <typename IIterator>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::assign(const IIterator &p_first, const IIterator &p_last)
{
    m_data.assign(p_first, p_last);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::assign(const size_type &p_size, const value_type &p_value)
{
#ifdef PARAM_CHECK
    if (std::is_same<std::less<value_type>, Compare>::value)
        throw std::runtime_error("Priority queue can only accept element has difference priority, because Compare is std::less type.\n");
#endif

    m_data.assign(p_size, p_value);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::assign(const std::initializer_list<value_type> &p_elements)
{
    m_data.assign(p_elements);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::reference dsaa::MinHeap<Elem, Alloc, Compare>::operator[](const size_type &p_index) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (heap_size() <= p_index)
        throw std::out_of_range("p_index out of range exception.\n;");
#endif

    return m_data[p_index];
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_reference dsaa::MinHeap<Elem, Alloc, Compare>::operator[](const size_type &p_index) const NOEXCEPT
{
#ifdef PARAM_CHECK
    if (heap_size() <= p_index)
        throw std::out_of_range("p_index out of range exception.\n;");
#endif

    return m_data[p_index];
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::reference dsaa::MinHeap<Elem, Alloc, Compare>::at(const size_type &p_index)
{
    if (heap_size() <= p_index)
        throw std::out_of_range("p_index out of range exception.\n;");

    return m_data[p_index];
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::const_reference dsaa::MinHeap<Elem, Alloc, Compare>::at(const size_type &p_index) const
{
    if (heap_size() <= p_index)
        throw std::out_of_range("p_index out of range exception.\n;");

    return m_data[p_index];
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::DynamicArray<Elem> &dsaa::MinHeap<Elem, Alloc, Compare>::data() noexcept
{
    return m_data;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR dsaa::DynamicArray<Elem> const &dsaa::MinHeap<Elem, Alloc, Compare>::data() const noexcept
{
    return m_data;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR bool dsaa::MinHeap<Elem, Alloc, Compare>::empty() const noexcept
{
    return m_data.empty();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::size_type dsaa::MinHeap<Elem, Alloc, Compare>::size() const noexcept
{
    return m_data.capacity();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::size_type dsaa::MinHeap<Elem, Alloc, Compare>::heap_size() const noexcept
{
    return m_data.size();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR bool dsaa::MinHeap<Elem, Alloc, Compare>::is_leaf(size_type p_index) const noexcept
{
    return heap_size() / 2 <= p_index;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::size_type dsaa::MinHeap<Elem, Alloc, Compare>::get_index(const const_iterator &p_position) NOEXCEPT
{
    return m_data.get_index(typename dsaa::DynamicArray<Elem, Alloc>::const_iterator(p_position.content()));
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::get_iterator(const size_type &p_index) NOEXCEPT
{
    return iterator(m_data.get_iterator(p_index).content());
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::shrink_size(const size_type &p_size)
{
#ifdef PARAM_CHECK
    if (heap_size() <= p_size)
        throw std::runtime_error("MinHeap only allow shrink size to smaller size.\n");
#endif

    m_data.resize(p_size);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::size_type dsaa::MinHeap<Elem, Alloc, Compare>::parent(size_type p_index) const NOEXCEPT
{
#ifdef PARAM_CHECK
    if (0 == p_index)
        throw std::runtime_error("Given index already is root node, and root node have no parent.\n");
#endif

    return (p_index - 1) / 2;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::size_type dsaa::MinHeap<Elem, Alloc, Compare>::left_child(size_type p_index) const NOEXCEPT
{
#ifdef PARAM_CHECK
    if (is_leaf(p_index))
        throw std::runtime_error("Given index is a leaf node and there is no left_child.\n");
#endif

    return 2 * p_index + 1;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::size_type dsaa::MinHeap<Elem, Alloc, Compare>::right_child(size_type p_index) const NOEXCEPT
{
#ifdef PARAM_CHECK
    if (is_leaf(p_index))
        throw std::runtime_error("Given index is a leaf node and there is no right_child.\n");
#endif

    return 2 * p_index + 2;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR bool dsaa::MinHeap<Elem, Alloc, Compare>::min_heap_property(size_type p_index) const NOEXCEPT
{
#ifdef PARAM_CHECK
    if (heap_size() <= p_index)
        throw std::out_of_range("index out of range.\n");
#endif

    return 0 == p_index ? true : m_comparer(m_data[parent(p_index)], m_data[p_index]);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::recursive_min_heapify(size_type p_parent_index) NOEXCEPT
{
    if (is_leaf(p_parent_index))
        return;

    size_type left_index(left_child(p_parent_index));
    size_type right_index(right_child(p_parent_index));

    size_type key_index = (left_index < heap_size() && !m_comparer(m_data[p_parent_index], m_data[left_index])) ? left_index : p_parent_index;
    key_index = (right_index < heap_size() && !m_comparer(m_data[key_index], m_data[right_index])) ? right_index : key_index;

    if (key_index != p_parent_index)
    {
        std::swap(m_data[p_parent_index], m_data[key_index]);
        recursive_min_heapify(key_index);
    }
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::iterative_min_heapify(size_type p_parent_index) NOEXCEPT
{
    size_type left_index(0);
    size_type right_index(0);
    size_type key_index(p_parent_index);
    size_type previous_key_index(p_parent_index);
    while (true)
    {
        if (is_leaf(previous_key_index))
            return;

        left_index = left_child(key_index);
        right_index = right_child(key_index);
        key_index = (left_index < heap_size() && !m_comparer(m_data[key_index], m_data[left_index])) ? left_index : key_index;
        key_index = (right_index < heap_size() && !m_comparer(m_data[key_index], m_data[right_index])) ? right_index : key_index;

        if (key_index != previous_key_index)
        {
            std::swap(m_data[previous_key_index], m_data[key_index]);
            previous_key_index = key_index;
        }
        else
            return;
    }
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::build_min_heap() NOEXCEPT
{
    for (int64_t index((size() - 1) / 2); 0 <= index; --index)
    {
        iterative_min_heapify(index);
    }
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::value_type dsaa::MinHeap<Elem, Alloc, Compare>::extract_min() NOEXCEPT
{
#ifdef PARAM_CHECK
    if (0 == heap_size())
        throw std::runtime_error("heap size is zero, there is nothing to extract.\n");
#endif

    value_type result(m_data[0]);
    m_data[0] = m_data[heap_size() - 1];
    m_data.erase_last();
    iterative_min_heapify(0);
    return result;
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::value_type dsaa::MinHeap<Elem, Alloc, Compare>::get_min() NOEXCEPT
{
#ifdef PARAM_CHECK
    if (0 == heap_size())
        throw std::runtime_error("heap size is zero, there is nothing to get.\n");
#endif

    return m_data[0];
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::insert(const_reference p_value) NOEXCEPT
{
    m_data.insert_last(p_value);
    int64_t index(heap_size() - 1);
    while (0 < index && !min_heap_property(index))
    {
        std::swap(m_data[index], m_data[parent(index)]);
        index = parent(index);
    }
    return get_iterator(index);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::insert(value_type &&p_value) NOEXCEPT
{
    m_data.insert_last(std::move(p_value));
    int64_t index(heap_size() - 1);
    while (0 < index && !min_heap_property(index))
    {
        std::swap(m_data[index], m_data[parent(index)]);
        index = parent(index);
    }
    return get_iterator(index);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::insert(const size_type &p_size, const_reference p_value) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (std::is_same<std::less<value_type>, Compare>::value)
        throw std::runtime_error("Priority queue can only accept element has difference priority, because Compare is std::less type.\n");
#endif

    m_data.insert_last(p_size, p_value);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::insert(const std::initializer_list<value_type> &p_elements) NOEXCEPT
{
    m_data.insert_last(p_elements);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
template <class IIterator>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::insert(const IIterator &p_first, const IIterator &p_last) NOEXCEPT
{
    m_data.insert_last(p_first, p_last);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
template <class... Args>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::emplace(Args &&...p_args) NOEXCEPT
{
    m_data.insert_last(p_args...);
    int64_t index(heap_size() - 1);
    while (0 < index && !min_heap_property(index))
    {
        std::swap(m_data[index], m_data[parent(index)]);
        index = parent(index);
    }
    return get_iterator(index);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::decrease_key(int64_t p_index, const_reference p_value) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (!m_comparer(p_value, m_data[p_index]))
        throw std::invalid_argument("new key is greater than current key.\n");
#endif

    m_data[p_index] = p_value;
    while (0 < p_index && !min_heap_property(p_index))
    {
        std::swap(m_data[p_index], m_data[parent(p_index)]);
        p_index = parent(p_index);
    }
    return get_iterator(p_index);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::decrease_key(int64_t p_index, value_type &&p_value) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (!m_comparer(p_value, m_data[p_index]))
        throw std::invalid_argument("new key is greater than current key.\n");
#endif

    m_data[p_index] = std::move(p_value);
    while (0 < p_index && !min_heap_property(p_index))
    {
        std::swap(m_data[p_index], m_data[parent(p_index)]);
        p_index = parent(p_index);
    }
    return get_iterator(p_index);
}

template <typename Elem, typename Alloc, typename Compare>
template <class... Args>
CONSTEXPR typename dsaa::MinHeap<Elem, Alloc, Compare>::iterator dsaa::MinHeap<Elem, Alloc, Compare>::decrease_key(int64_t p_index, Args &&...p_args) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (!m_comparer(p_args..., m_data[p_index]))
        throw std::invalid_argument("new key is greater than current key.\n");
#endif

    m_data[p_index] = std::move(value_type(p_args...));
    while (0 < p_index && !min_heap_property(p_index))
    {
        std::swap(m_data[p_index], m_data[parent(p_index)]);
        p_index = parent(p_index);
    }
    return get_iterator(p_index);
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::erase_at(const const_iterator &p_position) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (p_position < begin())
        throw std::invalid_argument("p_position can not less than begin().\n");
    if (end() <= p_position)
        throw std::invalid_argument("p_position can not greater than iterator(last()).\n");
#endif

    typename dsaa::DynamicArray<Elem, Alloc>::iterator position(const_cast<pointer>(p_position.content()));
    m_data.erase_at(position);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::erase(const const_iterator &p_first, const const_iterator &p_last) NOEXCEPT
{
#ifdef PARAM_CHECK
    if (p_last < p_first)
        throw std::invalid_argument("p_first can not less than p_last.\n");
    if (p_first < begin())
        throw std::invalid_argument("p_first can not less than begin().\n");
    if (end() < p_last)
        throw std::invalid_argument("p_last can not greater than end().\n");
#endif

    typename dsaa::DynamicArray<Elem, Alloc>::iterator first(const_cast<pointer>(p_first.content())), last(const_cast<pointer>(p_last.content()));
    m_data.erase(first, last);
    build_min_heap();
}

template <typename Elem, typename Alloc, typename Compare>
CONSTEXPR void dsaa::MinHeap<Elem, Alloc, Compare>::clear() noexcept
{
    m_data.clear();
}

#endif // !DSAA_MIN_HEAP_H