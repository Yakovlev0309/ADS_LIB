#ifndef SORTINGS_H
#define SORTINGS_H

#include <cstddef>
#include <algorithm>
#include <vector>

namespace Sortings
{
// Пузырьковая сотрировка
template <typename T>
void bubble_sort(T* arr, size_t size);

// Сортировка выбором
template <typename T>
void selection_sort(T* arr, size_t size);

// Сортировка вставками
template <typename T>
void insertion_sort(T* arr, size_t size);

// Быстрая сортировка
template <typename T>
void q_sort(T* arr, size_t begin, size_t end);
template <typename T>
void quick_sort(T* arr, size_t size);

// Сортировка слиянием
template <typename T>
void m_sort(T* arr, size_t size, std::vector<T>& buffer, size_t l, size_t r);
template <typename T>
void merge_sort(T* arr, size_t size);
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
void Sortings::insertion_sort(T* arr, size_t size)
{
    for (size_t i = 1; i < size; ++i)
    {
        T next = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > next)
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = next;
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

template <typename T>
void Sortings::m_sort(T* arr, size_t size, std::vector<T>& buffer, size_t l, size_t r)
{
    if (l < r)
    {
        size_t mid = (l + r) / 2;
        m_sort(arr, size, buffer, l, mid);
        m_sort(arr, size, buffer, mid + 1, r);

        size_t k = l;
        for (size_t i = l, j = mid + 1; i <= mid || j <= r; )
        {
            if (j > r || (i <= mid && arr[i] < arr[j]))
            {
                buffer[k] = arr[i];
                ++i;
            }
            else
            {
                buffer[k] = arr[j];
                ++j;
            }
            ++k;
        }

        for (; l <= r; ++l)
        {
            arr[l] = buffer[l];
        }
    }
}
template <typename T>
void Sortings::merge_sort(T* arr, size_t size)
{
    if (size > 0)
    {
        std::vector<T> buffer(size);
        m_sort(arr, size, buffer, 0, size - 1);
    }
}

#endif // SORTINGS_H
