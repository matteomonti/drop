// Forward declarations

namespace network
{
    namespace acceptors
    {
        class tcp;
    };
};

#if !defined(__forward__) && !defined(__drop__network__acceptors__tcp__h)
#define __drop__network__acceptors__tcp__h

// Libraries

#include <stdint.h>

// Includes

#include "network/sockets/tcp.h"
#include "network/connection.hpp"

namespace network :: acceptors
{
    class tcp
    {
    public:

        // Nested classes

        class sync
        {
            // Members

            sockets :: tcp _socket;

        public:
            
            // Constructors

            sync(const uint16_t &);

            // Methods

            connection accept();
        };
    };
};

#endif
