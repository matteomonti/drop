// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace bytewise
{
    template <typename, size_t> class proxy;
};

#if !defined(__forward__) && !defined(__drop__bytewise__proxy__h)
#define __drop__bytewise__proxy__h

namespace bytewise
{
    template <typename type, size_t index> class proxy
    {
        // Static methods

        static inline auto & get(type &);
        static inline const auto & get(const type &);
    };
};

#endif
