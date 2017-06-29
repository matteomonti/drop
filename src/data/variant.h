// Forward declarations

namespace data
{
    template <typename...> class variant_base;
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
    template <typename... types> class variant_base
    {
        // Static asserts

        static_assert(sizeof...(types) >= 2, "Variant types must have at least two types.");
        static_assert(utils :: distinct <types...> :: value, "Variant types must be distinct.");

        // Service nested classes

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

        template <size_t index> struct type
        {
            template <size_t, typename...> struct iterator;

            template <typename first, typename... tail> struct iterator <0, first, tail...>
            {
                typedef first type;
            };

            template <size_t cursor, typename first, typename... tail> struct iterator <cursor, first, tail...>
            {
                typedef typename iterator <cursor - 1, tail...> :: type type;
            };

            typedef typename iterator <index, types...> :: type vtype;
        };

        struct visit
        {
            template <size_t, bool> struct iterator;

            template <bool dummy> struct iterator <sizeof...(types), dummy>
            {
                template <typename lambda> static inline void run(variant_base <types...> &, lambda &&);
                template <typename lambda> static inline void run(const variant_base <types...> &, lambda &&);
            };

            template <size_t index, bool dummy> struct iterator
            {
                template <typename lambda> static inline void run(variant_base <types...> &, lambda &&);
                template <typename lambda> static inline void run(const variant_base <types...> &, lambda &&);
            };

            template <typename lambda> static inline void run(variant_base <types...> &, lambda &&);
            template <typename lambda> static inline void run(const variant_base <types...> &, lambda &&);
        };

        struct are
        {
            template <typename...> struct iterator;

            template <typename first> struct iterator <first>
            {
                static constexpr bool move_constructible = std :: is_move_constructible <first> :: value;
                static constexpr bool copy_constructible = std :: is_copy_constructible <first> :: value;
            };

            template <typename first, typename next, typename... tail> struct iterator <first, next, tail...>
            {
                static constexpr bool move_constructible = std :: is_move_constructible <first> :: value && iterator <next, tail...> :: move_constructible;
                static constexpr bool copy_constructible = std :: is_copy_constructible <first> :: value && iterator <next, tail...> :: copy_constructible;
            };

            static constexpr bool move_constructible = iterator <types...> :: move_constructible;
            static constexpr bool copy_constructible = iterator <types...> :: copy_constructible;
        };

        // Private static members

        static constexpr size_t size = utils :: static_max <size_t, sizeof(types)...> :: value;
        static constexpr size_t align = utils :: static_max <size_t, alignof(types)...> :: value;

        // Members

        std :: aligned_storage <size, align> _bytes;
        size_t _typeid;

        // Private constructors

        variant_base();

    public:

        // Constructors

        variant_base(variant_base &&);
        variant_base(const variant_base &);

        // Destructor

        ~variant_base();

        // Methods

        template <typename lambda> void visit(lambda &&);
        template <typename lambda> void visit(lambda &&) const;

        // Static methods

        template <typename vtype, typename... atypes, std :: enable_if_t <utils :: in <vtype, types...> :: value && std :: is_constructible <vtype, atypes...> :: value> * = nullptr> static inline variant_base construct(atypes && ...);
    };
};

#endif
