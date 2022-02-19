#include "Catch2/Catch.hpp"
#include "algorithms/Random.h"
#include "test/TestObject.h"
#include "math/Matrix.h"

#include <initializer_list>

using size_type = dsaa::Matrix<TestObject<int>>::size_type;

TEST_CASE("Test Maxtrix Matrix(const size_type &p_row, const size_type &p_column) constructor.", "[Matrix]")
{
    const size_type row_size(3), column_size(5);
    TestObject<int> default_value(100);
    dsaa::Matrix<TestObject<int>> matrix(row_size, column_size, default_value);
    REQUIRE(row_size == matrix.row_size());
    REQUIRE(column_size == matrix.column_size());

    for (size_type i(0); i != matrix.row_size(); ++i)
    {
        for (size_type k(0); k != matrix.column_size(); ++k)
        {
            REQUIRE(default_value == matrix[i][k]);
        }
    }
}

TEST_CASE("Test Maxtrix Matrix(std::initializer_list<std::initializer_list<value_type>> p_arg) constructor.", "[Matrix]")
{
    dsaa::DynamicArray<dsaa::DynamicArray<TestObject<int>>> arg{{1, 9, -13}, {20, 5, -6}};
    dsaa::Matrix<TestObject<int>> matrix(arg);
    REQUIRE(arg.size() == matrix.row_size());
    REQUIRE(arg[0].size() == matrix.column_size());

    for (size_type i(0); i != matrix.row_size(); ++i)
    {
        for (size_type k(0); k != matrix.column_size(); ++k)
        {
            REQUIRE(arg[i][k] == matrix[i][k]);
        }
    }
}

TEST_CASE("Test Maxtrix Matrix(const Matrix &p_other) copy constructor.", "[Matrix]")
{
    dsaa::DynamicArray<dsaa::DynamicArray<TestObject<int>>> arg{{1, 9, -13}, {20, 5, -6}};
    dsaa::Matrix<TestObject<int>> matrix(arg);
    dsaa::Matrix<TestObject<int>> matrix2(matrix);

    REQUIRE(arg.size() == matrix2.row_size());
    REQUIRE(arg[0].size() == matrix2.column_size());

    for (size_type i(0); i != matrix2.row_size(); ++i)
    {
        for (size_type k(0); k != matrix2.column_size(); ++k)
        {
            REQUIRE(arg[i][k] == matrix2[i][k]);
        }
    }
}

TEST_CASE("Test Maxtrix Matrix(Matrix &&p_other) move constructor.", "[Matrix]")
{
    dsaa::DynamicArray<dsaa::DynamicArray<TestObject<int>>> arg{{1, 9, -13}, {20, 5, -6}};
    dsaa::Matrix<TestObject<int>> matrix(arg);
    dsaa::Matrix<TestObject<int>> matrix2(std::move(matrix));

    REQUIRE(0 == matrix.row_size());

    REQUIRE(arg.size() == matrix2.row_size());
    REQUIRE(arg[0].size() == matrix2.column_size());

    for (size_type i(0); i != matrix2.row_size(); ++i)
    {
        for (size_type k(0); k != matrix2.column_size(); ++k)
        {
            REQUIRE(arg[i][k] == matrix2[i][k]);
        }
    }
}

TEST_CASE("Test Matrix &operator=(const Matrix &p_other) copy assignment.", "[Matrix]")
{
    dsaa::DynamicArray<dsaa::DynamicArray<TestObject<int>>> arg{{1, 9, -13}, {20, 5, -6}};
    dsaa::Matrix<TestObject<int>> matrix(arg);
    dsaa::Matrix<TestObject<int>> matrix2(0, 0);

    matrix2 = matrix;

    REQUIRE(arg.size() == matrix2.row_size());
    REQUIRE(arg[0].size() == matrix2.column_size());

    for (size_type i(0); i != matrix2.row_size(); ++i)
    {
        for (size_type k(0); k != matrix2.column_size(); ++k)
        {
            REQUIRE(arg[i][k] == matrix2[i][k]);
        }
    }
}

TEST_CASE("Test Matrix &operator=(Matrix &&p_other) move assignment.", "[Matrix]")
{
    dsaa::DynamicArray<dsaa::DynamicArray<TestObject<int>>> arg{{1, 9, -13}, {20, 5, -6}};
    dsaa::Matrix<TestObject<int>> matrix(arg);
    dsaa::Matrix<TestObject<int>> matrix2(0, 0);

    matrix2 = std::move(matrix);
    REQUIRE(0 == matrix.row_size());

    REQUIRE(arg.size() == matrix2.row_size());
    REQUIRE(arg[0].size() == matrix2.column_size());

    for (size_type i(0); i != matrix2.row_size(); ++i)
    {
        for (size_type k(0); k != matrix2.column_size(); ++k)
        {
            REQUIRE(arg[i][k] == matrix2[i][k]);
        }
    }
}

TEST_CASE("Test Matrix resize.", "[Matrix]")
{
    dsaa::DynamicArray<dsaa::DynamicArray<TestObject<int>>> arg{{1, 9, -13}, {20, 5, -6}};
    dsaa::Matrix<TestObject<int>> matrix(arg);

    matrix.resize(arg.size(), arg[0].size());

    matrix[0][0] = 1;
    matrix[0][1] = 9;
    matrix[0][2] = -13;
    matrix[1][0] = 20;
    matrix[1][1] = 5;
    matrix[1][2] = -6;

    for (size_type i(0); i != matrix.row_size(); ++i)
    {
        for (size_type k(0); k != matrix.column_size(); ++k)
        {
            REQUIRE(arg[i][k] == matrix[i][k]);
        }
    }
}

TEST_CASE("Test Matrix substraction.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{12, -3}, {2, 15}});
        dsaa::Matrix<TestObject<int>> matrix2({{6, 1}, {11, -8}});

        dsaa::Matrix<TestObject<int>> expected_value({{6, -4}, {-9, 23}});
        dsaa::Matrix<TestObject<int>> result(matrix - matrix2);

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }
}

TEST_CASE("Test Matrix addition.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{1, 3, 1}, {1, 0, 0}});
        dsaa::Matrix<TestObject<int>> matrix2({{0, 0, 5}, {7, 5, 0}});

        dsaa::Matrix<TestObject<int>> expected_value({{1, 3, 6}, {8, 5, 0}});
        dsaa::Matrix<TestObject<int>> result(matrix + matrix2);

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }
}

TEST_CASE("Test Matrix multiplication.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{2, 3, 4}, {1, 0, 0}});
        dsaa::Matrix<TestObject<int>> matrix2({{0, 1000}, {1, 100}, {0, 10}});

        dsaa::Matrix<TestObject<int>> expected_value({{3, 2340}, {0, 1000}});
        dsaa::Matrix<TestObject<int>> result(matrix * matrix2);

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }

    SECTION("value 2")
    {
        dsaa::Matrix<TestObject<int>> matrix({{1, 2}, {3, 4}});
        dsaa::Matrix<TestObject<int>> matrix2({{0, 1}, {0, 0}});

        dsaa::Matrix<TestObject<int>> expected_value({{0, 1}, {0, 3}});
        dsaa::Matrix<TestObject<int>> result(matrix * matrix2);

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }

    SECTION("value 3")
    {
        dsaa::Matrix<TestObject<int>> matrix({{0, 1}, {0, 0}});
        dsaa::Matrix<TestObject<int>> matrix2({{1, 2}, {3, 4}});

        dsaa::Matrix<TestObject<int>> expected_value({{3, 4}, {0, 0}});
        dsaa::Matrix<TestObject<int>> result(matrix * matrix2);

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }
}

TEST_CASE("Test Matrix scalar multiplication.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{1, 8, -3}, {4, -2, 5}});
        TestObject<int> scalar(2);
        dsaa::Matrix<TestObject<int>> expected_value({{2, 16, -6}, {8, -4, 10}});
        dsaa::Matrix<TestObject<int>> result(matrix * scalar);

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }
}

TEST_CASE("Test Matrix transpose.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{1, 2, 3}, {0, -6, 7}});
        dsaa::Matrix<TestObject<int>> expected_value({{1, 0}, {2, -6}, {3, 7}});
        dsaa::Matrix<TestObject<int>> result(matrix.transpose());

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }
}

TEST_CASE("Test Matrix submatrix.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});
        dsaa::Matrix<TestObject<int>> expected_value({{1, 3, 4}, {5, 7, 8}});
        dsaa::Matrix<TestObject<int>> result(matrix.submatrix(2, 1));

        REQUIRE(expected_value.row_size() == result.row_size());
        REQUIRE(expected_value.column_size() == result.column_size());

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                REQUIRE(expected_value[i][k] == result[i][k]);
            }
        }
    }
}

TEST_CASE("Test Matrix identity.", "[Matrix]")
{
    SECTION("value 1")
    {
        dsaa::Matrix<TestObject<int>> matrix({{1, 2, 3}, {5, 6, 7}, {9, 10, 11}});
        dsaa::Matrix<TestObject<int>> result(dsaa::Matrix<TestObject<int>>::identity(3, 3));

        REQUIRE(matrix.row_size() == result.row_size());
        REQUIRE(matrix.column_size() == result.column_size());

        for (size_type i(0); i != result.row_size(); ++i)
        {
            for (size_type k(0); k != result.column_size(); ++k)
            {
                if (i == k)
                    REQUIRE(TestObject<int>(1) == result[i][k]);
                else
                    REQUIRE(TestObject<int>(0) == result[i][k]);
            }
        }
    }
}