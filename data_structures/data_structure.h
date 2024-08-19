#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <cstddef>

template <typename T>
class DataStructure
{
public:
    virtual size_t size() const = 0;
    virtual bool is_empty() const = 0;
    virtual bool contains(const T& value) const = 0;

    virtual T* to_array() const = 0;
};

#endif // DATA_STRUCTURE_H
