#ifndef __drop__data__optional__hpp
#define __drop__data__optional__hpp

// Includes

#include "optional.h"

namespace data
{
    // optional_base

    // Constructors

    template <typename type> optional_base <type> :: optional_base(class null) : _exists(false)
    {
        std :: cout << "Null constructor" << std :: endl;
    }

    template <typename type> template <typename... types, std :: enable_if_t <std :: is_constructible <type, types...> :: value> *> optional_base <type> :: optional_base(types && ... args) : _exists(true)
    {
        std :: cout << "Parametric constructor" << std :: endl;
        new (&(this->_bytes)) type(std :: forward <types> (args)...);
    }

    template <typename type> optional_base <type> :: optional_base(const optional_base & that) : _exists(that._exists)
    {
        std :: cout << "Copy constructor" << std :: endl;

        if(this->_exists)
            new (&(this->_bytes)) type(reinterpret_cast <const type &> (that._bytes));
    }

    template <typename type> optional_base <type> :: optional_base(optional_base && that) : _exists(that._exists)
    {
        std :: cout << "Move constructor" << std :: endl;

        if(this->_exists)
            new (&(this->_bytes)) type(std :: move(reinterpret_cast <type &&> (that._bytes)));
    }

    // Destructor

    template <typename type> optional_base <type> :: ~optional_base()
    {
        std :: cout << "Destructor" << std :: endl;

        if(this->_exists)
            (reinterpret_cast <type &> (this->_bytes)).~type();
    }

    // Operators

    template <typename type> type & optional_base <type> :: operator * ()
    {
        assert(this->_exists);
        return reinterpret_cast <type &> (this->_bytes);
    }

    template <typename type> const type & optional_base <type> :: operator * () const
    {
        assert(this->_exists);
        return reinterpret_cast <type &> (this->_bytes);
    }

    template <typename type> type * optional_base <type> :: operator -> ()
    {
        assert(this->_exists);
        return &(reinterpret_cast <type &> (this->_bytes));
    }

    template <typename type> const type * optional_base <type> :: operator -> () const
    {
        assert(this->_exists);
        return &(reinterpret_cast <type &> (this->_bytes));
    }

    template <typename type> optional_base <type> & optional_base <type> :: operator = (const optional_base <type> & that)
    {
        std :: cout << "Copy assignment" << std :: endl;

        if(that._exists)
        {
            if(this->_exists)
                reinterpret_cast <type &> (this->_bytes) = reinterpret_cast <const type &> (that._bytes);
            else
            {
                this->_exists = true;
                new (&(this->_bytes)) type(reinterpret_cast <const type &> (that._bytes));
            }
        }
        else if(this->_exists)
        {
            this->_exists = false;
            (reinterpret_cast <type &> (this->_bytes)).~type();
        }

        return (*this);
    }

    template <typename type> optional_base <type> & optional_base <type> :: operator = (optional_base <type> && that)
    {
        std :: cout << "Move assignment" << std :: endl;

        if(that._exists)
        {
            if(this->_exists)
                reinterpret_cast <type &> (this->_bytes) = std :: move(reinterpret_cast <type &&> (that._bytes));
            else
            {
                this->_exists = true;
                new (&(this->_bytes)) type(std :: move(reinterpret_cast <type &&> (that._bytes)));
            }
        }
        else if(this->_exists)
        {
            this->_exists = false;
            (reinterpret_cast <type &> (this->_bytes)).~type();
        }

        return (*this);
    }

    // Casting

    template <typename type> optional_base <type> :: operator const bool & ()
    {
        return this->_exists;
    }

    // optional

    // Constructors

    template <typename type> optional <type> :: optional(class null) : optional_base <type> (null)
    {
    }

    template <typename type> template <typename... types, typename std :: enable_if_t <std :: is_constructible <type, types...> :: value> *> optional <type> :: optional(types && ... args) : optional_base <type> (std :: forward <types> (args)...)
    {
    }
};

#endif
