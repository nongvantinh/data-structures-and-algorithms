#include "test.h"

#include <iostream>

#include "test_sort_algorithms.h"
#include "test_search_algorithms.h"
#include "facilities.h"

void algorithms::test::test()
{
	test_sort_algorithms();
	test_search_algorithms();
}

void algorithms::test::test_sort_algorithms()
{
	std::cout << "---------------------------------------------\n";
	std::cout << "running test_sort_algorithms.\n";
	std::cout << "test_insertion_sort: " << (algorithms::test::sort::test_insertion_sort() ? "OK." : "Failed.") << std::endl;
	std::cout << "test_selection_sort: " << (algorithms::test::sort::test_selection_sort() ? "OK." : "Failed.") << std::endl;
	std::cout << "test_bubble_sort: "    << (algorithms::test::sort::test_bubble_sort()    ? "OK." : "Failed.") << std::endl;
	std::cout << "test_merge_sort: "    << (algorithms::test::sort::test_merge_sort()    ? "OK." : "Failed.") << std::endl;
}

void algorithms::test::test_search_algorithms()
{
	std::cout << "---------------------------------------------\n";
	std::cout << "running test_search_algorithms.\n";
	std::cout << "test_linear_search: " << (algorithms::test::search::test_linear_search() ? "OK." : "Failed.") << std::endl;
	std::cout << "test_binary_search: " << (algorithms::test::search::test_binary_search() ? "OK." : "Failed.") << std::endl;
}
