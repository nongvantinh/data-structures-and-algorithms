#ifndef DSAA_GENERIC_H
#define DSAA_GENERIC_H

#include <functional>
#include <cmath>

#include "Random.h"
#include "BinaryTree.h"

namespace dsaa
{
    template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
    RIterator merge(RIterator p_first, RIterator p_mid, RIterator p_last, Compare p_compare = Compare());

    template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
    RIterator lomuto_partition(RIterator p_first, RIterator p_last, Compare p_compare = Compare());

    template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
    RIterator hoare_partition(RIterator p_first, RIterator p_last, Compare p_compare = Compare());

    template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
    RIterator randomized_lomuto_partition(RIterator p_first, RIterator p_last, Compare p_compare = Compare());

    template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
    RIterator randomized_hoare_partition(RIterator p_first, RIterator p_last, Compare p_compare = Compare());

    bool is_prime(size_t p_number);
}

template <typename RIterator, typename Compare>
RIterator dsaa::merge(RIterator p_first, RIterator p_mid, RIterator p_last, Compare p_compare)
{
    if (p_first == p_last)
        return p_first;
    size_t arr1_size = p_mid - p_first;
    size_t arr2_size = p_last - p_mid;
    std::vector<typename std::iterator_traits<RIterator>::value_type> left(arr1_size);
    std::vector<typename std::iterator_traits<RIterator>::value_type> right(arr2_size);

    for (size_t i(0); i < arr1_size; ++i)
        left[i] = *(p_first + i);

    for (size_t i(0); i < arr2_size; ++i)
        right[i] = *(p_mid + i);

    size_t i(0), m(0);
    for (RIterator k(p_first); k != p_last; ++k)
    {
        if (arr1_size <= i)
        {
            *k = right[m];
            ++m;
        }
        else if (arr2_size <= m)
        {
            *k = left[i];
            ++i;
        }
        else if (p_compare(left[i], right[m]))
        {
            *k = left[i];
            ++i;
        }
        else
        {
            *k = right[m];
            ++m;
        }
    }
    return p_last;
}

template <typename RIterator, typename Compare>
RIterator dsaa::lomuto_partition(RIterator p_first, RIterator p_last, Compare p_compare)
{
    auto pivot = *(p_last - 1);
    RIterator i = p_first;
    bool is_first(true); // To adapt to iterator, in case bound checking of iterator is turned on.

    for (RIterator k(p_first); (p_last - 1) != k; ++k)
    {
        if (p_compare(*k, pivot))
        {
            if (is_first)
                is_first = false;
            else
                ++i;
            std::swap(*i, *k);
        }
    }
    // Special case we never ever do swap.
    if (is_first)
        std::swap(*i, *(p_last - 1));
    else
        std::swap(*++i, *(p_last - 1));

    return i;
}

template <typename RIterator, typename Compare>
RIterator dsaa::hoare_partition(RIterator p_first, RIterator p_last, Compare p_compare)
{
    auto pivot = *p_first;
    RIterator i = p_first;
    bool is_first(true); // To adapt to iterator, in case bound checking of iterator is turned on.
    RIterator k(p_last);

    while (true)
    {
        // Find the element that satisfy the condition to swap.
        do
            --k;
        while (p_compare(pivot, *k));

        // Find the element doesn't satisfy the condition to swap.
        do
        {
            if (is_first)
                is_first = false;
            else
                ++i;
        } while (p_compare(*i, pivot));

        // Return when all element has been put in correct side.
        if (k <= i)
            return k;
        std::swap(*i, *k);
    }
}

template <typename RIterator, typename Compare>
RIterator dsaa::randomized_lomuto_partition(RIterator p_first, RIterator p_last, Compare p_compare)
{
    size_t i(0);
    i = dsaa::random::random_range_int(0, static_cast<int>((p_last - p_first) - 1));
    std::swap(*(p_first + i), *(p_last - 1));
    return dsaa::lomuto_partition(p_first, p_last, p_compare);
}

template <typename RIterator, typename Compare>
RIterator dsaa::randomized_hoare_partition(RIterator p_first, RIterator p_last, Compare p_compare)
{
    size_t i(0);
    i = dsaa::random::random_range_int(0, static_cast<int>((p_last - p_first) - 1));
    std::swap(*p_first, *(p_first + i));
    return dsaa::hoare_partition(p_first, p_last, p_compare);
}

#endif //!DSAA_GENERIC_H
