// Forward declarations

namespace thread
{
    class semaphore;
};

#if !defined(__forward__) && !defined(__drop__thread__semaphore__h)
#define __drop__thread__semaphore__h

// Libraries

#include <stddef.h>
#include <time.h>

#ifdef __APPLE__
#include <dispatch/dispatch.h>
#endif

#ifdef __linux__
#include <semaphore.h>
#endif

// Includes

#include "chrono/time.h"

namespace thread
{
    class semaphore
    {
        // Members

        #ifdef __APPLE__
        dispatch_semaphore_t _semaphore;
        #endif

        #ifdef __linux__
        sem_t _semaphore;
        #endif

        size_t _base;

    public:

        // Constructors

        semaphore(const size_t & = 0);

        // Destructor

        ~semaphore();

        // Methods

        bool wait(const microtimestamp & = 0);
        void post();
    };
};

#endif
