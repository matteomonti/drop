// Forward declarations

namespace network
{
    namespace packet
    {
        template <typename, typename> class in;
    };
};

#if !defined(__forward__) && !defined(__drop__network__packet__in__h)
#define __drop__network__packet__count__h

// Libraries

#include <stddef.h>
#include <type_traits>

// Includes

#include "count.h"
#include "proxy.h"

namespace network :: packet
{
    template <typename haystack, typename needle> class in
    {
        // Service nested classes

        template <ssize_t, bool> struct iterator;

        template <bool dummy> struct iterator <-1, dummy>
        {
            static constexpr bool value = false;
        };

        template <ssize_t index, bool dummy> struct iterator
        {
            static constexpr bool value = std :: is_same <proxy_t <haystack, index>, needle> :: value || iterator <index - 1, false> :: value;
        };

    public:

        // Static members

        static constexpr bool value = iterator <((ssize_t) count <needle> :: value) - 1, false> :: value;
    };
};

#endif
