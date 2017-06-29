// Forward declarations

namespace data
{
    template <typename...> class variant;
};

#if !defined(__forward__) && !defined(__drop__data__variant__h)
#define __drop__data__variant__h

// Libraries

#include <type_traits>
#include <stddef.h>

// Includes

#include "utils/template/static_max.h"
#include "utils/template/enable_in.h"
#include "utils/template/distinct.h"

namespace data
{
    template <typename... types> class variant
    {
    public: // REMOVE ME

        // Static asserts

        static_assert(sizeof...(types) >= 2, "Variant types must have at least two types.");
        static_assert(utils :: distinct <types...> :: value, "Variant types must be distinct.");

        // Service nested classes

        struct bits
        {
            template <size_t, size_t> struct iterator;

            template <size_t bits> struct iterator <0, bits>
            {
                static constexpr size_t value = bits;
            };

            template <size_t number, size_t bits> struct iterator
            {
                static constexpr size_t value = iterator <number / 2, bits + 1> :: value;
            };

            static constexpr size_t value = iterator <sizeof...(types) - 1, 0> :: value;
        };

        template <typename needle> struct id
        {
            template <typename...> struct iterator;

            template <typename first> struct iterator <first>
            {
                static constexpr size_t value = 0;
            };

            template <typename next, typename... tail> struct iterator <needle, next, tail...>
            {
                static constexpr size_t value = 0;
            };

            template <typename first, typename next, typename... tail> struct iterator <first, next, tail...>
            {
                static constexpr size_t value = iterator <next, tail...> :: value + 1;
            };

            static constexpr size_t value = iterator <types...> :: value;
        };

        // Private static members

        static constexpr size_t size = utils :: static_max <size_t, sizeof(types)...> :: value;
        static constexpr size_t align = utils :: static_max <size_t, alignof(types)...> :: value;

        // Members

        std :: aligned_storage <size, align> _bytes;

        // Private constructors

        variant();

    public:

        // Static methods

        template <typename vtype, typename... atypes, std :: enable_if_t <utils :: in <vtype, types...> :: value && std :: is_constructible <vtype, atypes...> :: value> * = nullptr> static inline variant construct(atypes && ...);
    };
};

#endif
