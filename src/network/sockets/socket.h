// Forward declarations

namespace network
{
    namespace sockets
    {
        class socket;
    };
};

#if !defined(__forward__) && !defined(__drop__network__sockets__socket__h)
#define __drop__network__sockets__socket__h

// Libraries

#include <stddef.h>

// Forward includes

#define __forward__
#include "time/time.h"
#undef __forward__

namespace network :: sockets
{
    class socket
    {
    public:

        // Destructor

        virtual ~socket();

        // Setters

        virtual void send_timeout(const microtimestamp &) = 0;
        virtual void receive_timeout(const microtimestamp &) = 0;

        // Getters

        virtual const int & descriptor() const = 0;

        // Methods

        virtual void send(const char *, const size_t &) = 0;
        virtual size_t receive(char *, const size_t &) = 0;

        virtual void close() = 0;
    };
};

#endif
