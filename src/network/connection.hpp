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

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size > 0)> *> void connection :: arc :: send(const type & target)
    {
        auto buffer = bytewise :: serialize(target);

        this->_socket.visit([&](auto && socket)
        {
            socket.send(buffer, bytewise :: traits <type> :: size);
        });
    }

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size == 0)> *> void connection :: arc :: send(const type & target)
    {
        auto buffer = bytewise :: serialize(target);
        this->send(buffer);
    }

    template <typename type, std :: enable_if_t <std :: is_same <type, bytewise :: buffer> :: value> *> type connection :: arc :: receive()
    {
        bytewise :: buffer buffer;

        this->_socket.visit([&](sockets :: tcp & socket)
        {
            char sbuffer[sizeof(uint32_t)];
            for(char * cursor = sbuffer; cursor < sbuffer + sizeof(uint32_t);)
            {
                socket.receive(cursor, 1);
                cursor++;

                bytewise :: bsize bsize(sbuffer, cursor - sbuffer);
                if(bsize.value() > -1)
                {
                    buffer.alloc(bsize.value());
                    break;
                }
            }

            for(char * cursor = buffer; cursor < buffer + buffer.size();)
                cursor += socket.receive(cursor, buffer + buffer.size() - cursor);
        });

        return buffer;
    }

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size > 0)> *> type connection :: arc :: receive()
    {
        bytewise :: block <bytewise :: traits <type> :: size> buffer;

        this->_socket.visit([&](sockets :: tcp & socket)
        {
            for(char * cursor = buffer; cursor < buffer + bytewise :: traits <type> :: size;)
                cursor += socket.receive(cursor, buffer + bytewise :: traits <type> :: size - cursor);
        });

        return bytewise :: deserialize <type> (buffer);
    }

    template <typename type, std :: enable_if_t <bytewise :: traits <type> :: enabled && (bytewise :: traits <type> :: size == 0)> *> type connection :: arc :: receive()
    {
        return bytewise :: deserialize <type> (this->receive <bytewise :: buffer> ());
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
