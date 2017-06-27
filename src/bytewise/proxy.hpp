#ifndef __drop__bytewise__proxy__hpp
#define __drop__bytewise__proxy__hpp

// Includes

#include "proxy.h"

namespace bytewise
{
    // Static methods

    template <typename target, size_t index> template <typename otype, utils :: enable_in_t <otype, target> *> inline auto && proxy <target, index> :: get(otype && obj)
    {
        return target :: template __bytewise__ <index, false> :: get(obj);
    }
};

#endif
