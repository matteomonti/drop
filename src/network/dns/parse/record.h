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

#if !defined(__forward__) && !defined(__drop__network__dns__parse__record__h)
#define __drop__network__dns__parse__record__h

// Includes

#include "name.h"
#include "string.h"
#include "network/dns/record.h"
#include "data/variant.hpp"

namespace network :: dns :: parse
{
    data :: variant <record <A>, record <NS>, record <CNAME>, record <SOA>, record <WKS>, record <PTR>, record <HINFO>, record <MINFO>, record <MX>, record <TXT>, record <null>> record(const char *, const size_t &, size_t &);
};

#endif
