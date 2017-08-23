#ifndef __drop__utils__template__function__hpp
#define __drop__utils__template__function__hpp

// Includes

#include "function.h"

namespace utils
{
    // wrapper

    // Constructors

    template <typename ret_type, typename... types> template <typename lambda> function <ret_type (types...)> :: wrapper <lambda> :: wrapper(const lambda & functor) : _functor(functor)
    {
    }

    // Operators

    template <typename ret_type, typename... types> template <typename lambda> ret_type function <ret_type (types...)> :: wrapper <lambda> :: operator () (types && ... args)
    {
        return this->_functor(std :: forward <types> (args)...);
    }

    // function

    // Constructors

    template <typename ret_type, typename... types> function <ret_type (types...)> :: function()
    {
    }

    template <typename ret_type, typename... types> template <typename lambda, std :: enable_if_t <is_callable <lambda, types...> :: value && std :: is_same <std :: result_of_t <lambda(types...)>, ret_type> :: value> *> function <ret_type (types...)> :: function(const lambda & functor) : _functor(new wrapper <lambda> (functor))
    {
    }

    // Methods

    template <typename ret_type, typename... types> void function <ret_type (types...)> :: reset()
    {
        this->_functor.reset();
    }

    // Operators

    template <typename ret_type, typename... types> ret_type function <ret_type (types...)> :: operator () (types && ... args) const
    {
        return (*(this->_functor))(std :: forward <types> (args)...);
    }

    template <typename ret_type, typename... types> template <typename lambda, std :: enable_if_t <is_callable <lambda, types...> :: value && std :: is_same <std :: result_of_t <lambda(types...)>, ret_type> :: value> *> void function <ret_type (types...)> :: operator = (const lambda & functor)
    {
        this->_functor.reset(new wrapper <lambda> (functor));
    }

    // Operators

    template <typename ret_type, typename... types> function <ret_type (types...)> :: operator bool () const
    {
        return (bool) (this->_functor);
    }
};

#endif
