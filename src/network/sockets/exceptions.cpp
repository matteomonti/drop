// Includes

#include "exceptions.h"

namespace network :: sockets
{
    // setsockopt_failed

    const char * setsockopt_failed :: what() const noexcept
    {
        return "Setsockopt failed.";
    }

    // socket_closed

    const char * socket_closed :: what() const noexcept
    {
        return "Socket closed.";
    }

    // bind_failed

    const char * bind_failed :: what() const noexcept
    {
        return "Bind failed.";
    }

    // connect_failed

    const char * connect_failed :: what() const noexcept
    {
        return "Connect failed.";
    }

    // listen_failed

    const char * listen_failed :: what() const noexcept
    {
        return "Listen failed.";
    }

    // accept_failed

    const char * accept_failed :: what() const noexcept
    {
        return "Accept failed.";
    }

    // send_failed

    const char * send_failed :: what() const noexcept
    {
        return "Send failed.";
    }

    // timeout

    const char * timeout :: what() const noexcept
    {
        return "Timeout.";
    }

    // receive_failed

    const char * receive_failed :: what() const noexcept
    {
        return "Receive failed.";
    }
};
