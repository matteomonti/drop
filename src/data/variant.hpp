#ifndef __drop__data__variant__hpp
#define __drop__data__variant__hpp

// Includes

#include "variant.h"

namespace data
{
    // caller <false, dummy>

    template <typename... types> template <bool dummy> template <typename dtype, typename lambda, typename... lambdas> void variant_base <types...> :: dispatch :: caller <false, dummy> :: run(dtype && item, lambda && callback, lambdas && ... tail)
    {
        dispatch :: run(item, tail...);
    }

    // caller <true, dummy>

    template <typename... types> template <bool dummy> template <typename dtype, typename lambda, typename... lambdas> void variant_base <types...> :: dispatch :: caller <true, dummy> :: run(dtype && item, lambda && callback, lambdas && ... tail)
    {
        callback(item);
    }

    // dispatch

    template <typename... types> template <typename dtype> void variant_base <types...> :: dispatch :: run(dtype && item)
    {
    }

    template <typename... types> template <typename dtype, typename lambda, typename... lambdas> void variant_base <types...> :: dispatch :: run(dtype && item, lambda && callback, lambdas && ... tail)
    {
        caller <utils :: is_callable <std :: remove_reference_t <lambda>, dtype> :: direct, false> :: run(item, callback, tail...);
    }

    // iterator <sizeof...(types), dummy>

    template <typename... types> template <bool dummy> template <typename... lambdas> void variant_base <types...> :: visit :: iterator <sizeof...(types), dummy> :: run(variant_base <types...> &, lambdas && ...)
    {
    }

    template <typename... types> template <bool dummy> template <typename... lambdas> void variant_base <types...> :: visit :: iterator <sizeof...(types), dummy> :: run(const variant_base <types...> &, lambdas && ...)
    {
    }

    // iterator <index, dummy>

    template <typename... types> template <size_t index, bool dummy> template <typename... lambdas> void variant_base <types...> :: visit :: iterator <index, dummy> :: run(variant_base <types...> & variant, lambdas && ... callbacks)
    {
        if(index == variant._typeid)
            dispatch :: run(reinterpret_cast <typename type <index> :: vtype &> (variant._bytes), callbacks...);
        else
            iterator <index + 1, dummy> :: run(variant, callbacks...);
    }

    template <typename... types> template <size_t index, bool dummy> template <typename... lambdas> void variant_base <types...> :: visit :: iterator <index, dummy> :: run(const variant_base <types...> & variant, lambdas && ... callbacks)
    {
        if(index == variant._typeid)
            dispatch :: run(reinterpret_cast <const typename type <index> :: vtype &> (variant._bytes), callbacks...);
        else
            iterator <index + 1, dummy> :: run(variant, callbacks...);
    }

    // visit

    template <typename... types> template <typename... lambdas> void variant_base <types...> :: visit :: run(variant_base <types...> & variant, lambdas && ... callbacks)
    {
        iterator <0, false> :: run(variant, callbacks...);
    }

    template <typename... types> template <typename... lambdas> void variant_base <types...> :: visit :: run(const variant_base <types...> & variant, lambdas && ... callbacks)
    {
        iterator <0, false> :: run(variant, callbacks...);
    }

    // variant_base

    // Private constructors

    template <typename... types> variant_base <types...> :: variant_base()
    {
    }

    // Constructors

    template <typename... types> variant_base <types...> :: variant_base(const variant_base & that)
    {
        this->_typeid = that._typeid;

        that.visit([&](auto && value)
        {
            typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
            new (&(this->_bytes)) vtype(value);
        });
    }

    template <typename... types> variant_base <types...> :: variant_base(variant_base && that)
    {
        this->_typeid = that._typeid;

        that.visit([&](auto && value)
        {
            typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
            new (&(this->_bytes)) vtype(std :: move(value));
        });
    }

    // Destructor

    template <typename... types> variant_base <types...> :: ~variant_base()
    {
        this->visit([&](auto && value)
        {
            typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
            value.~vtype();
        });
    }

    // Methods

    template <typename... types> template <typename... lambdas> void variant_base <types...> :: visit(lambdas && ... callbacks)
    {
        visit :: run(*this, callbacks...);
    }

    template <typename... types> template <typename... lambdas> void variant_base <types...> :: visit(lambdas && ... callbacks) const
    {
        visit :: run(*this, callbacks...);
    }

    // Operators

    template <typename... types> variant_base <types...> & variant_base <types...> :: operator = (const variant_base & that)
    {
        if(this->_typeid == that._typeid)
        {
            that.visit([&](auto && value)
            {
                typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
                reinterpret_cast <vtype &> (this->_bytes) = value;
            });
        }
        else
        {
            this->visit([&](auto && value)
            {
                typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
                value.~vtype();
            });

            this->_typeid = that._typeid;

            that.visit([&](auto && value)
            {
                typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
                new (&(this->_bytes)) vtype(value);
            });
        }

        return (*this);
    }

    template <typename... types> variant_base <types...> & variant_base <types...> :: operator = (variant_base && that)
    {
        if(this->_typeid == that._typeid)
        {
            that.visit([&](auto && value)
            {
                typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
                reinterpret_cast <vtype &> (this->_bytes) = std :: move(value);
            });
        }
        else
        {
            this->visit([&](auto && value)
            {
                typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
                value.~vtype();
            });

            this->_typeid = that._typeid;

            that.visit([&](auto && value)
            {
                typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
                new (&(this->_bytes)) vtype(std :: move(value));
            });
        }

        return (*this);
    }

    // variant

    // Constructors

    template <typename... types> variant <types...> :: variant()
    {
    }

    // Static methods

    template <typename... types> template <typename vtype, typename... atypes, std :: enable_if_t <utils :: in <vtype, types...> :: value && std :: is_constructible <vtype, atypes...> :: value> *> inline variant <types...> variant <types...> :: construct(atypes && ... args)
    {
        variant variant;
        variant._typeid = variant_base <types...> :: template id <vtype> :: value;
        new (&(variant._bytes)) vtype(std :: forward <atypes> (args)...);
        return variant;
    }
}
#endif
