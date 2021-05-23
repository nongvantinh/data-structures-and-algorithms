#ifndef DSAA_TEST_H
#define DSAA_TEST_H

#include <iostream>
#include <random>
#include <cassert>

namespace dsaa
{
	unsigned int random_range(unsigned int start = 0, unsigned int end = 678);

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
