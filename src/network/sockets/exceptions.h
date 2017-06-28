// Forward declarations

namespace network
{
    namespace sockets
    {
        class setsockopt_failed;
    };
};

#if !defined(__forward__) && !defined(__network__sockets__exceptions__h)
#define __network__sockets__exceptions__h

// Libraries

#include <exception>

namespace network :: sockets
{
    class setsockopt_failed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class socket_closed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class bind_failed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class connect_failed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class listen_failed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class accept_failed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class send_failed : public std :: exception
    {
        const char * what() const noexcept;
    };

    class timeout : public std :: exception
    {
        const char * what() const noexcept;
    };

    class receive_failed : public std :: exception
    {
        const char * what() const noexcept;
    };
}

#endif
