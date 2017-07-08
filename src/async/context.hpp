#ifndef __drop__async__context__hpp
#define __drop__async__context__hpp

// Includes

#include "context.h"
#include "promise.hpp"

namespace async
{
    // Constructors

    template <typename type, typename lambda> context <type, lambda> :: context(const lambda & kernel) : _kernel(kernel), _entrypoint(0)
    {
    }

    // Getters

    template <typename type, typename lambda> const size_t & context <type, lambda> :: entrypoint() const
    {
        return this->_entrypoint;
    }

    template <typename type, typename lambda> const promise <type> & context <type, lambda> :: promise() const
    {
        return this->_promise;
    }

    // Methods

    template <typename type, typename lambda> typename context <type, lambda> :: exit context <type, lambda> :: leave(const size_t & entrypoint)
    {
        this->_entrypoint = entrypoint;
        return exit();
    }

    template <typename type, typename lambda> typename context <type, lambda> :: exit context <type, lambda> :: resolve(const type & response)
    {
        this->_promise.resolve(response);
        delete this;
        return exit();
    }

    template <typename type, typename lambda> void context <type, lambda> :: run()
    {
        this->_kernel(*this);
    }

    // Functions

    template <typename type, typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <type, lambda> &> :: value> *> context <type, lambda> * contextualize(const lambda & kernel)
    {
        return new context <type, lambda> (kernel);
    }
};

#endif
