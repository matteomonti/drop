// Forward declarations

namespace network
{
    namespace connectors
    {
        class tcp;
    };
};

#if !defined(__forward__) && !defined(__drop__network__connectors__tcp__h)
#define __drop__network__connectors__tcp__h

// Includes

#include "network/address.h"
#include "network/sockets/tcp.h"
#include "network/connection.hpp"

namespace network :: connectors
{
    class tcp
    {
    public:

        // Nested classes

        class sync
        {
        public:

            // Static methods

            static connection connect(const address &);
        };
    };
};

#endif
