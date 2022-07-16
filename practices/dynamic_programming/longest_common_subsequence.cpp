/*
Given two strands:
S1 = ACCGGTCGAGTGCGCGGAAGCCGGCCGAA
S2 = GTCGTTCGGAATGCCGTTGCTCTGTAAA

We can define the similarity as follows:
    1. Two DNA strands are similar if one is a substring of the other, or
    2. Two strands are similar if the number of changes needed to turn one into the other is small, or
    3. There is a third strand S3 in which the bases in S3 appear in each of S1 and S2:
            - These bases must appear in the same order, but not necessarily consecutively.
            - The longer the strand S3 we can find, the more similar S1 and S2 are.
    In our example, the longest strand S3 is GTCGTCGGAAGCCGGCCGAA.

--> I implemented the algorithm using rule number 3.
*/

#include "Catch2/Catch.hpp"
#include <vector>
#include <tuple>
#include <sstream>
#include <vector>
#include <tuple>
#include <sstream>
#include <iostream>

class Matrix
{
public:
	Matrix(size_t p_rows, size_t p_columns, int p_value = 0) : m_matrix(p_rows)
	{
		for (auto& row : m_matrix)
		{
			row.resize(p_columns);
			for (auto& i : row)
			{
				i = p_value;
			}
		}
	}

	Matrix(const std::vector<std::vector<int>>& p_args) : m_matrix(p_args.size())
	{
		for (size_t i(0); i != rows(); ++i)
		{
			m_matrix[i] = p_args[i];
		}
	}

	size_t rows() const { return m_matrix.size(); }
	size_t columns() const { return 0 == rows() ? 0 : m_matrix[0].size(); }

	std::vector<int>& operator[](size_t p_index)
	{
		if (0 == rows())
			throw std::runtime_error("Matrix is empty");
		if (p_index < 0 || rows() <= p_index)
			throw std::runtime_error("Index out of range");

		return m_matrix[p_index];
	}

	const std::vector<int>& operator[](size_t p_index) const
	{
		if (0 == rows())
			throw std::runtime_error("Matrix is empty");
		if (p_index < 0 || rows() <= p_index)
			throw std::runtime_error("Index out of range");

		return m_matrix[p_index];
	}

private:
	std::vector<std::vector<int>> m_matrix;
};

std::tuple<Matrix, Matrix> tabular_lcs_length(const std::string& p_first, const std::string& p_second)
{
	Matrix lcs_table(p_first.size() + 1, p_second.size() + 1);
	Matrix direction(p_first.size(), p_second.size());

	for (size_t i(1); i <= p_first.size(); ++i)
	{
		for (size_t k(1); k <= p_second.size(); ++k)
		{
			if (p_first[i - 1] == p_second[k - 1])
			{
				lcs_table[i][k] = lcs_table[i - 1][k - 1] + 1;
				direction[i - 1][k - 1] = '\\'; // Move up left
			}
			else if (lcs_table[i][k - 1] <= lcs_table[i - 1][k])
			{
				lcs_table[i][k] = lcs_table[i - 1][k];
				direction[i - 1][k - 1] = '|'; // Move up.
			}
			else
			{
				lcs_table[i][k] = lcs_table[i][k - 1];
				direction[i - 1][k - 1] = '-'; // Move left.
			}
		}
	}

	return std::make_tuple(lcs_table, direction);
}

void lcs_aux(const Matrix& p_direction, const std::string& p_strand, int p_strand1_length, int p_strand2_length, std::stringstream& p_ss)
{
	if (0 == p_strand1_length || 0 == p_strand2_length)
		return;

	if ('\\' == p_direction[p_strand1_length - 1][p_strand2_length - 1])
	{
		lcs_aux(p_direction, p_strand, p_strand1_length - 1, p_strand2_length - 1, p_ss);
		p_ss << p_strand[p_strand1_length - 1];
	}
	else if ('|' == p_direction[p_strand1_length - 1][p_strand2_length - 1])
	{
		lcs_aux(p_direction, p_strand, p_strand1_length - 1, p_strand2_length, p_ss);
	}
	else
	{
		lcs_aux(p_direction, p_strand, p_strand1_length, p_strand2_length - 1, p_ss);
	}
}

// Returns the longest common subseuence of two strands.
std::string tabular_get_lcs(const std::string& p_first_strand, const std::string& p_second_strand)
{
	std::stringstream ss;
	auto result = tabular_lcs_length(p_first_strand, p_second_strand);
	lcs_aux(std::get<1>(result), p_first_strand, p_first_strand.size(), p_second_strand.size(), ss);

	return ss.str();
}

void memoized_lcs_length(Matrix& lcs_table, Matrix& direction, const std::string& p_first, const std::string& p_second, int p_strand1_length, int p_strand2_length)
{
	if (0 == p_strand1_length)
		return;

	if (0 != lcs_table[p_strand1_length][p_strand2_length])
		return;

	memoized_lcs_length(lcs_table, direction, p_first, p_second, p_strand1_length - 1, p_strand2_length - 1);

	for (size_t k(1); k <= p_second.size(); ++k)
	{
		if (p_first[p_strand1_length - 1] == p_second[k - 1])
		{
			lcs_table[p_strand1_length][k] = lcs_table[p_strand1_length - 1][k - 1] + 1;
			direction[p_strand1_length - 1][k - 1] = '\\'; // Move up left
		}
		else if (lcs_table[p_strand1_length][k - 1] <= lcs_table[p_strand1_length - 1][k])
		{
			lcs_table[p_strand1_length][k] = lcs_table[p_strand1_length - 1][k];
			direction[p_strand1_length - 1][k - 1] = '|'; // Move up.
		}
		else
		{
			lcs_table[p_strand1_length][k] = lcs_table[p_strand1_length][k - 1];
			direction[p_strand1_length - 1][k - 1] = '-'; // Move left.
		}
	}
}

std::string memoized_get_lcs(const std::string& p_first_strand, const std::string& p_second_strand)
{
	std::stringstream ss;

	Matrix lcs_table(p_first_strand.size() + 1, p_second_strand.size() + 1);
	Matrix direction(p_first_strand.size(), p_second_strand.size());

	memoized_lcs_length(lcs_table, direction, p_first_strand, p_second_strand, p_first_strand.size(), p_second_strand.size());
	lcs_aux(direction, p_first_strand, p_first_strand.size(), p_second_strand.size(), ss);

	return ss.str();
}

void get_lcs_aux(const Matrix& p_lcs_table, const std::string& p_first_strand, const std::string& p_second_strand, std::stringstream& p_ss)
{
	if (0 == p_first_strand.size())
		return;

	int x(p_first_strand.size());
	int y(p_second_strand.size());

	while (0 != x && 0 != y)
	{
		int left(p_lcs_table[x - 1][y]);
		int top(p_lcs_table[x][y - 1]);

		if (p_first_strand[x - 1] == p_second_strand[y - 1])
		{
			p_ss << p_first_strand[x - 1];
			--x;
			--y;
		}
		else if (left < top)
		{
			--y;
		}
		else
		{
			--x;
		}
	}
}

std::string get_lcs_without_direction_table(const std::string& p_first_strand, const std::string& p_second_strand)
{
	std::stringstream ss;

	Matrix lcs_table(p_first_strand.size() + 1, p_second_strand.size() + 1);
	Matrix direction(p_first_strand.size(), p_second_strand.size());

	memoized_lcs_length(lcs_table, direction, p_first_strand, p_second_strand, p_first_strand.size(), p_second_strand.size());
	get_lcs_aux(lcs_table, p_first_strand, p_second_strand, ss);

	std::string result(ss.str());
	std::reverse(result.begin(), result.end());
	return result;
}

TEST_CASE("Find longest_common_subsequence using tabular bottom-up approach.", "[longest_common_subsequence]")
{
	SECTION("Some common_subsequence.")
	{
		std::string x = "ABCBDAB";
		std::string y = "BDCABA";
		const std::string lcs = "BCBA";

		CHECK(lcs == tabular_get_lcs(x, y));
	}

	SECTION("Other common_subsequence.")
	{
		std::string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
		std::string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
		const std::string result = "GTCGTCGGAAGCCGGCCGAA";

		CHECK(result == tabular_get_lcs(x, y));
	}

	SECTION("Other common_subsequence.")
	{
		std::string x = "10010101";
		std::string y = "010110110";
		const std::string result = "100110";

		CHECK(result == tabular_get_lcs(x, y));
	}
}


TEST_CASE("Find longest_common_subsequence using memozation approach.", "[longest_common_subsequence]")
{
	SECTION("Some common_subsequence.")
	{
		std::string x = "ABCBDAB";
		std::string y = "BDCABA";
		const std::string lcs = "BCBA";

		CHECK(lcs == memoized_get_lcs(x, y));
	}

	SECTION("Other common_subsequence.")
	{
		std::string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
		std::string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
		const std::string result = "GTCGTCGGAAGCCGGCCGAA";

		CHECK(result == memoized_get_lcs(x, y));
	}

	SECTION("Other common_subsequence.")
	{
		std::string x = "10010101";
		std::string y = "010110110";
		const std::string result = "100110";

		CHECK(result == memoized_get_lcs(x, y));
	}
}


TEST_CASE("Find longest_common_subsequence using tabular bottom-up approach without direction table.", "[longest_common_subsequence]")
{
	SECTION("Some common_subsequence.")
	{
		std::string x = "ABCBDAB";
		std::string y = "BDCABA";
		const std::string lcs = "BCBA";

		CHECK(lcs == get_lcs_without_direction_table(x, y));
	}

	SECTION("Other common_subsequence.")
	{
		std::string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
		std::string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
		const std::string result = "GTCGTCGGAAGCCGGCCGAA";

		CHECK(result == get_lcs_without_direction_table(x, y));
	}

	SECTION("Other common_subsequence.")
	{
		std::string x = "10010101";
		std::string y = "010110110";
		const std::string result = "100110";

		CHECK(result == get_lcs_without_direction_table(x, y));
	}
}