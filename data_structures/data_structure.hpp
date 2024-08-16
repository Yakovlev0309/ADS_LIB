#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

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

#endif // DATA_STRUCTURE_HPP
