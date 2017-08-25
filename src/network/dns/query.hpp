#ifndef __drop__network__dns__query__hpp
#define __drop__network__dns__query__hpp

// Includes

#include "query.h"

namespace network :: dns
{
    // Constructors

    template <typename type> query <type> :: query(const char * name, const size_t & length, const enum qclass & qclass) : _length(length), _qclass(qclass)
    {
        memcpy(this->_name, name, this->_length);
    }

    // Getters

    template <typename type> const char * query <type> :: name() const
    {
        return this->_name;
    }

    template <typename type> const size_t & query <type> :: length() const
    {
        return this->_length;
    }

    template <typename type> const enum qclass & query <type> :: qclass() const
    {
        return this->_qclass;
    }
};

#endif
