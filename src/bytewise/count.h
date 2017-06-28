// Forward declarations

namespace bytewise
{
    template <typename> class count;
};

#if !defined(__forward__) && !defined(__drop__bytewise__count__h)
#define __drop__bytewise__count__h

// Libraries

#include <stddef.h>

// Includes

#include "exists.h"

namespace bytewise
{
    template <typename type> class count
    {
        // Service nested classes

        template <size_t, bool> struct iterator;

        template <size_t index> struct iterator <index, false>
        {
            static constexpr size_t value = index;
        };

        template <size_t index> struct iterator <index, true>
        {
            static constexpr size_t value = iterator <index + 1, exists <type, index + 1> :: value> :: value;
        };

    public:

        // Static members

        static constexpr size_t value = iterator <0, exists <type, 0> :: value> :: value;
    };
};

#endif
