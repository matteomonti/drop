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

#if !defined(__forward__) && !defined(__drop__network__dns__dump__name__h)
#define __drop__network__dns__dump__name__h

// Libraries

#include <stdint.h>
#include <string.h>

// Includes

#include "data/hashtable.hpp"
#include "network/dns/name.h"

namespace network :: dns :: dump
{
    void name(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: name &);
};

#endif
