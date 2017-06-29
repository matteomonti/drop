#ifndef __drop__data__variant__hpp
#define __drop__data__variant__hpp

// Includes

#include "variant.h"

namespace data
{
    // iterator <sizeof...(types), dummy>

    template <typename... types> template <bool dummy> template <typename lambda> void variant_base <types...> :: visit :: iterator <sizeof...(types), dummy> :: run(variant_base <types...> &, lambda &&)
    {
    }

    template <typename... types> template <bool dummy> template <typename lambda> void variant_base <types...> :: visit :: iterator <sizeof...(types), dummy> :: run(const variant_base <types...> &, lambda &&)
    {
    }

    // iterator <index, dummy>

    template <typename... types> template <size_t index, bool dummy> template <typename lambda> void variant_base <types...> :: visit :: iterator <index, dummy> :: run(variant_base <types...> & variant, lambda && callback)
    {
        if(index == variant._typeid)
            callback(reinterpret_cast <typename type <index> :: vtype &> (variant._bytes));
        else
            iterator <index + 1, dummy> :: run(variant, callback);
    }

    template <typename... types> template <size_t index, bool dummy> template <typename lambda> void variant_base <types...> :: visit :: iterator <index, dummy> :: run(const variant_base <types...> & variant, lambda && callback)
    {
        if(index == variant._typeid)
            callback(reinterpret_cast <const typename type <index> :: vtype &> (variant._bytes));
        else
            iterator <index + 1, dummy> :: run(variant, callback);
    }

    // visit

    template <typename... types> template <typename lambda> void variant_base <types...> :: visit :: run(variant_base <types...> & variant, lambda && callback)
    {
        iterator <0, false> :: run(variant, callback);
    }

    template <typename... types> template <typename lambda> void variant_base <types...> :: visit :: run(const variant_base <types...> & variant, lambda && callback)
    {
        iterator <0, false> :: run(variant, callback);
    }

    // variant

    // Private constructors

    template <typename... types> variant_base <types...> :: variant_base()
    {
    }

    // Constructors

    template <typename... types> variant_base <types...> :: variant_base(variant_base && that)
    {
        this->_typeid = that._typeid;

        that.visit([&](auto && value)
        {
            typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
            new (&(this->_bytes)) vtype(std :: move(value));
        });
    }

    template <typename... types> variant_base <types...> :: variant_base(const variant_base & that)
    {
        this->_typeid = that._typeid;

        that.visit([&](auto && value)
        {
            typedef std :: remove_const_t <std :: remove_reference_t <decltype(value)>> vtype;
            new (&(this->_bytes)) vtype(value);
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

    template <typename... types> template <typename lambda> void variant_base <types...> :: visit(lambda && callback)
    {
        visit :: run(*this, callback);
    }

    template <typename... types> template <typename lambda> void variant_base <types...> :: visit(lambda && callback) const
    {
        visit :: run(*this, callback);
    }

    // Static methods

    template <typename... types> template <typename vtype, typename... atypes, std :: enable_if_t <utils :: in <vtype, types...> :: value && std :: is_constructible <vtype, atypes...> :: value> *> inline variant_base <types...> variant_base <types...> :: construct(atypes && ... args)
    {
        variant_base variant;
        variant._typeid = id <vtype> :: value;
        new (&(variant._bytes)) vtype(std :: forward <atypes> (args)...);
        return variant;
    }
}
#endif
