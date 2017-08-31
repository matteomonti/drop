// Includes

#include "bitmask.h"

namespace network :: dns
{
    // Constructors

    bitmask :: bitmask(const char * mask, const size_t & size) : _size(size)
    {
        memcpy(this->_mask, mask, this->_size);
    }

    // Getters

    const size_t & bitmask :: size() const
    {
        return this->_size;
    }

    // Operators

    bool bitmask :: operator [] (const size_t & index) const
    {
        size_t byte = index / 8;

        if(byte > this->_size)
            return false;

        size_t bit = index % 8;
        return this->_mask[byte] & (1 << (7 - bit));
    }

    // Casting

    bitmask :: operator const char * () const
    {
        return (const char *) this->_mask;
    }
};
