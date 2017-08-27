// Includes

#include "string.h"

namespace network :: dns
{
    // Settings

    constexpr size_t string :: settings :: max_length;

    // Constructors

    string :: string() : _length(0)
    {
    }

    string :: string(const char * value, const size_t & length) : _length(length)
    {
        memcpy(this->_value, value, this->_length);
        this->_value[this->_length] = '\0';
    }

    string :: string(const char * value) : _length(strlen(value))
    {
        memcpy(this->_value, value, this->_length);
        this->_value[this->_length] = '\0';
    }

    // Getters

    const size_t & string :: length() const
    {
        return this->_length;
    }

    // Casting

    string :: operator const char * () const
    {
        return this->_value;
    }
};
