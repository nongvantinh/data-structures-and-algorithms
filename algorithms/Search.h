#ifndef SEARCH_H
#define SEARCH_H

namespace dsaa
{
	namespace search
	{
		template<typename IIterator, typename Value>
		IIterator linear_search(IIterator p_first, IIterator p_last, Value p_value);
		template <typename IIterator, typename Predicate>
		IIterator linear_search_if(IIterator p_first, IIterator p_last, Predicate p_predicate);

		template <typename RIterator, typename Value>
		RIterator binary_search(RIterator p_first, RIterator p_last, Value p_value);

		template <typename RIterator, typename OrderBy, typename Predicate>
		RIterator binary_search(RIterator p_first, RIterator p_last, OrderBy p_orderBy, Predicate p_predicate);
	}
}

template<typename IIterator, typename Value>
IIterator dsaa::search::linear_search(IIterator p_first, IIterator p_last, Value p_value)
{
	while (p_first != p_last && *p_first != p_value)
		++p_first;

	return p_first;
}

template <typename IIterator, typename Predicate>
IIterator dsaa::search::linear_search_if(IIterator p_first, IIterator p_last, Predicate p_predicate)
{
	while (p_first != p_last && !p_predicate(*p_first))
		++p_first;

	return p_first;
}

template <typename RIterator, typename Value>
RIterator dsaa::search::binary_search(RIterator p_first, RIterator p_last, Value p_value)
{
	RIterator low(p_first), mid(p_first), high(p_last);

	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (mid == p_last)
			return p_last;
		else if (*mid == p_value)
			return mid;
		else if (*p_first < *(p_last - 1))
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
RIterator dsaa::search::binary_search(RIterator p_first, RIterator p_last, OrderBy p_orderBy, Predicate p_predicate)
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

#endif SEARCH_H
