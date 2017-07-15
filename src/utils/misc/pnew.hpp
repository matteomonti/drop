#ifndef __drop__utils__misc__pnew__hpp
#define __drop__utils__misc__pnew__hpp

// Includes

#include "pnew.h"

namespace utils
{
    // iterator

    // Constructors

    template <typename type> pnew <type> :: factories :: uniform :: iterator :: iterator(const size_t & size) : _pnew(size), _size(size)
    {
    }

    // Operators

    template <typename type> template <typename... atypes, std :: enable_if_t <std :: is_constructible <type, atypes...> :: value> *> const typename pnew <type> :: factories :: uniform :: iterator & pnew <type> :: factories :: uniform :: iterator :: operator () (atypes && ... args) const
    {
        for(size_t i = 0; i < this->_size; i++)
            this->_pnew[i](std :: forward <atypes> (args)...);

        return (*this);
    }

    // Casting

    template <typename type> pnew <type> :: factories :: uniform :: iterator :: operator type * () const
    {
        return (type *) (this->_pnew);
    }

    // uniform

    template <typename type> typename pnew <type> :: factories :: uniform :: iterator pnew <type> :: factories :: uniform :: operator [] (const size_t & size)
    {
        return iterator(size);
    }

    // item

    // Constructors

    template <typename type> pnew <type> :: item :: item(std :: aligned_storage_t <sizeof(type), alignof(type)> & item) : _item(&item)
    {
    }

    // Operators

    template <typename type> template <typename... atypes, std :: enable_if_t <std :: is_constructible <type, atypes...> :: value> *> void pnew <type> :: item :: operator () (atypes && ... args) const
    {
        new (this->_item) type(std :: forward <atypes> (args)...);
    }

    // pnew

    // Constructors

    template <typename type> pnew <type> :: pnew(const size_t & size) : _items(new std :: aligned_storage_t <sizeof(type), alignof(type)> [size])
    {
    }

    // Operators

    template <typename type> typename pnew <type> :: item pnew <type> :: operator [] (const size_t & index) const
    {
        return item(this->_items[index]);
    }

    // Casting

    template <typename type> pnew <type> :: operator type * () const
    {
        return (type *) this->_items;
    }

    // Static members declarations

    template <typename type>  typename pnew <type> :: factories :: uniform pnew <type> :: uniform;

    // Functions

    template <typename type> void pdelete(type * array, const size_t & size)
    {
        for(size_t i = 0; i < size; i++)
            array[i].~type();

        delete [] reinterpret_cast <std :: aligned_storage_t <sizeof(type), alignof(type)> *> (array);
    }
};

#endif
