#ifndef __drop__network__dispatcher__hpp
#define __drop__network__dispatcher__hpp

// Includes

#include "dispatcher.h"

namespace network
{
    // proxy

    // Static methods

    template <typename protocol> template <typename... types> template <typename ptype> inline void dispatcher <protocol> :: proxy <:: network :: packet :: fields <types...>> :: send(arc & arc, const address & remote, const types & ... fields)
    {
        arc.template send <ptype> (remote, fields...);
    }

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
        typename :: network :: packet :: template count <protocol> :: type index = ptype :: index;
        auto message = bytewise :: serialize <bytewise :: options :: pad :: template beg <sizeof(index)>> (((types) fields)...);
        bytewise :: endianess :: translate(reinterpret_cast <char (&)[sizeof(index)]> (message), reinterpret_cast <const char (&)[sizeof(index)]> (index));

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
        proxy <typename ptype :: fields> :: template send <ptype> (*(this->_arc), remote, fields...);
    }
};

#endif
