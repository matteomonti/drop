// Includes

#include "name.h"

namespace network :: dns
{
    // Settings

    constexpr size_t name :: settings :: max_length;

    // Constructors

    name :: name(const char * name, const size_t & length) : _length(length)
    {
        memcpy(this->_name, name, this->_length);
        this->_name[this->_length] = '\0';
    }

    name :: name(const char * name) : _length(strlen(name))
    {
        memcpy(this->_name, name, this->_length);
        this->_name[this->_length] = '\0';
    }

    // Getters

    const size_t & name :: length() const
    {
        return this->_length;
    }

    // Casting

    name :: operator const char * () const
    {
        return this->_name;
    }
};
