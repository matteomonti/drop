// Forward declarations

namespace network
{
    namespace dns
    {
        namespace dump
        {
        };
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__dump__string__h)
#define __drop__network__dns__dump__string__h

// Libraries

#include <stddef.h>
#include <stdint.h>

// Includes

#include "network/dns/string.h"

namespace network :: dns :: dump
{
    void string(char *, size_t &, const :: network :: dns :: string &);
};

#endif
