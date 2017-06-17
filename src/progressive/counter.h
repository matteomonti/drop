// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace progressive
{
    template <template <size_t, bool> typename, size_t> class counter;
};

#if !defined(__forward__) && !defined(__drop__progressive__counter__h)
#define __drop__progressive__counter__h

// Includes

#include "exists.h"

namespace progressive
{
    template <template <size_t, bool> typename scope, size_t shuffle> class counter
    {
        // Service nested classes

        template <size_t, bool> struct iterator;

        template <size_t index> struct iterator <index, false>
        {
            static constexpr size_t value = index;
        };

        template <size_t index> struct iterator <index, true>
        {
            static constexpr size_t value = iterator <index + 1, exists <scope, index + 1, shuffle> :: value> :: value;
        };

    public:

        // Static members

        static constexpr size_t value = iterator <0, exists <scope, 0, shuffle> :: value> :: value;
    };
};

#endif
