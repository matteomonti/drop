#ifndef __drop__utils__misc__pnew__hpp
#define __drop__utils__misc__pnew__hpp

// Includes

#include "pnew.h"

namespace utils
{
    // item

    // Constructors

    template <typename type> pnew <type> :: item :: item(std :: aligned_storage_t <sizeof(type), alignof(type)> & item) : _item(&item)
    {
    }

    // Operators

    template <typename type> template <typename... atypes, std :: enable_if_t <std :: is_constructible <type, atypes...> :: value> *> void pnew <type> :: item :: operator () (atypes && ... args)
    {
        new (this->_item) type(std :: forward <atypes> (args)...);
    }

    // pnew

    // Constructors

    template <typename type> pnew <type> :: pnew(const size_t & size) : _items(new std :: aligned_storage_t <sizeof(type), alignof(type)> [size])
    {
    }

    // Operators

    template <typename type> typename pnew <type> :: item pnew <type> :: operator [] (const size_t & index)
    {
        return item(this->_items[index]);
    }

    // Casting

    template <typename type> pnew <type> :: operator type * ()
    {
        return reinterpret_cast <type *> (this->_items);
    }
};

#endif
