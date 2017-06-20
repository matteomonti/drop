// Forward declarations

namespace bytewise
{
    namespace scanners
    {
        template <typename> class buffer;
    };
};

#if !defined(__forward__) && !defined(__drop__bytewise__scanners__buffer__h)
#define __drop__bytewise__scanners__buffer__h

// Libraries

#include <type_traits>
#include <stddef.h>

// Forward includes

#define __forward__
#include "bytewise/buffer.h"
#undef __forward__

// Includes

#include "bytewise/count.h"
#include "bytewise/proxy.h"
#include "bytewise/map.h"

namespace bytewise :: scanners
{
    template <typename target> class buffer
    {
    public: // REMOVE ME

        // Service nested classes

        template <typename mtype> struct valid
        {
            template <ssize_t, bool> struct extent_iterator;

            template <bool dummy> struct extent_iterator <-1, dummy>
            {
                static constexpr bool value = true;
            };

            template <ssize_t dimension, bool dummy> struct extent_iterator
            {
                static constexpr bool value = extent_iterator <dimension - 1, dummy> :: value && std :: extent <mtype, dimension> :: value != 0;
            };

            static constexpr bool value = (std :: is_class <typename std :: remove_all_extents <mtype> :: type> :: value) && (extent_iterator <(ssize_t) (std :: rank <mtype> :: value) - 1, false> :: value);
        };

        template <size_t index> struct member
        {
            typedef typename proxy <target, index> :: type mtype;
            typedef typename std :: remove_cv <typename std :: remove_all_extents <mtype> :: type> :: type base;

            typedef typename std :: conditional
            <
                valid <mtype> :: value,
                typename std :: conditional
                <
                    std :: is_same <base, :: bytewise :: buffer> :: value,
                    map <path <index>>,
                    typename buffer <base> :: type :: template prefix <index> :: type
                > :: type,
                map <>
            > :: type type;
        };

        template <ssize_t, bool> struct iterator;

        template <bool dummy> struct iterator <-1, dummy>
        {
            typedef map <> type;
        };

        template <ssize_t index, bool dummy> struct iterator
        {
            typedef typename iterator <index - 1, false> :: type :: template append <typename member <index> :: type> :: type type;
        };

    public:

        // Typedefs

        typedef typename iterator <(ssize_t) (count <target> :: value) - 1, false> :: type type;
    };
};

#endif
