// Forward declarations

namespace network
{
    namespace sockets
    {
        class tcp;
    };
};

#if !defined(__forward__) && !defined(__network__sockets__tcp__h)
#define __network__sockets__tcp__h

// Libraries

#include <arpa/inet.h>
#include <unistd.h>
#include <stddef.h>
#include <assert.h>

// Includes

#include "exceptions.h"
#include "network/address.h"
#include "socket.h"
#include "os/signal.h"

namespace network :: sockets
{
    class tcp
    {
    public:

        // Settings

        struct settings
        {
            static constexpr size_t listen_buffer_size = 128;
        };

    private:

        // Members

        int _descriptor;
        class address :: port _port;
        address _remote;

    public:

        // Constructors

        tcp();

    private:

        // Private constructors

        tcp(const int &, const class address :: port &, const address &);

    public:

        // Getters

        const int & descriptor() const;
        const address & remote() const;

        // Setters

        void send_timeout(const microtimestamp &);
        void receive_timeout(const microtimestamp &);

        // Methods

        void bind(const class address :: port &);
        void connect(const address &);

        void listen();
        tcp accept();

        void send(const char *, const size_t &);
        size_t receive(char *, const size_t &);

        void close();
    };
};

#endif
