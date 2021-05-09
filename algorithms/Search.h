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
#endif SEARCH_H
