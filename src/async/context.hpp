#ifndef __drop__async__context__hpp
#define __drop__async__context__hpp

// Includes

#include "context.h"
#include "promise.hpp"

namespace async
{
    // Constructors

    template <typename type, typename lambda> context <type, lambda> :: context(const lambda & kernel) : _kernel(kernel), _entrypoint(-1), _handlers{.size = 0}
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
        assert(this->_handlers.size);
        this->_handlers.size--;
    }

    template <typename type, typename lambda> void context <type, lambda> :: handler(const ssize_t & entrypoint)
    {
        assert(this->_handlers.size < settings :: handlers);
        this->_handlers.entrypoints[this->_handlers.size++] = entrypoint;
    }

    template <typename type, typename lambda> void context <type, lambda> :: rethrow()
    {
        std :: rethrow_exception(this->_exception);
    }

    template <typename type, typename lambda> typename context <type, lambda> :: exit context <type, lambda> :: leave(const ssize_t & entrypoint, const class :: promise <void> & promise)
    {
        this->_entrypoint = entrypoint;

        if(promise.resolved())
        {
            return exit{.resume = true};
        }
        else
        {
            promise.then([this]()
            {
                this->run();
            }).except([this](const std :: exception_ptr & exception)
            {
                this->_exception = exception;
                this->run();
            });

            return exit();
        }
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
        exit status;

        do
        {
            if(this->_exception)
            {
                if(this->_handlers.size)
                {
                    this->_entrypoint = this->_handlers.entrypoints[this->_handlers.size - 1];
                    this->_handlers.size--;
                }
                else
                {
                    this->_promise.reject(this->_exception);
                    delete this;
                    return;
                }
            }

            try
            {
                status = this->_kernel(*this);
            }
            catch(...)
            {
                this->_exception = std :: current_exception();
                status.resume = true;
            }
        }
        while(status.resume);
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
