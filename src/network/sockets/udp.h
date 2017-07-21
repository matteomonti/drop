// Forward declarations

namespace network
{
    namespace sockets
    {
        class udp;
    };
};

#if !defined(__forward__) && !defined(__drop__network__sockets__udp__h)
#define __drop__network__sockets__udp__h

// Libraries

#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>

// Includes

#include "exceptions.h"
#include "network/address.h"
#include "chrono/time.h"

namespace network :: sockets
{
    class udp
    {
    public:

        // Settings

        struct settings
        {
            static constexpr size_t mtu = 2048;
        };

        // Nested classes

        class packet
        {
            // Friends

            friend class udp;

            // Members

            address _remote;
            char _message[settings :: mtu + 1];
            ssize_t _size;

        public:

            // Getters

            const address & remote() const;
            const char * message() const;
            const size_t & size() const;

            // Casting

            operator bool() const;
        };

    private:
        // Members

        int _descriptor;
        class address :: port _port;
        bool _blocking;

    public:

        // Constructors

        udp();

        // Getters

        const int & descriptor() const;

        // Setters

        void send_timeout(const microtimestamp &);
        void receive_timeout(const microtimestamp &);

        void block(const bool &);

        // Methods

        void bind(const class address :: port &);

        bool send(const address &, const char *, const size_t &);
        packet receive();

        void close();
    };
};

#endif
