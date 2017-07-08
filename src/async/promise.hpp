#ifndef __drop__async__promise__hpp
#define __drop__async__promise__hpp

// Includes

#include "promise.h"

// callback_base

template <typename type> promise <type> :: callback_base :: ~callback_base()
{
}

// callback <lambda, false>

// Constructors

template <typename type> template <typename lambda> promise <type> :: callback <lambda, false> :: callback(const lambda & callback) : _callback(callback)
{
}

// Getters

template <typename type> template <typename lambda> void promise <type> :: callback <lambda, false> :: promise() const
{
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: callback <lambda, false> :: run(const arc & arc)
{
    arc.call(this->_callback);
}

// callback <lambda, true>

// Constructors

template <typename type> template <typename lambda> promise <type> :: callback <lambda, true> :: callback(const lambda & callback) : _callback(callback)
{
}

// Getters

template <typename type> template <typename lambda> typename promise <type> :: template callback <lambda, true> :: chain promise <type> :: callback <lambda, true>  :: promise() const
{
    return this->_promise;
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: callback <lambda, true> :: run(const arc & arc)
{
    this->_promise.alias(arc.call(this->_callback));
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

template <typename type> template <bool dummy> template <typename lambda> auto promise <type> :: arc_base <void, dummy> :: call(const lambda & callback) const
{
    return callback();
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

template <typename type> template <typename ptype, bool dummy> template <typename lambda> auto promise <type> :: arc_base <ptype, dummy> :: call(const lambda & callback) const
{
    return callback(*(this->_value));
}

// Private methods

template <typename type> template <typename ptype, bool dummy> void promise <type> :: arc_base <ptype, dummy> :: resolve(const ptype & value)
{
    this->_value = value;
}

// arc

// Constructors

template <typename type> promise <type> :: arc :: arc() : _size(0)
{
    memset(this->_callbacks, '\0', sizeof(void *) * settings :: callbacks);
}

// Methods

template <typename type> template <typename lambda> typename promise <type> :: template traits <lambda> :: then_type promise <type> :: arc :: then(const lambda & callback)
{
    if(this->_alias)
        return this->_alias->then(callback);
    else
    {
        if(this->resolved())
            return this->call(callback);
        else
        {
            assert(this->_size < settings :: callbacks);

            promise <type> :: callback <lambda> * handle = new promise <type> :: callback <lambda> (callback);
            this->_callbacks[this->_size++] = handle;
            return handle->promise();
        }
    }
}

template <typename type> template <typename... atypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(atypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(atypes) == 1)> *> void promise <type> :: arc :: resolve(const atypes & ... values)
{
    assert(!(this->resolved()));
    this->arc_base <type, false> :: resolve(values...);

    for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
    {
        this->_callbacks[i]->run(*this);
        delete this->_callbacks[i];
    }
}

template <typename type> void promise <type> :: arc :: alias(const promise & that)
{
    if(that._arc->resolved())
    {
        for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
        {
            this->_callbacks[i]->run(*(that._arc));
            delete this->_callbacks[i];
        }
    }
    else
    {
        assert(that._arc->_size + this->_size <= settings :: callbacks);

        for(size_t i = 0; i < this->_size; i++)
            that._arc->_callbacks[that._arc->_size++] = this->_callbacks[i];
    }

    this->_alias = that._arc;
}

// promise

// Constructors

template <typename type> promise <type> :: promise() : _arc(new arc)
{
}

// Methods

template <typename type> template <typename lambda, std :: enable_if_t <promise <type> :: template traits <lambda> :: valid> *> auto promise <type> :: then(const lambda & callback) const
{
    return this->_arc->then(callback);
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
