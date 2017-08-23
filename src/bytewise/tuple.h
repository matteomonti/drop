// Forward declarations

namespace bytewise
{
    template <typename...> class tuple;
};

#if !defined(__forward__) && !defined(__drop__bytewise__tuple__h)
#define __drop__bytewise__tuple__h

// Libraries

#include <type_traits>

// Forward includes

#define __forward__
#include "buffer.h"
#undef __forward__

// Includes

#include "bytewise.h"
#include "utils/template/is_callable.h"
#include "traits.h"

namespace bytewise
{
    template <typename ltype> class tuple <ltype>
    {
        // Asserts

        static_assert(traits <ltype> :: enabled || std :: is_same <ltype, buffer> :: value, "Bytewise tuple can only be constructed with bytewise-compliant types.");

        // Self

        typedef tuple self;

        // Members

        ltype _item;

        // Bytewise

        $bytewise(_item);

    public:

        // Constructors

        tuple();
        tuple(const ltype &);

        // Getters

        template <size_t index, std :: enable_if_t <index == 0> * = nullptr> auto & get();
        template <size_t index, std :: enable_if_t <index == 0> * = nullptr> const auto & get() const;

        // Methods

        template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, types & ..., ltype &> :: value> * = nullptr> void visit(const lambda &, types & ...);
        template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, const types & ..., const ltype &> :: value> * = nullptr> void visit(const lambda &, const types & ...) const;
    };

    template <typename ftype, typename stype, typename... ttypes> class tuple <ftype, stype, ttypes...>
    {
        // Asserts

        static_assert(traits <ftype> :: enabled || std :: is_same <ftype, buffer> :: value, "Bytewise tuple can only be constructed with bytewise-compliant types.");

        // Self

        typedef tuple self;

        // Members

        ftype _item;
        tuple <stype, ttypes...> _tail;

        // Bytewise

        $bytewise(_item);
        $bytewise(_tail);

    public:

        // Constructors

        tuple();
        tuple(const ftype &, const stype &, const ttypes & ...);

        // Getters

        template <size_t index, std :: enable_if_t <index == 0> * = nullptr> auto & get();
        template <size_t index, std :: enable_if_t <index == 0> * = nullptr> const auto & get() const;

        template <size_t index, std :: enable_if_t <(index > 0 && index < sizeof...(ttypes) + 2)> * = nullptr> auto & get();
        template <size_t index, std :: enable_if_t <(index > 0 && index < sizeof...(ttypes) + 2)> * = nullptr> const auto & get() const;

        // Methods

        template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, types & ..., ftype &, stype &, ttypes & ...> :: value> * = nullptr> void visit(const lambda &, types & ...);
        template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, const types & ..., const ftype &, const stype &, const ttypes & ...> :: value> * = nullptr> void visit(const lambda &, const types & ...) const;
    };
};

#endif
