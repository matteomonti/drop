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

    // remote

    // Static methods

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

    // deserializer

    // Static methods

    template <typename protocol> template <typename ptype, typename... types> inline ptype dispatcher <protocol> :: arc :: message :: deserializer <ptype, :: network :: packet :: fields <types...>> :: run(const sockets :: udp :: packet & packet)
    {
        return ptype(packet.remote(), bytewise :: deserialize <types...> (bytewise :: buffer(bytewise :: buffer :: reference, const_cast <char *> (packet.message()) + :: network :: packet :: template count <protocol> :: size, packet.size() - :: network :: packet :: template count <protocol> :: size)));
    }

    // wrapper <variant <ptypes...>>

    // Static methods

    template <typename protocol> template <typename... ptypes> template <typename ptype> inline data :: variant <ptypes...> dispatcher <protocol> :: arc :: message :: wrapper <data :: variant <ptypes...>> :: run(const ptype & packet)
    {
        return data :: variant <ptypes...> :: template construct <ptype> (packet);
    }

    // wrapper <ptype>

    // Static methods

    template <typename protocol> template <typename ptype> inline ptype dispatcher <protocol> :: arc :: message :: wrapper <ptype> :: run(const ptype & packet)
    {
        return packet;
    }

    // message

    // Static methods

    template <typename protocol> template <typename ret_type, typename... ptypes, std :: enable_if_t <sizeof...(ptypes) == 0> *> inline ret_type dispatcher <protocol> :: arc :: message :: interpret(const size_t &, const sockets :: udp :: packet &)
    {
        throw wrong_header();
    }

    template <typename protocol> template <typename ret_type, typename ptype, typename... ptypes> inline ret_type dispatcher <protocol> :: arc :: message :: interpret(const size_t & needle, const sockets :: udp :: packet & packet)
    {
        if(needle == ptype :: index)
            return wrapper <ret_type> :: run(deserializer <ptype, typename ptype :: fields> :: run(packet));
        else
            return interpret <ret_type, ptypes...> (needle, packet);
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
        try
        {
            this->_mutex.send.lock();
            assert(!(this->_locked));

            this->send_setup <ptype> (remote, fields...);
            this->send();

            this->_mutex.send.unlock();
        }
        catch(...)
        {
            this->_mutex.send.unlock();
            std :: rethrow_exception(std :: current_exception());
        }
    }

    template <typename protocol> template <typename ptype, typename... ptypes, typename... rtypes> std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype> dispatcher <protocol> :: arc :: receive(const rtypes & ... remotes)
    {
        try
        {
            this->_mutex.receive.lock();
            assert(!(this->_locked));

            while(true)
            {
                auto packet = receive_round <ptype, ptypes...> (remotes...);

                if(packet)
                    return *packet;
            }
        }
        catch(...)
        {
            this->_mutex.receive.unlock();
            std :: rethrow_exception(std :: current_exception());
        }
    }

    // Private methods

    template <typename protocol> template <typename ptype, typename... types> void dispatcher <protocol> :: arc :: send_setup(const address & remote, const types & ... fields)
    {
        typename :: network :: packet :: template count <protocol> :: type index = ptype :: index;
        auto message = bytewise :: serialize <bytewise :: options :: pad :: template beg <sizeof(index)>> (((types) fields)...);
        bytewise :: endianess :: translate(reinterpret_cast <char (&)[sizeof(index)]> (message), reinterpret_cast <const char (&)[sizeof(index)]> (index));

        this->_write.remote = remote;
        memcpy(this->_write.buffer, message, message.size());
        this->_write.size = message.size();
    }

    template <typename protocol> bool dispatcher <protocol> :: arc :: send()
    {
        return this->_socket.send(this->_write.remote, this->_write.buffer, this->_write.size);
    }

    template <typename protocol> template <typename ptype, typename... ptypes, typename... rtypes> data :: optional <std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype>> dispatcher <protocol> :: arc :: receive_round(const rtypes & ... remotes)
    {
        sockets :: udp :: packet packet = this->_socket.receive();

        if(!(remote :: match(packet.remote(), remotes...)))
            return data :: null;

        if(packet.size() < :: network :: packet :: count <protocol> :: size)
            return data :: null;

        typename :: network :: packet :: count <protocol> :: type index;
        bytewise :: endianess :: translate(reinterpret_cast <char (&)[:: network :: packet :: count <protocol> :: size]> (index), reinterpret_cast <const char (&)[:: network :: packet :: count <protocol> :: size]> (*(packet.message())));

        try
        {
            auto response = message :: template interpret <std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype>, ptype, ptypes...> (index, packet);
            this->_mutex.receive.unlock();

            return response;
        }
        catch(...)
        {
        }

        return data :: null;
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
