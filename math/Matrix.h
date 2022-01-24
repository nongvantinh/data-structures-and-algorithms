#ifndef DSAA_MATRIX_H
#define DSAA_MATRIX_H

#include "DynamicArray.h"

namespace dsaa
{
    template <typename Elem,
              typename ElementAllocator = std::allocator<Elem>,
              typename ContainerAllocator = std::allocator<DynamicArray<Elem, ElementAllocator>>>
    class Matrix
    {
    public:
        using value_type = Elem;
        using element_allocator_type = ElementAllocator;
        using container_allocator_type = ContainerAllocator;
        using size_type = size_t;
        using row_type = DynamicArray<DynamicArray<value_type, element_allocator_type>, container_allocator_type>;
        using column_type = DynamicArray<value_type, element_allocator_type>;

        // Creates a container's p_row and p_colum and initialize with p_default_value.
        CONSTEXPR explicit Matrix(const size_type &p_row, const size_type &p_column, const value_type &p_default_value = value_type()) noexcept;
        CONSTEXPR explicit Matrix(dsaa::DynamicArray<dsaa::DynamicArray<value_type>> p_arg) noexcept;
        // Creates a container and copy all emements from p_other.
        CONSTEXPR Matrix(const Matrix &p_other) noexcept;
        // Moves all elements from p_other into this.
        CONSTEXPR Matrix(Matrix &&p_other) noexcept;
        // Destroys old elements and copy all emements from p_other into this.
        CONSTEXPR Matrix &operator=(const Matrix &p_other) noexcept;
        // Destroys old elements and moves all emements from p_other into this.
        CONSTEXPR Matrix &operator=(Matrix &&p_other) noexcept(std::allocator_traits<element_allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<element_allocator_type>::is_always_equal::value);
        CONSTEXPR Matrix operator-(Matrix const &p_other);
        CONSTEXPR Matrix operator+(Matrix const &p_other);
        CONSTEXPR Matrix operator*(Matrix const &p_other);
        CONSTEXPR Matrix operator*(const value_type &p_scalar);
        CONSTEXPR Matrix transpose();
        CONSTEXPR static Matrix identity(size_type p_row, size_type p_column);
        CONSTEXPR Matrix submatrix(size_type p_row, size_type p_column);

        // Destroys all elements and clean used space.
        CONSTEXPR ~Matrix();

        CONSTEXPR void resize(const size_type &p_row, const size_type &p_column, const value_type &p_default_value = value_type());
        NODISCARD CONSTEXPR INLINE size_type row_size() const NOEXCEPT;
        NODISCARD CONSTEXPR INLINE size_type column_size() const NOEXCEPT;

        // Returns a reference to the underlying array at row p_index.
        NODISCARD CONSTEXPR INLINE column_type &operator[](const size_type &p_index) NOEXCEPT;
        NODISCARD CONSTEXPR INLINE column_type const &operator[](const size_type &p_index) const NOEXCEPT;
        // Bounds checking that returns a reference to the element at position p_index in the container.
        NODISCARD CONSTEXPR INLINE column_type &at(const size_type &p_index);
        NODISCARD CONSTEXPR INLINE column_type const &at(const size_type &p_index) const;

        // Returns a copy of the allocator object associated with the container.
        NODISCARD CONSTEXPR INLINE element_allocator_type const &get_element_allocator() const noexcept;
        NODISCARD CONSTEXPR INLINE container_allocator_type const &get_container_allocator() const noexcept;

    private:
        row_type m_matrix;
    };
} // dsaa

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::Matrix(const size_type &p_row, const size_type &p_column, const value_type &p_default_value) noexcept
    : m_matrix(p_row)
{
    for (size_type i(0); i != p_row; ++i)
        m_matrix[i].resize(p_column, p_default_value);
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::Matrix(dsaa::DynamicArray<dsaa::DynamicArray<value_type>> p_arg) noexcept
    : m_matrix(p_arg.size())
{
    for (size_type i(0); i != p_arg.size(); ++i)
        m_matrix[i] = p_arg[i];
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::Matrix(const Matrix &p_other) noexcept
    : m_matrix(p_other.m_matrix) {}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::Matrix(Matrix &&p_other) noexcept
    : m_matrix(std::move(p_other.m_matrix)) {}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator=(const Matrix &p_other) noexcept
{
    m_matrix = p_other.m_matrix;
    return *this;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator=(Matrix &&p_other) noexcept(std::allocator_traits<element_allocator_type>::propagate_on_container_move_assignment::value || std::allocator_traits<element_allocator_type>::is_always_equal::value)
{
    m_matrix = std::move(p_other.m_matrix);

    return *this;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator-(Matrix const &p_other)
{
    if (row_size() != p_other.row_size())
        throw std::runtime_error("Invalid matrix size: row_size() != p_other.row_size().\n");
    if (column_size() != p_other.column_size())
        throw std::runtime_error("Invalid matrix size: column_size() != p_other.column_size().\n");

    Matrix result(row_size(), column_size());

    for (size_type i(0); i != result.row_size(); ++i)
    {
        for (size_type k(0); k != result.column_size(); ++k)
        {
            result[i][k] = (*this)[i][k] - p_other[i][k];
        }
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator+(Matrix const &p_other)
{
    if (row_size() != p_other.row_size())
        throw std::runtime_error("Invalid matrix size: row_size() != p_other.row_size().\n");
    if (column_size() != p_other.column_size())
        throw std::runtime_error("Invalid matrix size: column_size() != p_other.column_size().\n");

    Matrix result(row_size(), column_size());

    for (size_type i(0); i != result.row_size(); ++i)
    {
        for (size_type k(0); k != result.column_size(); ++k)
        {
            result[i][k] = (*this)[i][k] + p_other[i][k];
        }
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator*(Matrix const &p_other)
{
    if (column_size() != p_other.row_size())
        throw std::runtime_error("Incompatible dimention: row_size() != p_other.column_size().\n");
    
    Matrix result(row_size(), p_other.column_size());
    for (size_type i(0); i != result.row_size(); ++i)
    {
        for (size_type k(0); k != result.column_size(); ++k)
        {
            for (size_type m(0); m != this->column_size(); ++m)
            {
                    result[i][k] = result[i][k] + (*this)[i][m] * p_other[m][k];
            }
        }
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator*(const value_type &p_scalar)
{
    Matrix result(row_size(), column_size());

    for (size_type i(0); i != result.row_size(); ++i)
    {
        for (size_type k(0); k != result.column_size(); ++k)
        {
            result[i][k] = (*this)[i][k] * p_scalar;
        }
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::transpose()
{
    Matrix result(column_size(), row_size());

    for (size_type i(0); i != result.row_size(); ++i)
    {
        for (size_type k(0); k != result.column_size(); ++k)
        {
            result[i][k] = (*this)[k][i];
        }
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::submatrix(size_type p_row, size_type p_column)
{
    if (row_size() <= p_row)
        throw std::runtime_error("Invalid matrix size: row_size() <= p_row.\n");
    if (column_size() <= p_column)
        throw std::runtime_error("Invalid matrix size: column_size() <= p_column.\n");

    Matrix result(row_size() - 1, column_size() - 1);

    for (size_type i(0), row_index(0); i != row_size(); ++i)
    {
        if (i == p_row)
            continue;
        for (size_type k(0), column_index(0); k != column_size(); ++k)
        {
            if (k == p_column)
                continue;
            result[row_index][column_index++] = (*this)[i][k];
        }
        ++row_index;
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator> dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::identity(size_type p_row, size_type p_column)
{
    if (p_row != p_column)
        throw std::runtime_error("Could not create identity matrix: p_row != p_column\n");

    Matrix result(p_row, p_column);

    for (size_type i(0); i != result.row_size(); ++i)
    {
        result[i][i] = 1;
    }

    return result;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::~Matrix()
{
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR void dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::resize(const size_type &p_row, const size_type &p_column, const value_type &p_default_value)
{
    m_matrix.resize(p_row);
    for (size_type i(0); i != p_row; ++i)
        m_matrix[i].resize(p_column, p_default_value);
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::size_type dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::row_size() const NOEXCEPT
{
    return m_matrix.size();
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::size_type dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::column_size() const NOEXCEPT
{
    return (row_size()) ? m_matrix[0].size() : 0;
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::column_type &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator[](const size_type &p_index) NOEXCEPT
{
    return m_matrix[p_index];
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::column_type const &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::operator[](const size_type &p_index) const NOEXCEPT
{
    return m_matrix[p_index];
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::column_type &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::at(const size_type &p_index)
{
    if (!row_size())
        throw std::runtime_error("row size is zero\n");

    return m_matrix[p_index];
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::column_type const &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::at(const size_type &p_index) const
{
    if (!row_size())
        throw std::runtime_error("row size is zero\n");

    return m_matrix[p_index];
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::element_allocator_type const &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::get_element_allocator() const noexcept
{
    return m_matrix[0].get_allocator();
}

template <typename Elem, typename ElementAllocator, typename ContainerAllocator>
CONSTEXPR typename dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::container_allocator_type const &dsaa::Matrix<Elem, ElementAllocator, ContainerAllocator>::get_container_allocator() const noexcept
{
    return m_matrix.get_allocator();
}

#endif //!DSAA_MATRIX_H
