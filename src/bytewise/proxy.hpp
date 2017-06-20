#ifndef __drop__bytewise__proxy__hpp
#define __drop__bytewise__proxy__hpp

// Includes

#include "proxy.h"

namespace bytewise
{
    // Static methods

    template <typename type, size_t index> inline auto && proxy <type, index> :: get(type && obj)
    {
        return type :: template bytewise <index, false> :: get(std :: forward <type> (obj));
    }
};

#endif
