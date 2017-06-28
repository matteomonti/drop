// Forward declarations

namespace os
{
    class signal;
};

#if !defined(__forward__) && !defined(__drop__os__signal__h)
#define __drop__os__signal__h

// Libraries

#include <signal.h>

namespace os
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
