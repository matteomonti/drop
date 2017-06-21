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
            typedef typename std :: remove_all_extents <mtype> :: type base;
            typedef typename std :: remove_cv <base> :: type clean;

            typedef typename std :: conditional
            <
                valid <mtype> :: value,
                typename std :: conditional
                <
                    std :: is_same <clean, :: bytewise :: buffer> :: value,
                    map <path <index>>,
                    typename buffer <base> :: type :: template prefix <index> :: type
                > :: type,
                map <>
            > :: type type;

            template <bool, bool> struct valid_conditional;

            template <bool dummy> struct valid_conditional <false, dummy>
            {
                static constexpr bool empty = true;
                static constexpr bool writable = true;
            };

            template <bool dummy> struct valid_conditional <true, dummy>
            {
                static constexpr bool empty = !(std :: is_same <clean, :: bytewise :: buffer> :: value) && (buffer <base> :: empty);
                static constexpr bool writable = (std :: is_same <clean, :: bytewise :: buffer> :: value && !(std :: is_const <base> :: value)) || (!(std :: is_same <clean, :: bytewise :: buffer> :: value) && buffer <base> :: writable && (buffer <base> :: empty || !(std :: is_const <base> :: value)));
            };

            static constexpr bool empty = valid_conditional <valid <mtype> :: value, false> :: empty;
            static constexpr bool writable = valid_conditional <valid <mtype> :: value, false> :: writable;
        };

        template <ssize_t, bool> struct iterator;

        template <bool dummy> struct iterator <-1, dummy>
        {
            typedef map <> type;

            static constexpr bool empty = true;
            static constexpr bool writable = true;
        };

        template <ssize_t index, bool dummy> struct iterator
        {
            typedef typename iterator <index - 1, false> :: type :: template append <typename member <index> :: type> :: type type;

            static constexpr bool empty = iterator <index - 1, false> :: empty && member <index> :: empty;
            static constexpr bool writable = iterator <index - 1, false> :: writable && member <index> :: writable;
        };

    public:

        // Typedefs

        typedef typename iterator <(ssize_t) (count <target> :: value) - 1, false> :: type type;

        // Static members

        static constexpr bool empty = iterator <(ssize_t) (count <target> :: value) - 1, false> :: empty;
        static constexpr bool writable = iterator <(ssize_t) (count <target> :: value) - 1, false> :: writable;
    };
};

#endif
