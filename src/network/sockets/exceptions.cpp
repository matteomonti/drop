// Includes

#include "exceptions.h"

namespace network :: sockets
{
    // setsockopt_failed

    const char * getsockopt_failed :: what() const noexcept
    {
        return "Getsockopt failed.";
    }

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

    // send_timeout

    const char * send_timeout :: what() const noexcept
    {
        return "Send timeout.";
    }

    // send_failed

    const char * send_failed :: what() const noexcept
    {
        return "Send failed.";
    }

    // timeout

    const char * receive_timeout :: what() const noexcept
    {
        return "Receive timeout.";
    }

    // receive_failed

    const char * receive_failed :: what() const noexcept
    {
        return "Receive failed.";
    }

    // connect_timeout

    const char * connect_timeout :: what() const noexcept
    {
        return "Connect timeout.";
    }

    // connection_closed

    const char * connection_closed :: what() const noexcept
    {
        return "Connection closed by remote endpoint.";
    }
};
