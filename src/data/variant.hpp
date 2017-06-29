#ifndef __drop__data__variant__hpp
#define __drop__data__variant__hpp

// Includes

#include "variant.h"

namespace data
{
    // Private constructors

    template <typename... types> variant <types...> :: variant()
    {
    }

    // Static methods

    template <typename... types> template <typename vtype, typename... atypes, std :: enable_if_t <utils :: in <vtype, types...> :: value && std :: is_constructible <vtype, atypes...> :: value> *> inline variant <types...> variant <types...> :: construct(atypes && ... args)
    {
        variant variant;
        new (&(variant._bytes)) vtype(std :: forward <atypes> (args)...);
        return variant;
    }
}
#endif
