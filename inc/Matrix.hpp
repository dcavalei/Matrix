#pragma once

#include <array>
#include <memory>
#include <iostream>
#include <cstring>

template <typename T>
class Matrix
{
public:
    Matrix();
    Matrix(size_t rows, size_t columns);
    Matrix(Matrix const &other);
    Matrix(Matrix &&other);

    /*--------------------------------------------------------------------------------------------*/

    Matrix operator+(Matrix const &other) const;
    Matrix &operator+=(Matrix const &other);
    Matrix operator-(Matrix const &other) const;
    Matrix &operator-=(Matrix const &other);
    Matrix operator*(T const &value) const;
    Matrix &operator*=(T const &value);
    Matrix operator*(Matrix const &other) const;
    Matrix &operator*=(Matrix const &other);
    Matrix &operator=(Matrix const &other);
    Matrix &operator=(Matrix &&other);
    T &operator()(size_t x, size_t y);
    T const &operator()(size_t x, size_t y) const;

    /*--------------------------------------------------------------------------------------------*/

    size_t getRows() const;
    size_t getColumns() const;
    size_t size() const;
    void print() const;
    void random(T (*func)());
    bool isEqualDim(Matrix const &other) const;
    bool isMultipliableBy(Matrix const &other) const;
    Matrix transpose() const;

private:
    size_t _rows;
    size_t _columns;
    size_t _size;
    std::unique_ptr<T[]> _buffer;
};

template <typename T>
Matrix<T>::Matrix() : Matrix(0, 0) {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : _rows(rows),
                                                 _columns(columns),
                                                 _size(rows * columns),
                                                 _buffer(std::make_unique<T[]>(rows * columns))
{
    std::memset(_buffer.get(), 0, sizeof(T) * _size);
}

template <typename T>
Matrix<T>::Matrix(Matrix const &other)
{
    *this = other;
}

template <typename T>
Matrix<T>::Matrix(Matrix &&other)
{
    *this = std::move(other);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(Matrix const &other) const
{
    if (isEqualDim(other) == false)
    {
        throw std::logic_error("Matrix dimension not equal!");
    }

    Matrix tmp(*this);

    for (size_t i = 0; i < tmp._size; i++)
    {
        tmp._buffer[i] -= other._buffer[i];
    }
    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(Matrix const &other)
{
    if (isEqualDim(other) == false)
    {
        throw std::logic_error("Matrix dimension not equal!");
    }

    for (size_t i = 0; i < _size; i++)
    {
        _buffer[i] -= other._buffer[i];
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T const &value) const
{
    Matrix ret(*this);

    for (size_t i = 0; i < _size; i++)
    {
        ret._buffer[i] *= value;
    }
    return (ret);
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(T const &value)
{
    for (size_t i = 0; i < _size; i++)
    {
        _buffer[i] *= value;
    }
    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(Matrix const &other) const
{
    if (isMultipliableBy(other) == false)
    {
        throw std::logic_error("_columns != other._rows");
    }

    Matrix ret(_rows, other._columns); //  [n, p] = [n, m] . [m, p]

    for (size_t i = 0; i < _rows; i++)
    {
        for (size_t j = 0; j < other._columns; j++)
        {
            for (size_t k = 0; k < other._rows; k++)
            {
                ret(i, j) += operator()(i, k) * other(k, j);
            }
        }
    }
    return (ret);
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(Matrix const &other)
{
    if (isMultipliableBy(other) == false)
    {
        throw std::logic_error("_columns != other._rows");
    }

    return (*this = *this * other);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(Matrix const &other) const
{
    if (isEqualDim(other) == false)
    {
        throw std::logic_error("Matrix dimension not equal!");
    }

    Matrix tmp(*this);

    for (size_t i = 0; i < tmp._size; i++)
    {
        tmp._buffer[i] += other._buffer[i];
    }
    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(Matrix const &other)
{
    if (isEqualDim(other) == false)
    {
        throw std::logic_error("Matrix dimension not equal!");
    }

    for (size_t i = 0; i < _size; i++)
    {
        _buffer[i] += other._buffer[i];
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix const &other)
{
    if (this == &other)
    {
        return *this;
    }

    _rows = other._rows;
    _columns = other._columns;
    _size = other._size;
    _buffer = std::make_unique<T[]>(other._size);
    for (size_t i = 0; i < _size; i++)
    {
        _buffer[i] = other._buffer[i];
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&other)
{
    if (this == &other)
    {
        return *this;
    }

    _rows = other._rows;
    other._rows = 0;
    _columns = other._columns;
    other._columns = 0;
    _size = other._size;
    other._size = 0;
    _buffer = std::move(other._buffer);
    return *this;
}

template <typename T>
T &Matrix<T>::operator()(size_t x, size_t y)
{
    return _buffer[x * _columns + y];
}

template <typename T>
T const &Matrix<T>::operator()(size_t x, size_t y) const
{
    return _buffer[x * _columns + y];
}

template <typename T>
size_t Matrix<T>::getRows() const
{
    return _rows;
}

template <typename T>
size_t Matrix<T>::getColumns() const
{
    return _columns;
}

template <typename T>
size_t Matrix<T>::size() const
{
    return _size;
}

template <typename T>
void Matrix<T>::print() const
{
    for (size_t i = 0; i < _size; i++)
    {
        std::cout << _buffer[i] << (((i + 1) % _columns) ? '\t' : '\n');
    }
}

template <typename T>
void Matrix<T>::random(T (*func)())
{
    for (size_t i = 0; i < _size; i++)
    {
        _buffer[i] = func();
    }
}

template <typename T>
bool Matrix<T>::isEqualDim(Matrix const &other) const
{
    return (_rows == other._rows && _columns == other._columns);
}

template <typename T>
bool Matrix<T>::isMultipliableBy(Matrix const &other) const
{
    return (_columns == other._rows);
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix ret(_columns, _rows);

    for (size_t x = 0; x < _rows; x++)
    {
        for (size_t y = 0; y < _columns; y++)
        {
            ret(y, x) = operator()(x, y);
        }
    }

    return ret;
}