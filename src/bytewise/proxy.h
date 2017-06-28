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
#include "visitors/on.h"
#undef __forward__

// Includes

#include "utils/template/enable_in.h"

namespace bytewise
{
    template <typename target, size_t index> class proxy
    {
        // Friends

        template <typename> friend class scanners :: arithmetic;
        template <typename> friend class scanners :: buffer;
        template <typename> friend class visitors :: buffer;
        friend class visitors :: on;

        // Typedefs

        typedef typename target :: template __bytewise__ <index, false> :: type type;

        // Static members

        static constexpr size_t offset = target :: template __bytewise__ <index, false> :: offset();

        // Static methods

        template <typename otype, utils :: enable_in_t <otype, target> * = nullptr> static inline auto && get(otype &&);
    };
};

#endif
