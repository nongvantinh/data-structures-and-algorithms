#include "Catch2/Catch.hpp"
#include <vector>
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

bool operator==(const Matrix& p_first, const Matrix& p_second)
{
	if (p_first.rows() != p_second.rows())
		return false;
	if (p_first.columns() != p_second.columns())
		return false;

	for (size_t i(0); i != p_first.rows(); ++i)
	{
		for (size_t k(0); k != p_first.columns(); ++k)
		{
			if (p_first[i][k] != p_second[i][k])
				return false;
		}
	}

	return true;
}

Matrix matrix_multiply(Matrix p_first, Matrix p_second)
{
	if (p_first.rows() != p_second.columns())
		throw std::runtime_error("incompatible dimention");

	Matrix result(p_first.rows(), p_second.columns());
	for (size_t i(0); i != p_first.rows(); ++i)
	{
		for (size_t k(0); k != p_second.columns(); ++k)
		{
			for (size_t m(0); m != p_first.columns(); ++m)
			{
				result[i][k] = result[i][k] + p_first[i][m] * p_second[m][k];
			}
		}
	}

	return result;
}

template<typename T = std::vector<Matrix>::const_iterator>
int matrix_chain_multiplication_aux(const std::vector<Matrix>& p_chain, Matrix& p_minimum_costs, Matrix& p_solution, size_t p_first, size_t p_last);

// Top-down approach with memoization added.
Matrix matrix_chain_multiplication(std::vector<Matrix> p_chain, Matrix& solution)
{
	Matrix minimum_costs(p_chain.size(), p_chain.size(), INT_MIN); // Holds the number of scalar mutiplication needed to compute matrix product.
	matrix_chain_multiplication_aux(p_chain, minimum_costs, solution, 0, p_chain.size() - 1);

	return minimum_costs;
}

// Calculate the number of scalar multiplication in the chain [p_first, p_last].
template<typename T >
int matrix_chain_multiplication_aux(const std::vector<Matrix>& p_chain, Matrix& p_minimum_costs, Matrix& p_solution, size_t p_first, size_t p_last)
{
	if (INT_MIN < p_minimum_costs[p_first][p_last])
		return p_minimum_costs[p_first][p_last];

	size_t min_cost(INT_MAX);
	if (p_first == p_last)
	{
		min_cost = 0;
	}
	else
	{
		for (size_t i(p_first); i < p_last; ++i)
		{
			// Calculate minimum scalar multiplication from: [first, i].
			size_t first_to_i = matrix_chain_multiplication_aux(p_chain, p_minimum_costs, p_solution, p_first, i);
			// Calculate minimum scalar multiplication from: [i + 1, last].
			size_t i_plus_1_to_last = matrix_chain_multiplication_aux(p_chain, p_minimum_costs, p_solution, i + 1, p_last);
			size_t scalar(first_to_i + i_plus_1_to_last + p_chain[p_first].rows() * p_chain[i].columns() * p_chain[p_last].columns());
			if (scalar <= min_cost)
			{
				min_cost = scalar;
				p_solution[p_first][p_last] = i;
			}
		}
	}

	p_minimum_costs[p_first][p_last] = min_cost;
	return p_minimum_costs[p_first][p_last];
}

// Tabular, bottom-up approach.
Matrix matrix_chain_order(const std::vector<Matrix>& p_chain, Matrix& solution)
{
	Matrix minimum_costs(p_chain.size(), p_chain.size(), 0); // Holds the number of scalar mutiplication needed to compute matrix product.

	for (size_t chain_length(1); chain_length < p_chain.size(); ++chain_length)
	{
		for (size_t first(0); first < p_chain.size() - chain_length; ++first)
		{
			size_t last = first + chain_length;
			minimum_costs[first][last] = INT_MAX;
			for (size_t k(first); k < last; ++k)
			{
				size_t scalar = minimum_costs[first][k] + minimum_costs[k + 1][last] + p_chain[first].rows() * p_chain[k].columns() * p_chain[last].columns();
				if (scalar < minimum_costs[first][last])
				{
					minimum_costs[first][last] = scalar;
					solution[first][last] = k;
				}
			}
		}
	}

	return minimum_costs;
}

void print_optimal_solution(const Matrix& p_solutions, size_t p_first, size_t p_last)
{
	if (p_first == p_last)
	{
		std::cout << "A" << p_first << " ";
	}
	else
	{
		std::cout << "(";
		print_optimal_solution(p_solutions, p_first, p_solutions[p_first][p_last]);
		print_optimal_solution(p_solutions, p_solutions[p_first][p_last] + 1, p_last);
		std::cout << ")";
	}
}


TEST_CASE("Matrix multiply operation.", "[matrix]")
{
	SECTION("No parenthesis.")
	{
		Matrix matrix1({ {2, 3, 4}, {1, 0, 0} });
		Matrix matrix2({ {0, 1000}, {1, 100}, {0, 10} });
		Matrix result({ {3, 2340}, {0, 1000} });

		CHECK(result == matrix_multiply(matrix1, matrix2));
	}
}

TEST_CASE("Matrix chain order top-down approach with memoization added.", "[matrix]")
{
	SECTION("One Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);
		CHECK(0 == matrix_chain_multiplication(values, solution)[first][last]);
	}

	SECTION("Two Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(15750 == matrix_chain_multiplication(values, solution)[first][last]);
	}

	SECTION("Three Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(7875 == matrix_chain_multiplication(values, solution)[first][last]);

	}

	SECTION("Four Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(9375 == matrix_chain_multiplication(values, solution)[first][last]);
	}

	SECTION("Five Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(11875 == matrix_chain_multiplication(values, solution)[first][last]);
	}

	SECTION("Six Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20),Matrix(20, 25) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(15125 == matrix_chain_multiplication(values, solution)[first][last]);
	}


	SECTION("at index [1, 4].")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20),Matrix(20, 25) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(1);
		size_t last(4);

		CHECK(7125 == matrix_chain_multiplication(values, solution)[first][last]);
	}
}


TEST_CASE("Matrix chain order using tabular bottom-up approach.", "[matrix]")
{
	SECTION("One Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);
		CHECK(0 == matrix_chain_order(values, solution)[first][last]);
	}

	SECTION("Two Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(15750 == matrix_chain_order(values, solution)[first][last]);
	}

	SECTION("Three Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(7875 == matrix_chain_order(values, solution)[first][last]);

	}

	SECTION("Four Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(9375 == matrix_chain_order(values, solution)[first][last]);
	}

	SECTION("Five Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(11875 == matrix_chain_order(values, solution)[first][last]);
	}

	SECTION("Six Matrix.")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20),Matrix(20, 25) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(0);
		size_t last(values.size() - 1);

		CHECK(15125 == matrix_chain_order(values, solution)[first][last]);
	}


	SECTION("at index [1, 4].")
	{
		std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20),Matrix(20, 25) };
		Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
		size_t first(1);
		size_t last(4);

		CHECK(7125 == matrix_chain_order(values, solution)[first][last]);
	}
}

TEST_CASE("Print optimal solution.", "[matrix]")
{
	std::vector<Matrix> values{ Matrix(30, 35),Matrix(35, 15),Matrix(15, 5) ,Matrix(5, 10),Matrix(10, 20),Matrix(20, 25) };
	Matrix solution(values.size(), values.size()); // Holds the index where we split the chain.
	matrix_chain_order(values, solution);
	print_optimal_solution(solution, 0, values.size() - 1);
}