#ifndef DSAA_TEST_H
#define DSAA_TEST_H

#include <iostream>
#include <random>
#include <cassert>

namespace dsaa
{
	template <class Iterator>
	void print_elem(Iterator p_first, Iterator p_last);
}

template <class Iterator>
void dsaa::print_elem(Iterator p_first, Iterator p_last)
{
	std::cout << "{ ";
	while (p_first != p_last)
	{
		std::cout << *p_first << ",";
		++p_first;
	}
	std::cout << " }" << std::endl;
}

#endif // !DSAA_TEST_H
