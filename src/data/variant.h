// Forward declarations

namespace data
{
    template <typename...> class variant_base;
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
#include "utils/template/all.h"
#include "utils/template/is_callable.h"
#include "utils/misc/copy_constructible.h"
#include "utils/misc/move_constructible.h"
#include "utils/misc/copy_assignable.h"
#include "utils/misc/move_assignable.h"

namespace data
{
    template <typename... types> class variant_base
    {
        // Friends

        template <typename...> friend class variant;

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

        struct dispatch
        {
            template <bool, bool> struct caller;

            template <bool dummy> struct caller <true, dummy>
            {
                template <typename dtype, typename lambda, typename... lambdas> static inline void run(dtype &&, lambda &&, lambdas && ...);
            };

            template <bool dummy> struct caller <false, dummy>
            {
                template <typename dtype, typename lambda, typename... lambdas> static inline void run(dtype &&, lambda &&, lambdas && ...);
            };

            template <typename dtype> static inline void run(dtype &&);
            template <typename dtype, typename lambda, typename... lambdas> static inline void run(dtype &&, lambda &&, lambdas && ...);
        };

        struct visit
        {
            template <size_t, bool> struct iterator;

            template <bool dummy> struct iterator <sizeof...(types), dummy>
            {
                template <typename... lambdas> static inline void run(variant_base <types...> &, lambdas && ...);
                template <typename... lambdas> static inline void run(const variant_base <types...> &, lambdas && ...);
            };

            template <size_t index, bool dummy> struct iterator
            {
                template <typename... lambdas> static inline void run(variant_base <types...> &, lambdas && ...);
                template <typename... lambdas> static inline void run(const variant_base <types...> &, lambdas && ...);
            };

            template <typename... lambdas> static inline void run(variant_base <types...> &, lambdas && ...);
            template <typename... lambdas> static inline void run(const variant_base <types...> &, lambdas && ...);
        };

        // Private static members

        static constexpr size_t size = utils :: static_max <size_t, sizeof(types)...> :: value;
        static constexpr size_t align = utils :: static_max <size_t, alignof(types)...> :: value;

        // Members

        std :: aligned_storage_t <size, align> _bytes;
        size_t _typeid;

        // Private constructors

        variant_base();

    public:

        // Constructors

        variant_base(const variant_base &);
        variant_base(variant_base &&);

        // Destructor

        ~variant_base();

        // Methods

        template <typename... lambdas> void visit(lambdas && ...);
        template <typename... lambdas> void visit(lambdas && ...) const;

        // Operators

        variant_base & operator = (const variant_base &);
        variant_base & operator = (variant_base &&);
    };

    template <typename... types> class variant : public variant_base <types...>,
                                                 public utils :: copy_constructible <utils :: all <std :: is_copy_constructible, types...> :: value>,
                                                 public utils :: move_constructible <utils :: all <std :: is_move_constructible, types...> :: value>,
                                                 public utils :: copy_assignable <utils :: all <std :: is_copy_constructible, types...> :: value && utils :: all <std :: is_copy_assignable, types...> :: value>,
                                                 public utils :: move_assignable <utils :: all <std :: is_move_constructible, types...> :: value && utils :: all <std :: is_move_assignable, types...> :: value>
    {
        // Static asserts

        static_assert(utils :: distinct <types...> :: value, "Variant types must be distinct.");

        // Private constructors

        variant();

    public:

        // Static methods

        template <typename vtype, typename... atypes, std :: enable_if_t <utils :: in <vtype, types...> :: value && std :: is_constructible <vtype, atypes...> :: value> * = nullptr> static inline variant construct(atypes && ...);
    };
};

#endif
