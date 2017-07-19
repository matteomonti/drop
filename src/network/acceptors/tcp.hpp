#ifndef __drop__network__acceptors__tcp__hpp
#define __drop__network__acceptors__tcp__hpp

#include "tcp.h"

namespace network :: acceptors
{
    // callback

    // Constructors

    template <typename lambda> tcp :: async :: callback <lambda> :: callback(const lambda & callback) : _callback(callback)
    {
    }

    // Methods

    template <typename lambda> void tcp :: async :: callback <lambda> :: run(const connection & connection)
    {
        this->_callback(connection);
    }

    // async

    // Methods

    template <typename type, typename lambda, typename std :: enable_if_t <std :: is_same <type, connection> :: value && utils :: is_callable <lambda, const connection &> :: value> *> void tcp :: async :: on(const lambda & callback)
    {
        this->_mutex.lock();

        assert(!(this->_callbacks[settings :: callbacks - 1]));

        for(size_t i = 0; i < settings :: callbacks; i++)
            if(!(this->_callbacks[i]))
            {
                this->_callbacks[i] = new (class tcp :: async :: callback <lambda>){callback};
                break;
            }

        this->_mutex.unlock();
    }
};

#endif
