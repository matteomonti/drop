#ifndef __drop__network__acceptors__tcp__hpp
#define __drop__network__acceptors__tcp__hpp

#include "tcp.h"

namespace network :: acceptors
{
    // async

    // Methods

    template <typename etype, typename lambda, typename std :: enable_if_t <std :: is_same <etype, connection> :: value && utils :: is_callable <lambda, const connection &> :: value && std :: is_same <std :: result_of_t <lambda(const connection &)>, void> :: value> *> void tcp :: async :: on(const lambda & callback)
    {
        this->_mutex.lock();

        assert(!(this->_callbacks[settings :: callbacks - 1]));

        for(size_t i = 0; i < settings :: callbacks; i++)
            if(!(this->_callbacks[i]))
            {
                this->_callbacks[i] = callback;
                break;
            }

        this->_mutex.unlock();
    }
};

#endif
