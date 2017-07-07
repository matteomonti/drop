#ifndef __drop__async__context__hpp
#define __drop__async__context__hpp

// Includes

#include "context.h"
#include "promise.hpp"
#include "data/optional.hpp"

namespace async
{
    // Constructors

    template <typename lambda> context <lambda> :: context(const lambda & kernel) : _kernel(kernel)
    {
    }

    // Methods

    template <typename lambda> void context <lambda> :: run()
    {
        this->_kernel(*this);
    }

    // Functions

    template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <lambda> &> :: value> *> context <lambda> * contextualize(const lambda & kernel)
    {
        return new context <lambda> (kernel);
    }
};

#endif
