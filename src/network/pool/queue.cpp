// Includes

#include "queue.hpp"

namespace network
{
    // kevent_failed

    const char * queue :: kevent_failed :: what() const noexcept
    {
        return "Kevent failed.";
    }

    // event

    // Getters

    #ifdef __APPLE__
    int queue :: event :: descriptor() const
    {
        return this->ident;
    }
    #endif

    // queue

    // Constructors

    queue :: queue()
    {
        #ifdef __APPLE__
        this->_descriptor = kqueue();
        #endif
    }

    // Destructor

    queue :: ~queue()
    {
        close(this->_descriptor);
    }

    // Methods

    size_t queue :: select(const microtimestamp & timeout)
    {
        int count;

        if(timeout)
        {
            struct timespec ktimeout
            {
                .tv_sec = (__darwin_time_t) (timeout / 1000000),
                .tv_nsec = (__darwin_time_t) (timeout % 1000000) * 1000
            };

            count = kevent(this->_descriptor, 0, 0, this->_events, (int) settings :: buffer_size, &ktimeout);
        }
        else
            count = kevent(this->_descriptor, 0, 0, this->_events, (int) settings :: buffer_size, nullptr);

        return count;
    }

    // Operators

    int queue :: operator [] (const size_t & index) const
    {
        return this->_events[index].descriptor();
    }
};
