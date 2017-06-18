// Forward declarations

namespace bytewise
{
    namespace scanners
    {
        template <typename> class arithmetic;
    };
};

#if !defined(__forward__) && !defined(__drop__bytewise__scanners__arithmetic__h)
#define __drop__bytewise__scanners__arithmetic__h

// Libraries

#include <type_traits>
#include <stddef.h>

// Includes

#include "bytewise/count.h"
#include "bytewise/proxy.h"

namespace bytewise :: scanners
{
    template <typename type> struct arithmetic
    {
        // Service nested classes

        template <typename mtype> struct extent
        {
            template <size_t, bool> struct iterator;

            template <bool dummy> struct iterator <0, dummy>
            {
                static constexpr size_t value = std :: extent <mtype, 0> :: value;
            };

            template <size_t dimension, bool dummy> struct iterator
            {
                static constexpr size_t value = std :: extent <mtype, dimension> :: value * iterator <dimension - 1, false> :: value;
            };

            struct null_iterator
            {
                static constexpr size_t value = 0;
            };

            static constexpr size_t value = std :: conditional <std :: rank <mtype> :: value != 0, iterator <std :: rank <mtype> :: value - 1, false>, null_iterator> :: type :: value;
        };

        template <typename mtype> struct valid
        {
            static constexpr bool value = (std :: is_class <typename std :: remove_all_extents <mtype> :: type> :: value || std :: is_arithmetic <typename std :: remove_all_extents <mtype> :: type> :: value) && (std :: rank <mtype> :: value == 0 || extent <mtype> :: value != 0);
        };
    };
};

#endif
