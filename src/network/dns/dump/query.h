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

#if !defined(__forward__) && !defined(__drop__network__dns__dump__query__h)
#define __drop__network__dns__dump__query__h

// Libraries

#include <stdint.h>
#include <type_traits>

// Includes

#include "name.h"
#include "network/dns/query.hpp"

namespace network :: dns :: dump
{
    template <qtype type, typename std :: enable_if_t <type != null> * = nullptr> void query(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: query <type> &);
};
#endif
