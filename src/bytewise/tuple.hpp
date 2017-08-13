#ifndef __drop__bytewise__tuple__hpp
#define __drop__bytewise__tuple__hpp

// Includes

#include "tuple.h"

namespace bytewise
{
    // tuple <ltype>

    // Constructors

    template <typename ltype> tuple <ltype> :: tuple()
    {
    }

    template <typename ltype> tuple <ltype> :: tuple(const ltype & item) : _item(item)
    {
    }

    // Getters

    template <typename ltype> template <size_t index, std :: enable_if_t <index == 0> *> auto & tuple <ltype> :: get()
    {
        return this->_item;
    }

    template <typename ltype> template <size_t index, std :: enable_if_t <index == 0> *> const auto & tuple <ltype> :: get() const
    {
        return this->_item;
    }

    // Methods

    template <typename ltype> template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, types & ..., ltype &> :: value> *> void tuple <ltype> :: visit(const lambda & callback, types & ... items)
    {
        callback(items..., this->_item);
    }

    template <typename ltype> template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, const types & ..., const ltype &> :: value> *> void tuple <ltype> :: visit(const lambda & callback, const types & ... items) const
    {
        callback(items..., this->_item);
    }

    // tuple <first, second, tail...>

    // Constructors

    template <typename ftype, typename stype, typename... ttypes> tuple <ftype, stype, ttypes...> :: tuple()
    {
    }

    template <typename ftype, typename stype, typename... ttypes> tuple <ftype, stype, ttypes...> :: tuple(const ftype & first, const stype & second, const ttypes & ... tail) : _item(first), _tail(second, tail...)
    {
    }

    template <typename ftype, typename stype, typename... ttypes> template <size_t index, std :: enable_if_t <index == 0> *> auto & tuple <ftype, stype, ttypes...> :: get()
    {
        return this->_item;
    }

    template <typename ftype, typename stype, typename... ttypes> template <size_t index, std :: enable_if_t <index == 0> *> const auto & tuple <ftype, stype, ttypes...> :: get() const
    {
        return this->_item;
    }

    template <typename ftype, typename stype, typename... ttypes> template <size_t index, std :: enable_if_t <(index > 0 && index < sizeof...(ttypes) + 2)> *> auto & tuple <ftype, stype, ttypes...> :: get()
    {
        return this->_tail.template get <index - 1> ();
    }

    template <typename ftype, typename stype, typename... ttypes> template <size_t index, std :: enable_if_t <(index > 0 && index < sizeof...(ttypes) + 2)> *> const auto & tuple <ftype, stype, ttypes...> :: get() const
    {
        return this->_tail.template get <index - 1> ();
    }

    // Methods

    template <typename ftype, typename stype, typename... ttypes> template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, types & ..., ftype &, stype &, ttypes & ...> :: value> *> void tuple <ftype, stype, ttypes...> :: visit(const lambda & callback, types & ... items)
    {
        this->_tail.visit(callback, items..., this->_item);
    }

    template <typename ftype, typename stype, typename... ttypes> template <typename lambda, typename... types, std :: enable_if_t <utils :: is_callable <lambda, const types & ..., const ftype &, const stype &, const ttypes & ...> :: value> *> void tuple <ftype, stype, ttypes...> :: visit(const lambda & callback, const types & ... items) const
    {
        this->_tail.visit(callback, items..., this->_item);
    }
};

#endif
