#ifndef __drop__async__context__hpp
#define __drop__async__context__hpp

// Includes

#include "context.h"
#include "promise.hpp"

namespace async
{
    // Constructors

    template <typename type, typename lambda> context <type, lambda> :: context(const lambda & kernel) : _kernel(kernel), _entrypoint(-1), _handler(data :: null)
    {
    }

    // Getters

    template <typename type, typename lambda> const ssize_t & context <type, lambda> :: entrypoint() const
    {
        return this->_entrypoint;
    }

    template <typename type, typename lambda> const promise <type> & context <type, lambda> :: promise() const
    {
        return this->_promise;
    }

    // Methods

    template <typename type, typename lambda> void context <type, lambda> :: handler()
    {
        this->_handler = data :: null;
    }

    template <typename type, typename lambda> void context <type, lambda> :: handler(const ssize_t & entrypoint)
    {
        this->_handler = entrypoint;
    }

    template <typename type, typename lambda> void context <type, lambda> :: rethrow()
    {
        std :: rethrow_exception(this->_exception);
    }

    template <typename type, typename lambda> typename context <type, lambda> :: exit context <type, lambda> :: leave(const ssize_t & entrypoint, const class :: promise <void> & promise)
    {
        promise.then([this]()
        {
            this->run();
        }).except([this](const std :: exception_ptr & exception)
        {
            this->_exception = exception;
            this->run();
        });

        this->_entrypoint = entrypoint;
        return exit();
    }

    template <typename type, typename lambda> template <typename ttype> typename context <type, lambda> :: exit context <type, lambda> :: leave(const ssize_t & entrypoint, ttype & target, const class :: promise <ttype> & promise)
    {
        promise.then([&, this](const ttype & value)
        {
            target = value;
            this->run();
        }).except([this](const std :: exception_ptr & exception)
        {
            this->_exception = exception;
            this->run();
        });

        this->_entrypoint = entrypoint;
        return exit();
    }

    template <typename type, typename lambda> template <typename... rtypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(rtypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(rtypes) == 1)> *> typename context <type, lambda> :: exit context <type, lambda> :: resolve(const rtypes & ... response)
    {
        this->_promise.resolve(response...);
        delete this;
        return exit();
    }

    template <typename type, typename lambda> void context <type, lambda> :: run()
    {
        bool threw = false;

        if(this->_exception)
        {
            threw = true;

            if(this->_handler)
                this->_entrypoint = *(this->_handler);
            else
            {
                this->_promise.reject(this->_exception);
                delete this;
                return;
            }
        }

        try
        {
            this->_kernel(*this);
        }
        catch(...)
        {
            if(threw)
            {
                this->_promise.reject(std :: current_exception());
                delete this;
                return;
            }
            else
            {
                this->_exception = std :: current_exception();
                this->run();
            }
        }
    }

    // Functions

    template <typename type, typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <type, lambda> &> :: value> *> promise <type> contextualize(const lambda & kernel)
    {
        context <type, lambda> * context = new class :: async :: context <type, lambda> (kernel);
        promise <type> promise = context->promise();
        context->run();

        return promise;
    }
};

#endif
