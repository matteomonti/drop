#ifndef __drop__bytewise__block__hpp
#define __drop__bytewise__block__hpp

// Includes

#include "block.h"

namespace bytewise
{
    // Constructors

    template <size_t alloc> block <alloc> :: block()
    {
    }

    template <size_t alloc> block <alloc> :: block(const char * bytes)
    {
        mempcy(this->_bytes, bytes, alloc);
    }

    template <size_t alloc> block <alloc> :: block(const block & that) : block(that._bytes)
    {
    }

    // Operators

    template <size_t alloc> char & block <alloc> :: operator [] (const size_t & index)
    {
        return this->_bytes[index];
    }

    template <size_t alloc> const char & block <alloc> :: operator [] (const size_t & index) const
    {
        return this->_bytes[index];
    }

    // Casting

    template <size_t alloc> block <alloc> :: operator array & ()
    {
        return this->_bytes;
    }

    template <size_t alloc> block <alloc> :: operator const array & () const
    {
        return this->_bytes;
    }

    template <size_t alloc> block <alloc> :: operator char * ()
    {
        return this->_bytes;
    }

    template <size_t alloc> block <alloc> :: operator const char * () const
    {
        return this->_bytes;
    }
};

#endif
