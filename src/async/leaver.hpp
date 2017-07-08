#ifndef __drop__async__leaver__hpp
#define __drop__async__leaver__hpp

// Includes

#include "leaver.h"
#include "context.hpp"

namespace async
{
    // Constructors

    template <typename type, typename lambda, typename ttype> leaver <type, lambda, ttype> :: leaver(context <type, lambda> & context, const ssize_t & entrypoint, ttype & target) : _context(context), _entrypoint(entrypoint), _target(target)
    {
    }

    // Operators

    template <typename type, typename lambda, typename ttype> auto leaver <type, lambda, ttype> :: operator = (const promise <ttype> & promise) const
    {
        return this->_context.leave(this->_entrypoint, this->_target, promise);
    }

    // Functions

    template <typename type, typename lambda, typename ttype> leaver <type, lambda, ttype> leave(context <type, lambda> & context, const ssize_t & entrypoint, ttype & target)
    {
        return leaver <type, lambda, ttype> (context, entrypoint, target);
    }
};

#endif
