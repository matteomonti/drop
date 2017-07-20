#ifndef __drop__chrono__timelock__hpp
#define __drop__chrono__timelock__hpp

// Includes

#include "timelock.h"

namespace chrono
{
    // entry

    // Operators

    template <typename type> bool timelock <type> :: entry :: operator < (const entry & rho) const
    {
        return this->expiry < rho.expiry;
    }

    template <typename type> bool timelock <type> :: entry :: operator > (const entry & rho) const
    {
        return this->expiry > rho.expiry;
    }

    // timelock

    // Methods

    template <typename type> void timelock <type> :: push(const type & value, const microtimestamp & expiry)
    {
        this->_entries.push(entry{.value = value, .expiry = expiry});
    }

    template <typename type> data :: optional <type> timelock <type> :: pop()
    {
        if(this->_entries.size() && this->_entries.peek().expiry < microtime())
            return this->_entries.pop().value;
        else
            return data :: null;
    }

    template <typename type> data :: optional <microtimestamp> timelock <type> :: next() const
    {
        if(this->_entries.size())
            return this->_entries.peek().expiry;
        else
            return data :: null;
    }
};

#endif
