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

// Forward includes

#define __forward__
#include "bytewise/serialize.h"
#include "bytewise/deserialize.h"
#undef __forward__

// Includes

#include "bytewise/count.h"
#include "bytewise/proxy.h"
#include "bytewise/mask.h"
#include "bytewise/endianess.h"

namespace bytewise :: scanners
{
    template <typename target> struct arithmetic
    {
        // Friends

        template <typename> friend class arithmetic;
        template <typename> friend class :: bytewise :: serializer;
        template <typename> friend class :: bytewise :: deserializer;
        template <typename> friend class :: bytewise :: traits;

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
            static constexpr bool value = (std :: is_class <std :: remove_all_extents_t <mtype>> :: value || std :: is_arithmetic <std :: remove_all_extents_t <mtype>> :: value) && (std :: rank <mtype> :: value == 0 || extent <mtype> :: value != 0);
        };

        template <size_t, size_t, typename, size_t> struct repeat;

        template <size_t offset, typename pattern, size_t size> struct repeat <offset, 0, pattern, size>
        {
            typedef mask <> type;
        };

        template <size_t offset, size_t reps, size_t size> struct repeat <offset, reps, mask <range <0, size, false>>, size>
        {
            typedef mask <range <offset, offset + size * reps, false>> type;
        };

        template <size_t offset, size_t reps, typename pattern, size_t size> struct repeat
        {
            typedef typename pattern :: template shift <offset> :: type :: template append <typename repeat <offset + size, reps - 1, pattern, size> :: type> :: type type;
        };

        template <size_t index> struct member
        {
            typedef typename proxy <target, index> :: type mtype;
            typedef std :: remove_all_extents_t <mtype> base;

            static constexpr endianess :: type endianess = proxy <target, index> :: endianess;

            typedef std :: conditional_t
            <
                valid <mtype> :: value,
                std :: conditional_t
                <
                    std :: is_arithmetic <base> :: value,
                    mask <range <0, sizeof(base), ((endianess != endianess :: local) && sizeof(base) > 1)>>,
                    typename arithmetic <base> :: type
                >,
                mask <>
            > pattern;

            typedef typename repeat <proxy <target, index> :: offset, (std :: is_array <mtype> :: value ? extent <mtype> :: value : 1), pattern, sizeof(base)> :: type type;

            template <bool, bool> struct arithmetic_conditional;

            template <bool dummy> struct arithmetic_conditional <true, dummy>
            {
                static constexpr bool empty = false;
                static constexpr bool writable = !(std :: is_const <base> :: value);
            };

            template <bool dummy> struct arithmetic_conditional <false, dummy>
            {
                static constexpr bool empty = arithmetic <base> :: empty;
                static constexpr bool writable = arithmetic <base> :: writable && (arithmetic <base> :: empty || !(std :: is_const <base> :: value));
            };

            static constexpr bool empty = (!valid <mtype> :: value) || (arithmetic_conditional <std :: is_arithmetic <base> :: value, false> :: empty);
            static constexpr bool writable = (!valid <mtype> :: value) || (arithmetic_conditional <std :: is_arithmetic <base> :: value, false> :: writable);
        };

        template <ssize_t, bool> struct iterator;

        template <bool dummy> struct iterator <-1, dummy>
        {
            typedef mask <> type;

            static constexpr bool empty = true;
            static constexpr bool writable = true;
        };

        template <ssize_t index, bool dummy> struct iterator
        {
            typedef typename iterator <index - 1, dummy> :: type :: template append <typename member <index> :: type> :: type type;

            static constexpr bool empty = iterator <index - 1, dummy> :: empty && member <index> :: empty;
            static constexpr bool writable = iterator <index - 1, dummy> :: writable && member <index> :: writable;
        };

        // Typedefs

        typedef typename iterator <(ssize_t)(count <target> :: value) - 1, false> :: type type;

        // Static members

        static constexpr bool empty = iterator <(ssize_t)(count <target> :: value) - 1, false> :: empty;
        static constexpr bool writable = iterator <(ssize_t)(count <target> :: value) - 1, false> :: writable;
    };
};

#endif
