// Forward declarations

namespace network
{
    namespace dns
    {
        namespace parse
        {
            struct range;
            struct mask;
        };
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__parse__name__h)
#define __drop__network__dns__parse__name__h

// Libraries

#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

// Includes

#include "network/dns/name.h"
#include "data/optional.hpp"

namespace network :: dns :: parse
{
    struct range
    {
        size_t beg;
        size_t end;
    };

    struct mask
    {
        range labels[64];
        size_t size;
    };

    data :: optional <:: network :: dns :: name> name(const char *, const size_t &, size_t &);
};

#endif
