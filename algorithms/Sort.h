#ifndef SORT_H
#define SORT_H

#include <memory>
#include <functional>
#include <algorithm>

namespace dsaa
{
	namespace sort
	{
		template <typename IIterator, typename SortBy = std::less_equal<typename std::iterator_traits<IIterator>::value_type>>
		bool is_sorted(IIterator p_first, IIterator p_last, SortBy p_sort_by);

		template <typename FIterator, typename Compare = std::less<typename std::iterator_traits<FIterator>::value_type>>
		FIterator buble_sort(FIterator p_first, FIterator p_last, Compare p_compare = Compare());
			}
}

template <typename IIterator, typename SortBy>
bool dsaa::sort::is_sorted(IIterator p_first, IIterator p_last, SortBy p_sort_by)
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
FIterator dsaa::sort::buble_sort(FIterator p_first, FIterator p_last, Compare p_compare)
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
#endif // ! SORT_H
