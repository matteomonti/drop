// Forward declarations

namespace chrono
{
    class crontab;
};

#if !defined(__forward__) && !defined(__drop__chrono__crontab__h)
#define __drop__chrono__crontab__h

// Libraries

#include <stddef.h>
#include <thread>
#include <mutex>

// Includes

#include "time.h"
#include "timelock.hpp"
#include "async/promise.hpp"
#include "thread/semaphore.h"

namespace chrono
{
    class crontab
    {
        // Members

        timelock <promise <void>> _timelock;
        thread :: semaphore _semaphore;

        volatile bool _alive;
        std :: recursive_mutex _mutex;
        std :: thread _thread;

    public:

        // Constructors

        crontab();

        // Destructor

        ~crontab();

        // Methods

        promise <void> wait(const microtimestamp &);

    private:

        // Private methods

        void run();
    };
};

#endif
