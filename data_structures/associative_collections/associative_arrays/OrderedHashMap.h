#ifndef ORDERED_HASH_MAP_H
#define ORDERED_HASH_MAP_H

#include <memory>
#include <functional>
#include <iterator>

#include "dsaaTypedefs.h"

namespace dsaa
{
    template <typename Key,                                                // OrderedHashMap::key_type
              typename Value,                                              // OrderedHashMap::mapped_type
              typename Compare = std::less<Key>,                           // OrderedHashMap::key_compare
              typename Alloc = std::allocator<std::pair<const Key, Value>> // OrderedHashMap::allocator_type
              >
    class OrderedHashMap
    {
        class ValueCompare;
        class ConstIterator;
        class Iterator;

        using key_type = Key;                                                       // The first template parameter (Key).
        using mapped_type = Value;                                                  // The second template parameter (Value).
        using value_type = std::pair<const key_type, mapped_type>;                  // std::pair<const key_type, mapped_type>.
        using key_compare = Compare;                                                // The third template parameter (Compare).
        using value_compare = ValueCompare;                                         // Nested function class to compare elements.
        using allocator_type = Alloc;                                               // The fourth template parameter (Alloc).
        using reference = value_type &;                                             // value_type&.
        using const_reference = const value_type &;                                 // const value_type&.
        using pointer = std::allocator_traits<allocator_type>::pointer;             // std::allocator_traits<allocator_type>::pointer.
        using const_pointer = std::allocator_traits<allocator_type>::const_pointer; // std::allocator_traits<allocator_type>::const_pointer.
        using iterator = Iterator;                                                  // A bidirectional iterator to value_type.
        using const_iterator = ConstIterator;                                       // A bidirectional iterator to const value_type.
        using reverse_iterator = std::reverse_iterator<iterator>;                   // std::reverse_iterator<iterator>.
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;       // std::reverse_iterator<const_iterator>.
        using difference_type = iterator_traits<iterator>::difference_type;         // A signed integral type, identical to: iterator_traits<iterator>::difference_type.
        using size_type = size_t;                                                   // an unsigned integral type that can represent any non-negative value of difference_type.

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
        CONSTEXPR OrderedHashMap(const allocator_type &p_allocator = allocator_type()) noexcept;
        // Creates a container's p_size elements with default value.
        CONSTEXPR explicit OrderedHashMap(const key_compare &p_compare, const allocator_type &p_allocator = allocator_type());
        // Creates a container and init its elements by content of IIterator in range (first, last].
        template <typename IIterator>
        CONSTEXPR OrderedHashMap(const IIterator &p_first, const IIterator &p_last, const key_compare &p_compare, const allocator_type &p_allocator = allocator_type());
        template <typename IIterator>
        CONSTEXPR OrderedHashMap(const IIterator &p_first, const IIterator &p_last, const allocator_type &p_allocator = allocator_type());
        // Creates a container's size equal to p_elements's size and init its elements by p_elements's element.
        CONSTEXPR OrderedHashMap(const std::initializer_list<value_type> &p_elements, const key_compare &p_compare, const allocator_type &p_allocator = allocator_type());
        CONSTEXPR OrderedHashMap(const std::initializer_list<value_type> &p_elements, const allocator_type &p_allocator = allocator_type());
        // Creates a container and copy all emements from p_other.
        CONSTEXPR OrderedHashMap(const OrderedHashMap &p_other);
        // Creates a container and copy all emements from p_other.
        CONSTEXPR OrderedHashMap(const OrderedHashMap &p_other, const allocator_type &p_allocator);
        // Moves all elements from p_other into this.
        CONSTEXPR OrderedHashMap(OrderedHashMap &&p_other) noexcept;
        // Moves all elements from p_other into this.
        CONSTEXPR OrderedHashMap(OrderedHashMap &&p_other, const allocator_type &p_allocator) noexcept;
        // Destroys old elements and copy all emements from p_other into this.
        CONSTEXPR OrderedHashMap &operator=(const OrderedHashMap &p_other);
        // Destroys old elements and moves all emements from p_other into this.
        CONSTEXPR OrderedHashMap &operator=(OrderedHashMap &&p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<allocator_type>::is_always_equal::value);
        // Destroys old elements and copy all elements from p_elements.
        CONSTEXPR OrderedHashMap &operator=(const std::initializer_list<value_type> &p_elements);
        // Destroys all elements and clean used space.
        virtual ~OrderedHashMap();

        // Returns a reference to the element at position p_index in the container.
        NODISCARD CONSTEXPR INLINE mapped_type &operator[](const key_type &p_key) NOEXCEPT;
        NODISCARD CONSTEXPR INLINE const mapped_type &operator[](const key_type &p_key) const NOEXCEPT;
        // Bounds checking that returns a reference to the element at position p_index in the container.
        NODISCARD CONSTEXPR INLINE mapped_type &at(const key_type &p_key);
        NODISCARD CONSTEXPR INLINE const mapped_type &at(const key_type &p_key) const;
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
        NODISCARD CONSTEXPR INLINE iterator get_iterator(const key_type &p_key) NOEXCEPT;
        CONSTEXPR INLINE key_compare key_comp() const;
        CONSTEXPR INLINE value_compare value_comp() const;
        NODISCARD CONSTEXPR iterator find(const key_type &p_key);
        NODISCARD CONSTEXPR const_iterator find(const key_type &p_key) const;
        NODISCARD CONSTEXPR size_type count(const key_type &p_key) const;
        NODISCARD CONSTEXPR iterator lower_bound(const key_type &p_key);
        NODISCARD CONSTEXPR const_iterator lower_bound(const key_type &p_key) const;
        NODISCARD CONSTEXPR iterator upper_bound(const key_type &p_key);
        NODISCARD CONSTEXPR const_iterator upper_bound(const key_type &p_key) const;
        NODISCARD CONSTEXPR std::pair<const_iterator, const_iterator> equal_range(const key_type &p_key) const;
        NODISCARD CONSTEXPR std::pair<iterator, iterator> equal_range(const key_type &p_key);

        // Increase Map size by one, initialize new element with p_value.
        CONSTEXPR std::pair<iterator, bool> insert(const_reference p_value);
        CONSTEXPR std::pair<iterator, bool> insert(value_type &&p_value);
        CONSTEXPR std::pair<iterator, bool> insert(const std::initializer_list<value_type> &p_elements);
        template <class IIterator>
        CONSTEXPR std::pair<iterator, bool> insert(const IIterator &p_first, const IIterator &p_last);
        template <class... Args>
        CONSTEXPR std::pair<iterator, bool> emplace(Args &&...p_args);

        CONSTEXPR iterator insert(const const_iterator &p_position, const_reference p_value);
        CONSTEXPR iterator insert(const const_iterator &p_position, value_type &&p_value);
        CONSTEXPR iterator insert(const const_iterator &p_position, const std::initializer_list<value_type> &p_elements);
        template <class IIterator>
        CONSTEXPR iterator insert(const const_iterator &p_position, const IIterator &p_first, const IIterator &p_last);
        template <class... Args>
        CONSTEXPR iterator emplace_hint(const const_iterator &p_position, Args &&...p_args);

        CONSTEXPR void erase(const const_iterator &p_position) NOEXCEPT;
        CONSTEXPR size_type erase(const key_type &p_key);
        CONSTEXPR void erase(iterator p_first, iterator p_last);

        CONSTEXPR INLINE void clear() noexcept;
        CONSTEXPR void swap(OrderedHashMap &p_other) noexcept(std::allocator_traits<allocator_type>::propagate_on_container_swap::value || std::allocator_traits<allocator_type>::is_always_equal::value);
    };
}

template <class Key, class Value, class Compare, class Alloc>
class dsaa::OrderedHashMap<Key, Value, Compare, Alloc>::ValueCompare
{ // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
    friend class OrderedHashMap;

protected:
    Compare comp;
    ValueCompare(Compare c) : comp(c) {} // constructed with OrderedHashMap's comparison object
public:
    using result_type = bool;
    using first_argument_type = value_type;
    using second_argument_type = value_type;

    bool operator()(const value_type &x, const value_type &y) const
    {
        return comp(x.first, y.first);
    }
};
#endif //!ORDERED_HASH_MAP_H