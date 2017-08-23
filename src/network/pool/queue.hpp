#ifndef __drop__network__pool__queue__hpp
#define __drop__network__pool__queue__hpp

// Includes

#include "queue.h"

namespace network
{
    // Methods

    template <queue :: type filter, std :: enable_if_t <filter == queue :: read> *> void queue :: add(const int & descriptor)
    {
        #ifdef __APPLE__
        struct kevent event
        {
            .ident = (uintptr_t) descriptor,
            .flags = (uint16_t) EV_ADD,
            .filter = EVFILT_READ,
            .fflags = 0,
            .data = 0,
            .udata = nullptr
        };

        if(kevent(this->_descriptor, &event, 1, 0, 0, 0) < 0)
            throw kevent_failed();
        #endif

        #ifdef __linux__
        struct epoll_event event
        {
            .data.fd = descriptor,
            .events = EPOLLIN
        };

        if(epoll_ctl(this->_descriptor, EPOLL_CTL_ADD, descriptor, &event) < 0)
            throw epoll_ctl_failed();
        #endif
    }

    template <queue :: type filter, std :: enable_if_t <filter == queue :: write> *> void queue :: add(const int & descriptor)
    {
        #ifdef __APPLE__
        struct kevent event
        {
            .ident = (uintptr_t) descriptor,
            .flags = (uint16_t) EV_ADD,
            .filter = EVFILT_WRITE,
            .fflags = 0,
            .data = 0,
            .udata = nullptr
        };

        if(kevent(this->_descriptor, &event, 1, 0, 0, 0) < 0)
            throw kevent_failed();
        #endif

        #ifdef __linux__
        struct epoll_event event
        {
            .data.fd = descriptor,
            .events = EPOLLOUT
        };

        if(epoll_ctl(this->_descriptor, EPOLL_CTL_ADD, descriptor, &event) < 0)
            throw epoll_ctl_failed();
        #endif
    }

    template <queue :: type filter, std :: enable_if_t <filter == queue :: read> *> void queue :: remove(const int & descriptor)
    {
        #ifdef __APPLE__
        struct kevent event
        {
            .ident = (uintptr_t) descriptor,
            .flags = (uint16_t) EV_DELETE,
            .filter = EVFILT_READ,
            .fflags = 0,
            .data = 0,
            .udata = nullptr
        };

        if(kevent(this->_descriptor, &event, 1, 0, 0, 0) < 0)
            throw kevent_failed();
        #endif

        #ifdef __linux__
        struct epoll_event event
        {
            .data.fd = descriptor,
            .events = EPOLLIN
        };

        if(epoll_ctl(this->_queue, EPOLL_CTL_DEL, descriptor, &event) < 0)
            throw epoll_ctl_failed();
        #endif
    }

    template <queue :: type filter, std :: enable_if_t <filter == queue :: write> *> void queue :: remove(const int & descriptor)
    {
        #ifdef __APPLE__
        struct kevent event
        {
            .ident = (uintptr_t) descriptor,
            .flags = (uint16_t) EV_DELETE,
            .filter = EVFILT_WRITE,
            .fflags = 0,
            .data = 0,
            .udata = nullptr
        };

        if(kevent(this->_descriptor, &event, 1, 0, 0, 0) < 0)
            throw kevent_failed();
        #endif

        #ifdef __linux__
        struct epoll_event event
        {
            .data.fd = descriptor,
            .events = EPOLLOUT
        };

        if(epoll_ctl(this->_queue, EPOLL_CTL_DEL, descriptor, &event) < 0)
            throw epoll_ctl_failed();
        #endif
    }
};

#endif
