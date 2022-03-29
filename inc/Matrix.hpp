#pragma once

#include <array>
#include <memory>
#include <iostream>
#include <cstring>

template <typename T>
class Matrix
{
public:
    Matrix() : Matrix(0, 0) {}

    Matrix(size_t rows, size_t columns) : _rows(rows),
                                          _columns(columns),
                                          _size(rows * columns),
                                          _buffer(std::make_unique<T[]>(rows * columns))
    {
        std::memset(_buffer.get(), 0, sizeof(T) * _size);
    }

    Matrix(Matrix const &other)
    {
        *this = other;
    }

    Matrix(Matrix &&other)
    {
        *this = std::move(other);
    }

    /*--------------------------------------------------------------------------------------------*/

    Matrix &operator=(Matrix const &other)
    {
        if (this == &other)
        {
            return *this;
        }
        this->~Matrix();
        _rows = other._rows;
        _columns = other._columns;
        _buffer = std::make_unique<T[]>(other._rows * other._columns);
        _size = other._size;
        for (size_t i = 0; i < _size; i++)
        {
            _buffer[i] = other._buffer[i];
        }
        return *this;
    }

    Matrix &operator=(Matrix &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        _buffer = other._buffer;
        other._buffer = nullptr;
        _rows = other._rows;
        other._rows = 0;
        _columns = other._columns;
        other._columns = 0;
        _size = other._size;
        other._size = 0;
        return *this;
    }

    T &operator()(size_t x, size_t y)
    {
        return _buffer[x * _columns + y];
    }

    T const &operator()(size_t x, size_t y) const
    {
        return _buffer[x * _columns + y];
    }

    /*--------------------------------------------------------------------------------------------*/

    size_t size() const
    {
        return _size;
    }

    void print() const
    {
        for (size_t i = 0; i < _size; i++)
        {
            std::cout << _buffer[i] << (((i + 1) % _columns) ? '\t' : '\n');
        }
    }

private:
    size_t _rows;
    size_t _columns;
    size_t _size;
    std::unique_ptr<T[]> _buffer;
};

// buffer = std::make_unique<T[]>( size );