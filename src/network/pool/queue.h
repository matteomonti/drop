// Forward declarations

namespace network
{
    class queue;
};

#if !defined(__forward__) && !defined(__drop__network__pool__queue__h)
#define __drop__network__pool__queue__h

// Libraries

#include <type_traits>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <exception>
#include <assert.h>

#ifdef __APPLE__
#include <sys/event.h>
#endif

#ifdef __linux__
#include <sys/epoll.h>
#endif

// Includes

#include "chrono/time.h"

namespace network
{
    class queue
    {
    public:
        // Settings

        struct settings
        {
            static constexpr size_t buffer_size = 1024;
        };

        // Exceptions

        class kevent_failed : public std :: exception
        {
            const char * what() const noexcept;
        };

        class epoll_ctl_failed : public std :: exception
        {
            const char * what() const noexcept;
        };

        // Nested enums

        enum type {read, write};

        // Nested classes

        class event : public
                            #ifdef __APPLE__
                            kevent
                            #endif
                            #ifdef __linux__
                            epoll_event
                            #endif
        {
        public:

            // Getters

            int descriptor() const;
            type type() const;
        };

    private:

        // Members

        int _descriptor;
        event _events[settings :: buffer_size];

    public:

        // Constructors

        queue();

        // Destructor

        ~queue();

        // Methods

        template <type filter, std :: enable_if_t <filter == read> * = nullptr> void add(const int &);
        template <type filter, std :: enable_if_t <filter == write> * = nullptr> void add(const int &);

        template <type filter, std :: enable_if_t <filter == read> * = nullptr> void remove(const int &);
        template <type filter, std :: enable_if_t <filter == write> * = nullptr> void remove(const int &);

        size_t select(const microtimestamp & = 0);

        // Operators

        const event & operator [] (const size_t &) const;
    };
};

#endif
