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
#include <sys/event.h>
#include <sys/time.h>
#include <exception>

// Includes

#include "time/time.h"

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

        // Nested enums

        enum type {read, write};

        // Nested classes

        #ifdef __APPLE__
        class event : public kevent
        {
        public:

            // Getters

            int descriptor() const;
        };
        #endif

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

        size_t select(const microtimestamp & = 0);

        // Operators

        int operator [] (const size_t &) const;
    };
};

#endif
