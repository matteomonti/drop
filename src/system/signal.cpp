// Includes

#include "signal.h"

namespace system
{
    // Constructors

    signal :: masker :: masker()
    {
        sigset_t mask;
        sigfillset(&mask);
        sigprocmask(SIG_SETMASK, &mask, nullptr);
    }

    // Static members

    class signal :: masker signal :: masker;
};
