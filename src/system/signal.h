// Forward declarations

namespace system
{
    class signal;
};

#if !defined(__forward__) && !defined(__drop__system__signal__h)
#define __drop__system__signal__h

// Libraries

#include <signal.h>

namespace system
{
    class signal
    {
        // Service nested classes

        struct masker
        {
            // Constructors

            masker();
        };

        // Static private members

        static masker masker;
    };
};

#endif
