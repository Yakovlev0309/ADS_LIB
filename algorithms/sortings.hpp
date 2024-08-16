#ifndef SORTINGS_H
#define SORTINGS_H

#include <cstddef>
#include <algorithm>

namespace Sortings
{
// Пузырьковая сотрировка
template <typename T>
void bubble_sort(T* arr, size_t size);

// Сортировка выбором
template <typename T>
void selection_sort(T* arr, size_t size);

// Быстрая сортировка
template <typename T>
void q_sort(T* arr, size_t begin, size_t end);
template <typename T>
void quick_sort(T* arr, size_t size);
}

template <typename T>
void Sortings::bubble_sort(T* arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = i + 1; j < size; ++j)
        {
            if (arr[j] < arr[i])
            {
                std::swap(arr[j], arr[i]);
            }
        }
    }
}

template <typename T>
void Sortings::selection_sort(T* arr, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < size; ++j)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

template <typename T>
void Sortings::q_sort(T* arr, size_t begin, size_t end)
{
    if (begin >= end)
        return;

    size_t pivot_index = begin;
    for (size_t i = begin + 1; i <= end; i++)
    {
        if (arr[i] < arr[begin])
        {
            std::swap(arr[++pivot_index], arr[i]);
        }
    }

    std::swap(arr[begin], arr[pivot_index]);

    if (pivot_index > begin)
    {
        q_sort(arr, begin, pivot_index - 1);
    }
    if (end > pivot_index + 1)
    {
        q_sort(arr, pivot_index + 1, end);
    }
}
template<typename T>
void Sortings::quick_sort(T* arr, size_t size)
{
    if (size > 0)
    {
        q_sort(arr, 0, size - 1);
    }
}

#endif // SORTINGS_H
