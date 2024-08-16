#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include "linked_list.hpp"

template <typename T>
class Queue
{
public:
    Queue();

    void push(const T& value);
    void pop();

    T peek() const;

    size_t size() const { return data.size(); }
    bool is_empty() const { return data.is_empty(); }
    bool contains(const T& value) const { return data.contains(value); }

    T* to_array() const { return data.to_array(); }

private:
    LinkedList<T> data;
};

// ----------

template <typename T>
Queue<T>::Queue() {}

template <typename T>
void Queue<T>::push(const T& value)
{
    data.append_back(value);
    return;
}

template <typename T>
void Queue<T>::pop()
{
    data.remove_back();
}

template <typename T>
T Queue<T>::peek() const
{
    if (size() > 0)
    {
        return data[data.size() - 1];
    }
    else
    {
        return NULL;
    }
}

#endif // QUEUE_H
