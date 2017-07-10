#ifndef __drop__async__promise__hpp
#define __drop__async__promise__hpp

// Includes

#include "promise.h"

// resolve_callback_base

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
    memset(this->_resolve_callbacks, '\0', sizeof(void *) * settings :: resolve_callbacks);
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

template <typename type> template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> *> void promise <type> :: arc :: resolve(const atypes & ... values)
{
    assert(!(this->resolved()));
    this->arc_base <type, false> :: resolve(values...);

    for(size_t i = 0; i < settings :: resolve_callbacks && this->_resolve_callbacks[i]; i++)
    {
        this->_resolve_callbacks[i]->run(*this);
        delete this->_resolve_callbacks[i];
    }
}

template <typename type> void promise <type> :: arc :: alias(const promise & that)
{
    if(that._arc->resolved())
    {
        for(size_t i = 0; i < settings :: resolve_callbacks && this->_resolve_callbacks[i]; i++)
        {
            this->_resolve_callbacks[i]->run(*(that._arc));
            delete this->_resolve_callbacks[i];
        }
    }
    else
    {
        assert(that._arc->_size + this->_size <= settings :: resolve_callbacks);

        for(size_t i = 0; i < this->_size; i++)
            that._arc->_resolve_callbacks[that._arc->_size++] = this->_resolve_callbacks[i];
    }

    this->_alias = that._arc;
}

// promise

// Constructors

template <typename type> promise <type> :: promise() : _arc(new arc)
{
}

// Methods

template <typename type> template <typename lambda, std :: enable_if_t <promise <type> :: template traits <lambda> :: valid> *> auto promise <type> :: then(const lambda & resolve_callback) const
{
    return this->_arc->then(resolve_callback);
}

template <typename type> template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> *> void promise <type> :: resolve(const atypes & ... values) const
{
    this->_arc->resolve(values...);
}

// Private methods

template <typename type> void promise <type> :: alias(const promise & that)
{
    this->_arc->alias(that);
}

#endif
