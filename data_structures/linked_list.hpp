#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class LinkedListNode
{
public:
    LinkedListNode();
    LinkedListNode(const T& value);
    LinkedListNode(const T& value, LinkedListNode* next);

    T value;
    LinkedListNode*  next;
};

template <typename T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(const std::initializer_list<T>& values);

    // FIXME уже добавленные emplace'ы работают неправильно
    template <typename... Args>
    void emplace_back(Args&&... args);
    template <typename... Args>
    void emplace_front(Args&&... args);
    // TODO добавить emplace'ы

    void append_back(const T& value);
    void append_front(const T& value);
    void append_after(LinkedListNode<T>* prev, const T& value);
    void append_before(LinkedListNode<T>* next, const T& value);
    void append_by_index(size_t index, const T& value);

    void remove_back();
    void remove_front();

    void clear();

    size_t size() const { return sz; }
    bool is_empty() const { return sz > 0 ? false : true; };
    bool contains(const T& value) const;
    LinkedListNode<T>* head() const { return _head; }

    T operator[](size_t index) const;

    T* to_array() const;

private:
    LinkedListNode<T>* _head;
    size_t sz;
};

// ----------

template <typename T>
LinkedListNode<T>::LinkedListNode()
{
    value = T();
    next = nullptr;
}

template <typename T>
LinkedListNode<T>::LinkedListNode(const T& value)
{
    this->value = value;
    next = nullptr;
}

template <typename T>
LinkedListNode<T>::LinkedListNode(const T& value, LinkedListNode<T>* next)
{
    this->value = value;
    this->next = next;
}

// ----------

template <typename T>
LinkedList<T>::LinkedList()
{
    _head = nullptr;
    sz = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& values)
{
    _head = nullptr;
    sz = 0;
    for (const T& value : values)
    {
        append_back(value);
    }
}

template <typename T>
template <typename... Args>
void LinkedList<T>::emplace_back(Args&&... args)
{
    if (_head == nullptr)
    {
        _head = new LinkedListNode<T>(std::forward<Args>(args)...);
    }
    else
    {
        LinkedListNode<T>* current = _head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new LinkedListNode<T>(std::forward<Args>(args)...);
    }

    sz += 1;
}

template <typename T>
template <typename... Args>
void LinkedList<T>::emplace_front(Args&&... args)
{
    LinkedListNode<T>* node = new LinkedListNode<T>(std::forward<Args>(args)...);

    if (_head != nullptr)
    {
        node->next = _head;
    }
    _head = node;

    sz += 1;
}

template <typename T>
void LinkedList<T>::append_back(const T& value)
{
    LinkedListNode<T>* node = new LinkedListNode<T>(value);

    if (_head == nullptr)
    {
        _head = node;
    }
    else
    {
        LinkedListNode<T>* current = _head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = node;
    }

    sz += 1;
}

template <typename T>
void LinkedList<T>::append_front(const T& value)
{
    LinkedListNode<T>* node = new LinkedListNode<T>(value);

    if (_head != nullptr)
    {
        node->next = _head;
    }
    _head = node;

    sz += 1;
}

template <typename T>
void LinkedList<T>::append_after(LinkedListNode<T>* prev, const T& value)
{
    if (prev == nullptr)
    {
        throw std::invalid_argument("LinkedListNode pointer value is nullptr.");
    }

    LinkedListNode<T>* node = new LinkedListNode<T>(value);

    node->next = prev->next;
    prev->next = node;

    sz += 1;
}

template <typename T>
void LinkedList<T>::append_before(LinkedListNode<T>* next, const T& value)
{
    if (next == nullptr)
    {
        throw std::invalid_argument("LinkedListNode pointer value is nullptr.");
    }

    LinkedListNode<T>* node = new LinkedListNode<T>(value);

    LinkedListNode<T>* current = _head;
    while (current->next != next)
    {
        current = current->next;
    }

    current->next = node;
    node->next = next;

    sz += 1;
}

template <typename T>
void LinkedList<T>::append_by_index(size_t index, const T& value)
{
    if (index < 0 || index > sz)
    {
        throw std::out_of_range("LinkedList index out of range.");
    }

    LinkedListNode<T>* node = new LinkedListNode<T>(value);

    if (_head != nullptr)
    {
        size_t i = 0;
        LinkedListNode<T>* current = _head;
        while (i < index - 1)
        {
            current = current->next;
            i++;
        }

        node->next = current->next;
        current->next = node;
    }
    else
    {
        _head = node;
    }

    sz += 1;
}

template <typename T>
void LinkedList<T>::remove_back()
{
    if (sz > 0)
    {
        LinkedListNode<T>* current = _head;
        for (size_t i = 1; i < sz - 1; ++i)
        {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;

        sz -= 1;
    }
}

template <typename T>
void LinkedList<T>::remove_front()
{
    if (sz > 0)
    {
        LinkedListNode<T>* next = _head->next;
        delete _head;
        _head = next;

        sz -= 1;
    }
}

template <typename T>
void LinkedList<T>::clear()
{
    if (sz > 0)
    {
        LinkedListNode<T>* current = _head;
        for (size_t i = 0; i < sz; ++i)
        {

        }

        sz = 0;
    }
}

template <typename T>
bool LinkedList<T>::contains(const T &value) const
{
    LinkedListNode<T>* current = _head;
    while (current->next != nullptr)
    {
        if (current->value == value)
        {
            return true;
        }
        current = current->next;
    }
    if (current->value == value)
    {
        return true;
    }
    return false;
}

template<typename T>
T LinkedList<T>::operator[](size_t index) const
{
    if (index < 0 || index > sz)
    {
        throw std::out_of_range("LinkedList index out of range.");
    }

    size_t i = 0;
    LinkedListNode<T>* current = _head;
    while (i < index)
    {
        current = current->next;
        i++;
    }

    return current->value;
}

template <typename T>
T* LinkedList<T>::to_array() const
{
    T* arr = new T[sz];
    LinkedListNode<T>* current = _head;
    for (size_t i = 0; i < sz; ++i)
    {
        arr[i] = current->value;
        current = current->next;
    }
    return arr;
}

#endif // LINKEDLIST_H
