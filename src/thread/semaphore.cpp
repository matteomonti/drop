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

        #ifdef __linux__
        sem_init(&(this->_semaphore), 0, this->_base);
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

        #ifdef __linux__
        sem_destroy(&(this->_semaphore));
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

        #ifdef __linux__
        if(!timeout)
            return sem_wait(&(this->_semaphore));
        else
        {
    		struct timeval now;
    		gettimeofday(&now, 0);

            struct timeval offset
            {
                .tv_sec = (__time_t) (timeout / 1000000),
                .tv_usec = (__time_t) (timeout % 1000000)
            };

            timeradd(&now, &offset, &now);

            struct timespec time
            {
    			.tv_sec = now.tv_sec,
                .tv_nsec = now.tv_usec * 1000
    		};

            return sem_timedwait(&(this->_semaphore), &time);
        }
        #endif
    }

    void semaphore :: post()
    {
        #ifdef __APPLE__
        dispatch_semaphore_signal(this->_semaphore);
        #endif

        #ifdef __linux__
        sem_post(&(this->_semaphore));
        #endif
    }
};
