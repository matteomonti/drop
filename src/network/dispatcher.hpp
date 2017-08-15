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

    // Methods

    template <typename protocol> template <typename ptype, typename... types> void dispatcher <protocol> :: arc :: send(const address & remote, const types & ... fields)
    {
        uint8_t index = ptype :: index;
        auto message = bytewise :: serialize(index, ((types) fields)...);

        this->_socket.send(remote, message, message.size());
    }

    // dispatcher

    // Constructors

    template <typename protocol> dispatcher <protocol> :: dispatcher(const sockets :: udp & socket) : _arc(new arc(socket))
    {
    }

    // Methods

    template <typename protocol> template <typename ptype, typename... types, std :: enable_if_t <dispatcher <protocol> :: template packet <ptype> :: template is_callable <types...> :: value> *> void dispatcher <protocol> :: send(const address & remote, const types & ... fields)
    {
        this->_arc->template send <ptype> (remote, fields...);
    }
};

#endif
