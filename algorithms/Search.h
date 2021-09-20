#ifndef DSAA_SEARCH_H
#define DSAA_SEARCH_H

#include <iostream>
#include "Generic.h"
#include "Sort.h"

namespace dsaa
{
	template <typename IIterator, typename Value>
	IIterator linear_search(IIterator p_first, IIterator p_last, Value p_value);
	template <typename IIterator, typename Predicate>
	IIterator linear_search_if(IIterator p_first, IIterator p_last, Predicate p_predicate);

	template <typename RIterator, typename Value>
	RIterator binary_search(RIterator p_first, RIterator p_last, Value p_value);

	template <typename RIterator, typename OrderBy, typename Predicate>
	RIterator binary_search(RIterator p_first, RIterator p_last, OrderBy p_orderBy, Predicate p_predicate);

	template <typename RIterator>
	std::tuple<RIterator, RIterator> search_pair_min_max(RIterator p_first, RIterator p_last);
}

template <typename IIterator, typename Value>
IIterator dsaa::linear_search(IIterator p_first, IIterator p_last, Value p_value)
{
	while (p_first != p_last && *p_first != p_value)
		++p_first;

	return p_first;
}

template <typename IIterator, typename Predicate>
IIterator dsaa::linear_search_if(IIterator p_first, IIterator p_last, Predicate p_predicate)
{
	while (p_first != p_last && !p_predicate(*p_first))
		++p_first;

	return p_first;
}

template <typename RIterator, typename Value>
RIterator dsaa::binary_search(RIterator p_first, RIterator p_last, Value p_value)
{
	RIterator low(p_first), mid(p_first), high(p_last);

	while (low < high)
	{
		mid = low + ((high - low) / 2);
		if (*mid == p_value)
			return mid;
		// Corner case. Value not found in list.
		if (mid + 1 == high)
		{
			if (*low == p_value)
				return low;
			if (*high == p_value)
				return high;
			return p_last;
		}

		if (*p_first <= *(p_last - 1))
		{
			if (*mid < p_value)
				low = mid;
			else
				high = mid;
		}
		else
		{
			if (*mid < p_value)
				high = mid;
			else
				low = mid;
		}
	}
	return p_last;
}

template <typename RIterator, typename OrderBy, typename Predicate>
RIterator dsaa::binary_search(RIterator p_first, RIterator p_last, OrderBy p_orderBy, Predicate p_predicate)
{
	RIterator low(p_first), mid(p_first), high(p_last);

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (mid == p_last)
			return p_last;
		else if (p_predicate(*mid))
			return mid;
		else if (p_orderBy(*p_first, *(p_last - 1)))
		{
			if (p_predicate(*mid))
				low = mid;
			else
				high = mid;
		}
		else
		{
			if (p_predicate(*mid))
				high = mid;
			else
				low = mid;
		}
	}
	return p_last;
}

template <typename RIterator>
std::tuple<RIterator, RIterator> dsaa::search_pair_min_max(RIterator p_first, RIterator p_last)
{
	if (p_first == p_last)
		return std::tuple(p_first, p_last);
	if (1 == p_last - p_first)
		return std::tuple(p_first, p_first);

	RIterator min_value(p_first);
	RIterator max_value(p_first);

	// Even number of element.
	if (0 == (p_last - p_first) % 2)
	{
		if (*p_first < *(p_first + 1))
		{
			min_value = p_first;
			max_value = (p_first + 1);
		}
		else if (*p_first > *(p_first + 1))
		{
			min_value = (p_first + 1);
			max_value = p_first;
		}
		p_first += 2;
	}
	else
	{
		min_value = max_value = p_first;
		++p_first;
	}

	// Corner case, the rest elements are equal except the begining.
	if (*p_first < *min_value)
		min_value = p_first;
	else if (*p_first > *max_value)
		max_value = p_first;

	for (auto iter(p_first); p_last != iter; iter += 2)
	{
		if (*iter < *(iter + 1))
		{
			min_value = (*iter < *min_value) ? iter : min_value;
			max_value = (*max_value < *(iter + 1)) ? (iter + 1) : max_value;
		}
		else if (*iter > *(iter + 1))
		{
			min_value = (*(iter + 1) < *min_value) ? (iter + 1) : min_value;
			max_value = (*max_value < *iter) ? iter : max_value;
		}
	}
	return std::tuple(min_value, max_value);
}
#endif // !DSAA_SEARCH_H
