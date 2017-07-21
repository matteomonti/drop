// Includes

#include "tcp.h"

namespace network :: sockets
{
    // Constructors

    tcp :: tcp() : _blocking(true)
    {
        this->_descriptor = :: socket(PF_INET, SOCK_STREAM, 0);

        int optreuse = 1;
        if (:: setsockopt(this->_descriptor, SOL_SOCKET, SO_REUSEADDR, &optreuse, sizeof(int)))
            throw setsockopt_failed();
    }

    // Private constructors

    tcp :: tcp(const int & descriptor, const class address :: port & port, const address & remote) : _descriptor(descriptor), _port(port), _remote(remote), _blocking(true)
    {
    }

    // Getters

    const int & tcp :: descriptor() const
    {
        return this->_descriptor;
    }

    const address & tcp :: remote() const
    {
        assert(this->_remote);
        return this->_remote;
    }

    // Setters

    void tcp :: send_timeout(const microtimestamp & timeout)
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        struct timeval timeval;

        timeval.tv_sec = timeout / 1000000;
        timeval.tv_usec = timeout % 1000000;

        if(:: setsockopt(this->_descriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeval, sizeof(struct timeval)))
            throw setsockopt_failed();
    }

    void tcp :: receive_timeout(const microtimestamp & timeout)
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        struct timeval timeval;

        timeval.tv_sec = timeout / 1000000;
        timeval.tv_usec = timeout % 1000000;

        if(:: setsockopt(this->_descriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeval, sizeof(struct timeval)))
            throw setsockopt_failed();
    }

    void tcp :: block(const bool & value)
    {
        int flags = fcntl(this->_descriptor, F_GETFL, 0);

        if(!value)
            fcntl(this->_descriptor, F_SETFL, flags | O_NONBLOCK);
        else
            fcntl(this->_descriptor, F_SETFL, flags & (!O_NONBLOCK));

        this->_blocking = value;
    }

    // Methods

    void tcp :: bind(const class address :: port & port)
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        address address({}, port);

        if(:: bind(this->_descriptor, (const struct sockaddr *) &(const sockaddr_in &)(address), sizeof(sockaddr_in)))
            throw bind_failed();

        this->_port = port;
    }

    void tcp :: connect(const address & remote)
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        int status = :: connect(this->_descriptor, (const sockaddr *) &(const sockaddr_in &) remote, sizeof(sockaddr_in));

        if(status && (this->_blocking || errno != EINPROGRESS))
            throw connect_failed();

        this->_remote = remote;
    }

    void tcp :: listen()
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        if(:: listen(this->_descriptor, settings :: listen_buffer_size))
            throw listen_failed();
    }

    tcp tcp :: accept()
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        address remote;
        socklen_t socklen;

        int descriptor = :: accept(this->_descriptor, (struct sockaddr *) &(sockaddr_in &)(remote), &socklen);

        if(descriptor < 0)
            throw accept_failed();

        return tcp(descriptor, this->_port, remote);
    }

    size_t tcp :: send(const char * message, const size_t & size)
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        ssize_t res = :: send(this->_descriptor, message, size, 0);

        if(res < 0)
        {
            if(!(this->_blocking) && errno == EWOULDBLOCK)
                return 0;
            else if(errno == EAGAIN)
                throw (class receive_timeout){};
            else
                throw send_failed();
        }

        return (size_t) res;
    }

    size_t tcp :: receive(char * message, const size_t & size)
    {
        if(this->_descriptor < 0)
            throw socket_closed();

        ssize_t res = :: recv(this->_descriptor, message, size, 0);

        if(res < 0)
        {
            if(!(this->_blocking) && errno == EWOULDBLOCK)
                return 0;
            else if(errno == EAGAIN)
                throw (class receive_timeout){};
            else
                throw receive_failed();
        }
        else if(res == 0)
            throw connection_closed();

        return (size_t) res;
    }

    void tcp :: rethrow()
    {
        int error;
        socklen_t len = sizeof(int);

        if(:: getsockopt(this->_descriptor, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
            throw getsockopt_failed();

        if(error)
            throw connect_failed();
    }

    void tcp :: close()
    {
        :: close(this->_descriptor);
        this->_descriptor = -1;
    }
};
