#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "linked_list.hpp"

template <typename T>
class Stack
{
public:
    Stack();

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
Stack<T>::Stack() {}

template <typename T>
void Stack<T>::push(const T& value)
{
    // data.append_back(value);
    data.append_front(value);
}

template <typename T>
void Stack<T>::pop()
{
    // data.remove_back();
    data.remove_front();
}

template <typename T>
T Stack<T>::peek() const
{
    if (size() > 0)
    {
        return data.head()->value;
    }
    else
    {
        return NULL;
    }
}

#endif // STACK_H
