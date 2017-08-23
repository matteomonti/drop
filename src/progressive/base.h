// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace progressive
{
    template <size_t> class base;
};

#if !defined(__forward__) && !defined(__drop__progressive__base__h)
#define __drop__progressive__base__h

namespace progressive
{
    template <size_t idx> class base
    {
    public:

        static constexpr bool exists = true;
        static constexpr size_t index = idx;
    };
};

#endif
