#ifndef SORT_H
#define SORT_H

#include <memory>
#include <functional>
#include <algorithm>

namespace dsaa
{
	template <typename IIterator, typename SortBy = std::less_equal<typename std::iterator_traits<IIterator>::value_type>>
	bool is_sorted(IIterator p_first, IIterator p_last, SortBy p_sort_by);

	template <typename FIterator, typename Compare = std::less<typename std::iterator_traits<FIterator>::value_type>>
	FIterator buble_sort(FIterator p_first, FIterator p_last, Compare p_compare = Compare());

	template <typename FIterator, typename Compare = std::less<typename std::iterator_traits<FIterator>::value_type>>
	FIterator selection_sort(FIterator p_first, FIterator p_last, Compare p_compare = Compare());

	template <typename BIterator, typename Compare = std::less<typename std::iterator_traits<BIterator>::value_type>>
	BIterator insertion_sort(BIterator p_first, BIterator p_last, Compare p_compare = Compare());

	template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
	RIterator merge_sort(RIterator p_first, RIterator p_last, Compare p_compare = Compare());

	template <typename RIterator, typename Compare = std::less<typename std::iterator_traits<RIterator>::value_type>>
	RIterator merge(RIterator p_first, RIterator p_mid, RIterator p_last, Compare p_compare = Compare());
}

template <typename IIterator, typename SortBy>
bool dsaa::is_sorted(IIterator p_first, IIterator p_last, SortBy p_sort_by)
{
	if (p_first == p_last)
		return true;
	IIterator succ_first(p_first);
	++succ_first;
	while (succ_first != p_last)
	{
		if (!p_sort_by(*p_first, *succ_first))
			return false;
		++p_first;
		++succ_first;
	}
	return true;
}

template <typename FIterator, typename Compare>
FIterator dsaa::buble_sort(FIterator p_first, FIterator p_last, Compare p_compare)
{
	while (p_first != p_last)
	{
		FIterator k(p_first);
		++k;

		for (; k != p_last; ++k)
		{
			if (p_compare(*k, *p_first))
				std::swap(*k, *p_first);
		}
		++p_first;
	}
	return p_first;
}

template <typename FIterator, typename Compare>
FIterator dsaa::selection_sort(FIterator p_first, FIterator p_last, Compare p_compare)
{
	while (p_first != p_last)
	{
		FIterator key(p_first), k(p_first);
		++k;

		for (; k != p_last; ++k)
		{
			if (p_compare(*k, *key))
				key = k;
		}
		if (key != p_first)
			std::swap(*key, *p_first);
		++p_first;
	}
	return p_first;
}

template <typename BIterator, typename Compare>
BIterator dsaa::insertion_sort(BIterator p_first, BIterator p_last, Compare p_compare)
{
	if (p_first == p_last)
		return p_first;

	BIterator i(p_first), index(p_first), succ_index(p_first);
	++i;
	for (; i != p_last; ++i)
	{
		auto key = *i;

		// Step back.
		index = i;
		--index;

		succ_index = p_first; // Reset succ_index.
		while (p_compare(key, *index))
		{
			succ_index = index;
			*(++succ_index) = *index; // Move data to the right.

			if (index == p_first) // Assume we can not move past the begining.
				break;
			--index;
		}
		if (succ_index == p_first) // Nothing happened.
			continue;
		if (index != p_first)
			*(++index) = key; // Offset for the last --index;
		else
			*(index) = key; // We met the begining.
	}
	return i;
}

template <typename RIterator, typename Compare>
RIterator dsaa::merge_sort(RIterator p_first, RIterator p_last, Compare p_compare)
{
	if (p_first == p_last)
		return p_first;

	if (p_first < p_last - 1)
	{
		RIterator mid_index(p_first + (p_last - p_first) / 2);
		merge_sort(p_first, mid_index, p_compare);
		merge_sort(mid_index, p_last, p_compare);
		merge(p_first, mid_index, p_last, p_compare);
	}
	return p_last;
}

template <typename RIterator, typename Compare>
RIterator dsaa::merge(RIterator p_first, RIterator p_mid, RIterator p_last, Compare p_compare)
{
	if (p_first == p_last)
		return p_first;
	size_t arr1_size = p_mid - p_first;
	size_t arr2_size = p_last - p_mid;
	std::vector<std::iterator_traits<RIterator>::value_type> left(arr1_size);
	std::vector<std::iterator_traits<RIterator>::value_type> right(arr2_size);

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
#endif // ! SORT_H
