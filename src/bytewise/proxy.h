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
    template <typename target, size_t index> class proxy
    {
        // Typedefs

        typedef typename target :: template bytewise <index> :: type type;

        // Static methods

        static inline auto & get(target &);
        static inline const auto & get(const target &);
    };
};

#endif
