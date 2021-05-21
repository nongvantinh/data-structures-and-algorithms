#ifndef DSAA_NUMERIC_H
#define DSAA_NUMERIC_H

#include <iterator>

namespace dsaa
{
	template<typename Iterator>
	using value_type = typename std::iterator_traits<Iterator>::value_type;

	template<typename IIterator, typename Initialize>
	Initialize accumulate(IIterator p_first, IIterator p_last, Initialize p_initialize);

	template<typename IIterator, typename Initialize, typename Operator>
	Initialize accumulate(IIterator p_first, IIterator p_last, Initialize p_initialize, Operator p_operator);

	template<typename IIterator, typename Initialize>
	Initialize inner_product(IIterator p_first, IIterator p_last, IIterator p_first2, Initialize p_initialize);

	template<typename IIterator1, typename IIterator2, typename Initialize, typename Operator1, typename Operator2>
	Initialize inner_product(IIterator1 p_first, IIterator1 p_last, IIterator2 p_first2, Initialize p_initialize, Operator1 p_operator1, Operator2 p_operator2);
}

template<typename IIterator, typename Initialize>
Initialize dsaa::accumulate(IIterator p_first, IIterator p_last, Initialize p_initialize)
{
	while (p_first != p_last)
	{
		p_initialize = p_initialize + *p_first;
		++p_first;
	}

	return p_initialize;
}

template<typename IIterator, typename Initialize, typename Operator>
Initialize dsaa::accumulate(IIterator p_first, IIterator p_last, Initialize p_initialize, Operator p_operator)
{
	while (p_first != p_last)
	{
		p_initialize = p_operator(p_initialize, *p_first);
		++p_first;
	}

	return p_initialize;
}

template<typename IIterator, typename Initialize>
Initialize dsaa::inner_product(IIterator p_first, IIterator p_last, IIterator p_first2, Initialize p_initialize)
{
	while (p_first != p_last)
	{
		p_initialize = p_initialize + (*p_first) * (*p_first2);
		++p_first;
		++p_first2;
	}
	return p_initialize;
}

template<typename IIterator1, typename IIterator2, typename Initialize, typename Operator1, typename Operator2>
Initialize dsaa::inner_product(IIterator1 p_first, IIterator1 p_last, IIterator2 p_first2, Initialize p_initialize, Operator1 p_operator1, Operator2 p_operator2)
{
	while (p_first != p_last)
	{
		p_initialize = p_operator1(p_initialize, p_operator2((*p_first), (*p_first2)));
		++p_first;
		++p_first2;
	}
	return p_initialize;
}
#endif // !DSAA_NUMERIC_H