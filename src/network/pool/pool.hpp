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

    // arc

    // Constructors

    template <typename protocol> pool :: dispatcher <protocol> :: arc :: arc(pool & pool, const :: network :: dispatcher <protocol> & dispatcher) : _pool(pool), _dispatcher(dispatcher._arc)
    {
        this->_dispatcher->_mutex.send.lock();
        this->_dispatcher->_mutex.receive.lock();

        this->_dispatcher->_locked = true;
        this->_dispatcher->block(false);

        this->_dispatcher->_mutex.send.unlock();
        this->_dispatcher->_mutex.receive.unlock();
    }

    // Destructor

    template <typename protocol> pool :: dispatcher <protocol> :: arc :: ~arc()
    {
        this->_dispatcher->_mutex.send.lock();
        this->_dispatcher->_mutex.receive.lock();

        this->_dispatcher->_locked = false;
        this->_dispatcher->block(true);

        this->_dispatcher->_mutex.send.unlock();
        this->_dispatcher->_mutex.receive.unlock();
    }

    // dispatcher

    // Private constructors

    template <typename protocol> pool :: dispatcher <protocol> :: dispatcher(pool & pool, const :: network :: dispatcher <protocol> & dispatcher) : _arc(new arc(pool, dispatcher))
    {
    }

    // Methods

    template <typename protocol> template <typename ptype, typename... types, std :: enable_if_t <:: network :: dispatcher <protocol> :: template packet <ptype> :: template is_callable <types...> :: value> *> promise <void> pool :: dispatcher <protocol> :: send(const address & remote, const types & ... fields)
    {
        return this->_arc->_pool.template send <ptype> (*this, remote, fields...);
    }

    // pool

    // Methods

    template <typename protocol> pool :: dispatcher <protocol> pool :: bind(const :: network :: dispatcher <protocol> & dispatcher)
    {
        return {*this, dispatcher};
    }

    // Private methods

    template <typename type> promise <void> pool :: send(const connection & connection, const type & target)
    {
        request :: connection request{.connection = connection, .type = queue :: write};

        connection._arc->_connection->send_setup(target);

        :: network :: connection :: step status;
        while((status = connection._arc->_connection->send_step()) == :: network :: connection :: more);

        if(status == :: network :: connection :: wait)
        {
            this->_mutex.lock();

            this->_new.push(data :: variant <request :: connection, request :: dispatcher> :: construct <request :: connection> (request));
            this->wake();

            this->_mutex.unlock();
        }
        else
            request.promise.resolve();

        return request.promise;
    }

    template <typename type> promise <type> pool :: receive(const connection & connection)
    {
        promise <type> promise;

        request :: connection request {.connection = connection, .type = queue :: read};
        connection._arc->_connection->receive_setup(bytewise :: traits <type> :: size);

        request.promise.then([=]()
        {
            promise.resolve(connection._arc->_connection->receive_finalize <type> ());
        }).except([=](const std :: exception_ptr & exception)
        {
            promise.reject(exception);
        });

        this->_mutex.lock();

        this->_new.push(data :: variant <request :: connection, request :: dispatcher> :: construct <request :: connection> (request));
        this->wake();

        this->_mutex.unlock();
        return promise;
    }

    template <typename ptype, typename protocol, typename... types> promise <void> pool :: send(const dispatcher <protocol> & dispatcher, const address & remote, const types & ... fields)
    {
        promise <void> promise;
        dispatcher._arc->_dispatcher->template send_setup <ptype> (remote, fields...);

        if(dispatcher._arc->_dispatcher->send())
            promise.resolve();
        else
        {
            request :: dispatcher request
            {
                .descriptor = dispatcher._arc->_dispatcher->descriptor(),
                .resolve = [=]()
                {
                    try
                    {
                        dispatcher._arc->_dispatcher->send();
                        promise.resolve();
                    }
                    catch(...)
                    {
                        promise.reject(std :: current_exception());
                    }

                    return true;
                },
                .reject = [=](const std :: exception_ptr & exception)
                {
                    promise.reject(exception);
                },
                .type = queue :: write
            };

            this->_mutex.lock();

            this->_new.push(data :: variant <request :: connection, request :: dispatcher> :: construct <request :: dispatcher> (request));
            this->wake();

            this->_mutex.unlock();
        }

        return promise;
    }
};

#endif
