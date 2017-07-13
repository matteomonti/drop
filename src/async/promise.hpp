#ifndef __drop__async__promise__hpp
#define __drop__async__promise__hpp

// Includes

#include "promise.h"

// resolve_callback_base

// Destructor

template <typename type> promise <type> :: resolve_callback_base :: ~resolve_callback_base()
{
}

// resolve_callback <lambda, false>

// Constructors

template <typename type> template <typename lambda> promise <type> :: resolve_callback <lambda, false> :: resolve_callback(const lambda & callback) : _callback(callback)
{
}

// Getters

template <typename type> template <typename lambda> void promise <type> :: resolve_callback <lambda, false> :: promise() const
{
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: resolve_callback <lambda, false> :: run(const arc & arc)
{
    arc.call(this->_callback);
}

template <typename type> template <typename lambda> bool promise <type> :: resolve_callback <lambda, false> :: reject(const std :: exception_ptr & exception)
{
    return false;
}

// resolve_callback <lambda, true>

// Constructors

template <typename type> template <typename lambda> promise <type> :: resolve_callback <lambda, true> :: resolve_callback(const lambda & callback) : _callback(callback)
{
}

// Getters

template <typename type> template <typename lambda> typename promise <type> :: template resolve_callback <lambda, true> :: chain promise <type> :: resolve_callback <lambda, true>  :: promise() const
{
    return this->_promise;
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: resolve_callback <lambda, true> :: run(const arc & arc)
{
    this->_promise.alias(arc.call(this->_callback));
}

template <typename type> template <typename lambda> bool promise <type> :: resolve_callback <lambda, true> :: reject(const std :: exception_ptr & exception)
{
    this->_promise.reject(exception);
    return true;
}

// reject_callback_base

// Destructor

template <typename type> promise <type> :: reject_callback_base :: ~reject_callback_base()
{
}

// reject_callback

// Constructors

template <typename type> template <typename lambda> promise <type> :: reject_callback <lambda> :: reject_callback(const lambda & callback) : _callback(callback)
{
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: reject_callback <lambda> :: run(const std :: exception_ptr & value)
{
    this->_callback(value);
}

// arc_base <void, dummy>

// Constructors

template <typename type> template <bool dummy> promise <type> :: arc_base <void, dummy> :: arc_base() : _resolved(false)
{
}

// Getters

template <typename type> template <bool dummy> const bool & promise <type> :: arc_base <void, dummy> :: resolved() const
{
    return this->_resolved;
}

// Methods

template <typename type> template <bool dummy> template <typename lambda> auto promise <type> :: arc_base <void, dummy> :: call(const lambda & resolve_callback) const
{
    return resolve_callback();
}

// Private methods

template <typename type> template <bool dummy> void promise <type> :: arc_base <void, dummy> :: resolve()
{
    this->_resolved = true;
}

// arc_base <ptype, dummy>

// Constructors

template <typename type> template <typename ptype, bool dummy> promise <type> :: arc_base <ptype, dummy> :: arc_base() : _value(data :: null)
{
}

// Getters

template <typename type> template <typename ptype, bool dummy> const bool & promise <type> :: arc_base <ptype, dummy> :: resolved() const
{
    return this->_value;
}

// Methods

template <typename type> template <typename ptype, bool dummy> template <typename lambda> auto promise <type> :: arc_base <ptype, dummy> :: call(const lambda & resolve_callback) const
{
    return resolve_callback(*(this->_value));
}

// Private methods

template <typename type> template <typename ptype, bool dummy> void promise <type> :: arc_base <ptype, dummy> :: resolve(const ptype & value)
{
    this->_value = value;
}

// arc

// Constructors

template <typename type> promise <type> :: arc :: arc() : _size(0), _reject_callback(nullptr)
{
}

// Destructor

template <typename type> promise <type> :: arc :: ~arc()
{
    if(!(this->_alias))
    {
        if(this->_exception)
        {
            if(this->_reject_callback)
                this->_reject_callback->run(this->_exception);
            else
            {
                bool forwarded = false;

                for(size_t i = 0; i < this->_size; i++)
                    forwarded |= this->_resolve_callbacks[i]->reject(this->_exception);

                assert(forwarded);
            }
        }

        if(!(this->resolved()))
            for(size_t i = 0; i < this->_size; i++)
                delete this->_resolve_callbacks[i];

        if(this->_reject_callback)
            delete this->_reject_callback;
    }
}

// Methods

template <typename type> template <typename lambda> typename promise <type> :: template traits <lambda> :: then_type promise <type> :: arc :: then(const lambda & resolve_callback)
{
    if(this->_alias)
        return this->_alias->then(resolve_callback);
    else
    {
        if(this->resolved())
            return this->call(resolve_callback);
        else
        {
            assert(this->_size < settings :: resolve_callbacks);

            promise <type> :: resolve_callback <lambda> * handle = new promise <type> :: resolve_callback <lambda> (resolve_callback);
            this->_resolve_callbacks[this->_size++] = handle;
            return handle->promise();
        }
    }
}

template <typename type> template <typename lambda> void promise <type> :: arc :: except(const lambda & reject_callback)
{
    if(!(this->_reject_callback))
        this->_reject_callback = new promise <type> :: reject_callback <lambda> (reject_callback);
}

template <typename type> template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> *> void promise <type> :: arc :: resolve(const atypes & ... values)
{
    assert(!(this->resolved()) && !(this->_exception));
    this->arc_base <type, false> :: resolve(values...);

    for(size_t i = 0; i < this->_size; i++)
    {
        this->_resolve_callbacks[i]->run(*this);
        delete this->_resolve_callbacks[i];
    }
}

template <typename type> template <typename rtype> void promise <type> :: arc :: reject(const rtype & exception)
{
    this->reject(std :: make_exception_ptr(exception));
}

template <typename type> void promise <type> :: arc :: reject(const std :: exception_ptr & exception)
{
    assert(!(this->resolved()) && !(this->_exception));
    this->_exception = exception;
}

template <typename type> void promise <type> :: arc :: alias(const promise & that)
{
    assert(!(this->resolved()) && !(this->_exception));

    if(that._arc->resolved())
    {
        for(size_t i = 0; i < this->_size; i++)
        {
            this->_resolve_callbacks[i]->run(*(that._arc));
            delete this->_resolve_callbacks[i];
        }

        if(this->_reject_callback)
            delete this->_reject_callback;
    }
    else
    {
        if(!(that._arc->_reject_callback))
            that._arc->_reject_callback = this->_reject_callback;
        else if(this->_reject_callback)
            delete this->_reject_callback;

        if(that._arc->_exception && !(that._arc->_reject_callback))
            for(size_t i = 0; i < this->_size; i++)
                delete this->_resolve_callbacks[i];
        else
        {
            assert(that._arc->_size + this->_size <= settings :: resolve_callbacks);

            for(size_t i = 0; i < this->_size; i++)
                that._arc->_resolve_callbacks[that._arc->_size++] = this->_resolve_callbacks[i];
        }
    }

    this->_alias = that._arc;
}

template <typename type> void promise <type> :: arc :: lock()
{
    this->_mutex.lock();
}

template <typename type> void promise <type> :: arc :: unlock()
{
    this->_mutex.unlock();
}

// promise

// Constructors

template <typename type> promise <type> :: promise() : _arc(new arc)
{
}

// Methods

template <typename type> template <typename lambda, std :: enable_if_t <promise <type> :: template traits <lambda> :: valid && promise <type> :: template traits <lambda> :: chainable> *> auto promise <type> :: then(const lambda & resolve_callback) const
{
    this->_arc->lock();
    auto chain = this->_arc->then(resolve_callback);
    this->_arc->unlock();

    return chain;
}

template <typename type> template <typename lambda, std :: enable_if_t <promise <type> :: template traits <lambda> :: valid && !(promise <type> :: template traits <lambda> :: chainable)> *> auto promise <type> :: then(const lambda & resolve_callback) const
{
    this->_arc->lock();
    this->_arc->then(resolve_callback);
    this->_arc->unlock();

    return (*this);
}

template <typename type> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const std :: exception_ptr &> :: value> *> void promise <type> :: except(const lambda & reject_callback) const
{
    this->_arc->lock();
    this->_arc->except(reject_callback);
    this->_arc->unlock();
}

template <typename type> template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> *> void promise <type> :: resolve(const atypes & ... values) const
{
    this->_arc->lock();
    this->_arc->resolve(values...);
    this->_arc->unlock();
}

template <typename type> template <typename rtype> void promise <type> :: reject(const rtype & exception)
{
    this->_arc->lock();
    this->_arc->reject(exception);
    this->_arc->unlock();
}

// Private methods

template <typename type> void promise <type> :: alias(const promise & that)
{
    this->_arc->lock();
    that._arc->lock();

    this->_arc->alias(that);

    that._arc->unlock();
    this->_arc->unlock();
}

#endif
