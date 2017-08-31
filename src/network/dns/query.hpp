#ifndef __drop__network__dns__query__hpp
#define __drop__network__dns__query__hpp

// Includes

#include "query.h"

namespace network :: dns
{
    // Constructors

    template <qtype type> query <type> :: query(const class name & name, const enum qclass & qclass) : _name(name), _qclass(qclass)
    {
    }

    // Getters

    template <qtype type> const name & query <type> :: name() const
    {
        return this->_name;
    }

    template <qtype type> const enum qclass & query <type> :: qclass() const
    {
        return this->_qclass;
    }
};

#endif
