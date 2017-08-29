// Forward declarations

namespace network
{
    namespace dns
    {
        namespace parse
        {
        };
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__parse__string__h)
#define __drop__network__dns__parse__string__h

// Libraries

#include <stddef.h>
#include <stdint.h>

// Includes

#include "network/dns/string.h"
#include "data/optional.hpp"

namespace network :: dns :: parse
{
    data :: optional <:: network :: dns :: string> string(const char *, const size_t &, size_t &);
};

#endif
