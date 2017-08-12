#ifndef __drop__network__dispatcher__hpp
#define __drop__network__dispatcher__hpp

// Includes

#include "dispatcher.h"

namespace network
{
    // arc

    // Constructors

    template <typename protocol> dispatcher <protocol> :: arc :: arc(const sockets :: udp & socket) : _socket(socket)
    {
    }

    // Destructor

    template <typename protocol> dispatcher <protocol> :: arc :: ~arc()
    {
        this->_socket.close();
    }

    // Getters

    template <typename protocol> const int & dispatcher <protocol> :: arc :: descriptor() const
    {
        return this->_socket.descriptor();
    }

    // Setters

    template <typename protocol> void dispatcher <protocol> :: arc :: block(const bool & value)
    {
        this->_socket.block(value);
    }

    // dispatcher

    // Constructors

    template <typename protocol> dispatcher <protocol> :: dispatcher(const sockets :: udp & socket) : _arc(new arc(socket))
    {
    }
};

#endif
