// Includes

#include "semaphore.h"

namespace thread
{
    // Constructors

    semaphore :: semaphore(const size_t & base) : _base(base)
    {
        #ifdef __APPLE__
        this->_semaphore = dispatch_semaphore_create(this->_base);
        #endif
    }

    // Destructor

    semaphore :: ~semaphore()
    {
        #ifdef __APPLE__
        for(size_t i = 0; i < this->_base; i++)
            this->post();

        dispatch_release(this->_semaphore);
        #endif
    }

    // Methods

    bool semaphore :: wait(const microtimestamp & timeout)
    {
        #ifdef __APPLE__
        if(!timeout)
            return dispatch_semaphore_wait(this->_semaphore, DISPATCH_TIME_FOREVER);
        else
        {
            dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW, timeout * NSEC_PER_USEC);
            return dispatch_semaphore_wait(this->_semaphore, time);
        }
        #endif
    }

    void semaphore :: post()
    {
        #ifdef __APPLE__
        dispatch_semaphore_signal(this->_semaphore);
        #endif
    }
};
