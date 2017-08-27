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
#include "name.h"

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

        name _name;
        qclass _qclass;

    public:

        // Constructors

        query(const name &, const qclass &);

        // Getters

        const name & name() const;
        const qclass & qclass() const;
    };
}

#endif
