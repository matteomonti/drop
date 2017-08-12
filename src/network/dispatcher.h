// Forward declarations

namespace network
{
    template <typename> class dispatcher;
};

#if !defined(__forward__) && !defined(__drop__network__dispatcher__h)
#define __drop__network__dispatcher__h

// Libraries

#include <stddef.h>
#include <mutex>
#include <memory>

// Includes

#include "packet/macros.h"
#include "packet/count.h"
#include "packet/proxy.h"
#include "packet/in.h"
#include "sockets/udp.h"

namespace network
{
    template <typename protocol> class dispatcher
    {
        class arc
        {
            // Members

            sockets :: udp _socket;

            struct
            {
                std :: mutex send;
                std :: mutex receive;
            } _mutex;

        public:

            // Constructors

            arc(const sockets :: udp &);

            // Destructor

            ~arc();

            // Getters

            const int & descriptor() const;

            // Setters

            void block(const bool &);
        };

        // Members

        std :: shared_ptr <arc> _arc;

    public:

        // Constructors

        dispatcher(const sockets :: udp &);
    };
};

#endif
