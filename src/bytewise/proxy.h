// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace bytewise
{
    template <typename, size_t> class proxy;
};

#if !defined(__forward__) && !defined(__drop__bytewise__proxy__h)
#define __drop__bytewise__proxy__h

// Libraries

#include <utility>

// Forward includes

#define __forward__
#include "scanners/arithmetic.h"
#include "scanners/buffer.h"
#include "visitors/buffer.h"
#undef __forward__

namespace bytewise
{
    template <typename target, size_t index> class proxy // TODO: Find a solution to properly forward calls in the const case
    {
        // Friends

        template <typename> friend class scanners :: arithmetic;
        template <typename> friend class scanners :: buffer;
        template <typename> friend class visitors :: buffer;

        // Typedefs

        typedef typename target :: template bytewise <index, false> :: type type;

        // Static members

        static constexpr size_t offset = target :: template bytewise <index, false> :: offset();

        // Static methods

        static inline auto & get(target &);
        static inline auto & get(const target &);
    };
};

#endif
