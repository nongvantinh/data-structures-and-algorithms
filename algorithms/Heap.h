#ifndef DSAA_HEAP_H
#define DSAA_HEAP_H

#include <functional>
#include <memory>
#include <algorithm>
#include <iterator>

namespace dsaa
{
    template <typename RIterator, typename Compare = std::greater_equal<typename std::iterator_traits<RIterator>::value_type>>
    void build_heap(RIterator p_first, RIterator p_last, Compare p_compare = Compare());

    template <typename RIterator, typename Compare = std::greater_equal<typename std::iterator_traits<RIterator>::value_type>>
    bool heap_property(RIterator p_first, RIterator p_last, RIterator p_position, Compare p_compare);

    template <typename RIterator, typename Compare = std::greater_equal<typename std::iterator_traits<RIterator>::value_type>>
    void heapify(RIterator p_first, RIterator p_last, RIterator p_position, Compare p_compare);
}

template <typename RIterator, typename Compare>
void dsaa::build_heap(RIterator p_first, RIterator p_last, Compare p_compare)
{
    if (p_first == p_last)
        return;
    for (auto i(p_first + (p_last - p_first - 1) / 2); p_first <= i; --i)
    {
        dsaa::heapify(p_first, p_last, i, p_compare);
    }
}

template <typename RIterator, typename Compare>
bool dsaa::heap_property(RIterator p_first, RIterator p_last, RIterator p_position, Compare p_compare)
{
    if (p_first + (p_last - p_first) <= p_position)
        throw std::out_of_range("index out of range.\n");

    return p_first == p_position ? true : p_compare(*(p_first + ((p_position - p_first) - 1) / 2), *p_position);
}

template <typename RIterator, typename Compare>
void dsaa::heapify(RIterator p_first, RIterator p_last, RIterator p_position, Compare p_compare)
{
    RIterator left_index;
    RIterator right_index;
    RIterator key_index = p_position;
    RIterator previous_key_index = p_position;

    while (true)
    {
        // is this a leaf node.
        if (p_first + ((p_last - p_first) / 2) <= previous_key_index)
            break;
        // index of left child.
        left_index = p_first + (2 * (key_index - p_first) + 1);
        // index of right child.
        right_index = p_first + (2 * (key_index - p_first) + 2);

        key_index = (left_index < p_last && !p_compare(*key_index, *left_index)) ? left_index : key_index;
        key_index = (right_index < p_last && !p_compare(*key_index, *right_index)) ? right_index : key_index;

        if (key_index != previous_key_index)
        {
            std::swap(*previous_key_index, *key_index);
            previous_key_index = key_index;
        }
        else
            break;
    }
}
#endif // !DSAA_HEAP_H