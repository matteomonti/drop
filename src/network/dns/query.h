// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace network
{
    namespace dns
    {
        template <typename> class query;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__query__h)
#define __drop__network__dns__query__h

// Libraries

#include <type_traits>
#include <string>
#include <stdint.h>

// Includes

#include "types.h"
#include "data/variant.hpp"
#include "data/optional.hpp"

namespace network :: dns
{
    template <> class query <null>
    {
    };

    template <typename type> class query
    {
        // Static asserts

        static_assert(std :: is_same <type, A> :: value || std :: is_same <type, NS> :: value || std :: is_same <type, CNAME> :: value || std :: is_same <type, SOA> :: value || std :: is_same <type, WKS> :: value || std :: is_same <type, PTR> :: value || std :: is_same <type, HINFO> :: value || std :: is_same <type, MINFO> :: value || std :: is_same <type, MX> :: value || std :: is_same <type, TXT> :: value, "Invalid query type.");

        // Members

        char _name[256];
        size_t _length;
        qclass _qclass;

    public:

        // Constructors

        query(const char *, const size_t &, const qclass &);

        // Getters

        const char * name() const;
        const size_t & length() const;
        const qclass & qclass() const;
    };

    namespace parse
    {
        data :: variant <query <A>, query <NS>, query <CNAME>, query <SOA>, query <WKS>, query <PTR>, query <HINFO>, query <MINFO>, query <MX>, query <TXT>, query <null>> query(const char *, const size_t &, size_t &);
    }
}

#endif
