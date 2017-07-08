#ifndef __drop__async__contextualizer__hpp
#define __drop__async__contextualizer__hpp

// Includes

#include "contextualizer.h"
#include "context.hpp"
#include "promise.hpp"

namespace async
{
    // Constructors

    template <typename lambda> contextualizer <lambda> :: contextualizer(const lambda & kernel) : _kernel(kernel)
    {
    }

    // Casting

    template <typename lambda> template <typename type> contextualizer <lambda> :: operator promise <type> () const
    {
        return contextualize <type> (this->_kernel);
    }

    // Functions

    template <typename lambda> auto contextualize(const lambda & kernel)
    {
        return contextualizer <lambda> (kernel);
    }
};

#endif
