#ifndef __drop__network__connection__hpp
#define __drop__network__connection__hpp

// Includes

#include "connection.h"

namespace network
{
    // arc

    // Constructors

    template <typename type> connection :: arc :: arc(const type & socket) : _socket(decltype(_socket) :: construct <type> (socket))
    {
    }

    // Methods

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled || std :: is_same <type, bytewise :: buffer> :: value> *> void connection :: arc :: send(const type & target)
    {
        this->send_setup(target);
        while(this->send_step() != completed);
    }

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled || std :: is_same <type, bytewise :: buffer> :: value> *> type connection :: arc :: receive()
    {
        this->receive_setup(bytewise :: traits <type> :: size);
        while(this->receive_step() != completed);
        return this->receive_finalize <type> ();
    }

    // Private methods

    template <typename type, std :: enable_if_t <(bytewise :: traits <type> :: enabled && bytewise :: traits <type> :: size > 0)> *> void connection :: arc :: send_setup(const type & target)
    {
        this->_write.buffer.data = bytewise :: buffer((const char *) bytewise :: serialize(target), bytewise :: traits <type> :: size);
        this->_write.ssize = 0;
        this->_write.cursor = 0;
    }

    template <typename type, std :: enable_if_t <(bytewise :: traits <type> :: enabled && bytewise :: traits <type> :: size == 0)> *> void connection :: arc :: send_setup(const type & target)
    {
        this->send_setup(bytewise :: serialize(target));
    }

    template <typename type, std :: enable_if_t <std :: is_same <type, bytewise :: buffer> :: value> *> type connection :: arc :: receive_finalize()
    {
        return this->_read.buffer.data;
    }

    template <typename type, std :: enable_if_t <(bytewise :: traits <type> :: enabled && bytewise :: traits <type> :: size > 0)> *> type connection :: arc :: receive_finalize()
    {
        return bytewise :: deserialize <type> (reinterpret_cast <bytewise :: block <bytewise :: traits <type> :: size> &> (* (char *)(this->_read.buffer.data)));
    }

    template <typename type, std :: enable_if_t <(bytewise :: traits <type> :: enabled && bytewise :: traits <type> :: size == 0)> *> type connection :: arc :: receive_finalize()
    {
        return bytewise :: deserialize <type> (this->_read.buffer.data);
    }

    // connection

    // Constructors

    template <typename type, utils :: enable_in_t <type, sockets :: tcp> *> connection :: connection(const type & socket) : _arc(new arc(socket))
    {
    }

    // Methods

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled || std :: is_same <type, bytewise :: buffer> :: value> *> void connection :: send(const type & target)
    {
        this->_arc->send(target);
    }

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled || std :: is_same <type, bytewise :: buffer> :: value> *> type connection :: receive()
    {
        return this->_arc->receive <type> ();
    }
}

#endif
