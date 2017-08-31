// Forward declarations includes

#include "enums.h"

// Forward declarations

namespace network
{
    namespace dns
    {
        template <qtype> class query;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__query__h)
#define __drop__network__dns__query__h

// Libraries

#include <type_traits>
#include <string>
#include <stdint.h>

// Includes

#include "data/variant.hpp"
#include "data/optional.hpp"
#include "name.h"

namespace network :: dns
{
    template <> class query <null>
    {
    };

    template <qtype type> class query
    {
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
