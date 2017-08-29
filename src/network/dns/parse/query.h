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

#if !defined(__forward__) && !defined(__drop__network__dns__parse__query__h)
#define __drop__network__dns__parse__query__h

// Includes

#include "name.h"
#include "network/dns/query.hpp"
#include "data/variant.hpp"

namespace network :: dns :: parse
{
    data :: variant <query <A>, query <NS>, query <CNAME>, query <SOA>, query <WKS>, query <PTR>, query <HINFO>, query <MINFO>, query <MX>, query <TXT>, query <null>> query(const char *, const size_t &, size_t &);
};

#endif
