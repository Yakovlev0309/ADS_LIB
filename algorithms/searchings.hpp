#ifndef SEARCHINGS_H
#define SEARCHINGS_H

#include <cstddef>

namespace Searchings
{
// Линейный поиск
template <typename T>
size_t linear_search(T* arr, size_t size, T value);

// Бинарный поиск
template <typename T>
size_t binary_search(T* arr, size_t size, T value);
}

template <typename T>
size_t Searchings::linear_search(T* arr, size_t size, T value)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
size_t Searchings::binary_search(T* arr, size_t size, T value)
{
    if (size == 0)
    {
        return -1;
    }

    size_t left = 0;
    size_t right = size - 1;
    size_t mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (value == arr[mid])
        {
            return mid;
        }
        else if (value < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

#endif // SEARCHINGS_H
