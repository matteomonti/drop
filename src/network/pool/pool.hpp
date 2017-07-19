#ifndef __drop__network__pool__pool__hpp
#define __drop__network__pool__pool__hpp

// Includes

#include "pool.h"

namespace network
{
    // connection

    // Methods

    template <typename type> promise <void> pool :: connection :: send(const type & target) const
    {
        return this->_arc->_pool.send(*this, target);
    }

    template <typename type> promise <type> pool :: connection :: receive() const
    {
        return this->_arc->_pool.receive <type> (*this);
    }

    // pool

    // Private methods

    template <typename type> promise <void> pool :: send(const connection & connection, const type & target)
    {
        request request {.connection = connection, .type = queue :: write};
        connection._arc->_connection->send_setup(target);

        this->_mutex.lock();

        this->_new.push(request);
        this->wake();

        this->_mutex.unlock();
        return request.promise;
    }

    template <typename type> promise <type> pool :: receive(const connection & connection)
    {
        promise <type> promise;

        request request {.connection = connection, .type = queue :: read};
        connection._arc->_connection->receive_setup(bytewise :: traits <type> :: size);

        request.promise.then([=]()
        {
            promise.resolve(connection._arc->_connection->receive_finalize <type> ());
        }).except([=](const std :: exception_ptr & exception)
        {
            promise.reject(exception);
        });

        this->_mutex.lock();

        this->_new.push(request);
        this->wake();

        this->_mutex.unlock();
        return promise;
    }
};

#endif
