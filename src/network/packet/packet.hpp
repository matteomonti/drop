#ifndef __drop__network__packet__packet__hpp
#define __drop__network__packet__packet__hpp

// Includes

#include "packet.h"

namespace network :: packet
{
    // packet <type>

    // Constructors

    template <typename type> packet <type> :: packet(const address & remote, const type & message) : _remote(remote), _message(message)
    {
    }

    // Methods

    template <typename type> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const address &, const type &> :: value> *> void packet <type> :: visit(const lambda & callback) const
    {
        callback(this->_remote, this->_message);
    }

    template <typename type> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const type &> :: value> *> void packet <type> :: visit(const lambda & callback) const
    {
        callback(this->_message);
    }

    // packet <types...>

    // Constructors

    template <typename... types> packet <types...> :: packet(const address & remote, const bytewise :: tuple <types...> & message) : _remote(remote), _message(message)
    {
    }

    // Methods

    template <typename... types> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const address &, const types & ...> :: value> *> void packet <types...> :: visit(const lambda & callback) const
    {
        this->_message.visit([&](const types & ... fields)
        {
            callback(this->_remote, fields...);
        });
    }

    template <typename... types> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const types & ...> :: value> *> void packet <types...> :: visit(const lambda & callback) const
    {
        this->_message.visit(callback);
    }
};

#endif
