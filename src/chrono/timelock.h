// Forward declarations

namespace chrono
{
    template <typename> class timelock;
};

#if !defined(__forward__) && !defined(__drop__chrono__timelock__h)
#define __drop__chrono__timelock__h

// Includes

#include "time.h"
#include "data/heap.hpp"
#include "data/optional.hpp"

namespace chrono
{
    template <typename type> class timelock
    {
        // Service nested classes

        struct entry
        {
            // Members

            type value;
            microtimestamp expiry;

            // Operators

            bool operator < (const entry &) const;
            bool operator > (const entry &) const;
        };

        // Members

        data :: heap <entry> _entries;

    public:

        // Methods

        void push(const type &, const microtimestamp &);
        data :: optional <type> pop();

        data :: optional <microtimestamp> next() const;
    };
};

#endif
