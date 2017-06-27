#ifndef __drop__bytewise__proxy__hpp
#define __drop__bytewise__proxy__hpp

// Includes

#include "proxy.h"

namespace bytewise
{
    // Static methods

    template <typename target, size_t index> inline auto & proxy <target, index> :: get(target & obj)
    {
        return target :: template __bytewise__ <index, false> :: get(obj);
    }

    template <typename target, size_t index> inline auto & proxy <target, index> :: get(const target & obj)
    {
        return target :: template __bytewise__ <index, false> :: get(obj);
    }
};

#endif
