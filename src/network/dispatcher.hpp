#ifndef __drop__network__dispatcher__hpp
#define __drop__network__dispatcher__hpp

// Includes

#include "dispatcher.h"

namespace network
{
    // wrong_header

    template <typename protocol> const char * dispatcher <protocol> :: wrong_header :: what() const noexcept
    {
        return "Wrong packet header.";
    }

    // fproxy

    // Static methods

    template <typename protocol> template <typename ptype> template <typename... types> inline void dispatcher <protocol> :: packet <ptype> :: fproxy <:: network :: packet :: fields <types...>> :: send(arc & arc, const address & remote, const types & ... fields)
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

    template <typename protocol> template <typename ptype, typename... ptypes, typename... rtypes> std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype> dispatcher <protocol> :: arc :: receive(const rtypes & ... remotes)
    {
        while(true)
        {
            sockets :: udp :: packet packet = this->_socket.receive();

            if(!(remote :: match(packet.remote(), remotes...)))
                continue;

            std :: cout << "Received packet from whitelisted remote" << std :: endl;

            if(packet.size() < :: network :: packet :: count <protocol> :: size)
            {
                std :: cout << "Message too short" << std :: endl;
                continue;
            }

            typename :: network :: packet :: count <protocol> :: type index;
            bytewise :: endianess :: translate(reinterpret_cast <char (&)[:: network :: packet :: count <protocol> :: size]> (index), reinterpret_cast <const char (&)[:: network :: packet :: count <protocol> :: size]> (*(packet.message())));

            try
            {
                return message :: template interpret <std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype>, ptype, ptypes...> (index, packet);
            }
            catch(...)
            {
                std :: cout << "Something went wrong" << std :: endl;
            }
        }
    }

    // Private static methods

    template <typename protocol> inline bool dispatcher <protocol> :: arc :: remote :: in(const address &)
    {
        return false;
    }

    template <typename protocol> template <typename rtype, typename... rtypes> inline bool dispatcher <protocol> :: arc :: remote :: in(const address & needle, const rtype & straw, const rtypes & ... haystack)
    {
        return (straw.port() ? needle == straw : needle.ip() == straw.ip()) || in(needle, haystack...);
    }

    template <typename protocol> inline bool dispatcher <protocol> :: arc :: remote :: match(const address &)
    {
        return true;
    }

    template <typename protocol> template <typename rtype, typename... rtypes> inline bool dispatcher <protocol> :: arc :: remote :: match(const address & needle, const rtype & straw, const rtypes & ... haystack)
    {
        return in(needle, straw, haystack...);
    }

    template <typename protocol> template <typename ret_type, typename... ptypes, std :: enable_if_t <sizeof...(ptypes) == 0> *> inline ret_type dispatcher <protocol> :: arc :: message :: interpret(const size_t &, const sockets :: udp :: packet &)
    {
        throw wrong_header();
    }

    template <typename protocol> template <typename ret_type, typename ptype, typename... ptypes> inline ret_type dispatcher <protocol> :: arc :: message :: interpret(const size_t & needle, const sockets :: udp :: packet & packet)
    {
        if(needle == ptype :: index)
        {
            // Run bytewise on the packet content, obtain either a type or a tuple of types, wrap it into a packet, and either return it directly or wrap it into a variant with other packets.
        }
        else
            return interpret <ret_type, ptypes...> (needle, packet);
    }

    // dispatcher

    // Constructors

    template <typename protocol> dispatcher <protocol> :: dispatcher(const sockets :: udp & socket) : _arc(new arc(socket))
    {
    }

    // Methods

    template <typename protocol> template <typename ptype, typename... types, std :: enable_if_t <dispatcher <protocol> :: template packet <ptype> :: template is_callable <types...> :: value> *> void dispatcher <protocol> :: send(const address & remote, const types & ... fields)
    {
        packet <ptype> :: proxy :: send(*(this->_arc), remote, fields...);
    }

    template <typename protocol> template <typename ptype, typename... ptypes, typename... rtypes, std :: enable_if_t <:: network :: packet :: template in <protocol, ptype, ptypes...> :: value && utils :: are_same <address, rtypes...> :: value> *> std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype> dispatcher <protocol> :: receive(const rtypes & ... remotes)
    {
        return this->_arc->template receive <ptype, ptypes...> (remotes...);
    }
};

#endif
