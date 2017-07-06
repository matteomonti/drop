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

template <typename type> template <typename lambda> void promise <type> :: callback <lambda, false> :: run(const type & value)
{
    this->_callback(value);
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

template <typename type> template <typename lambda> void promise <type> :: callback <lambda, true> :: run(const type & value)
{
    this->_promise.alias(this->_callback(value));
}

// arc

// Constructors

template <typename type> promise <type> :: arc :: arc() : _value(data :: null)
{
    memset(this->_callbacks, '\0', sizeof(void *) * settings :: callbacks);
}

// Methods

template <typename type> template <typename lambda> std :: conditional_t <promise <type> :: template is_promise <std :: result_of_t <lambda(const type &)>> :: value, std :: result_of_t <lambda(const type &)>, void> promise <type> :: arc :: then(const lambda & callback)
{
    if(this->_alias)
        return this->_alias->then(callback);
    else
    {
        if(this->_value)
            return callback(*(this->_value));
        else
        {
            assert(!(this->_callbacks[settings :: callbacks - 1]));

            for(size_t i = 0; i < settings :: callbacks; i++)
                if(!(this->_callbacks[i]))
                {
                    promise <type> :: callback <lambda> * handle = new promise <type> :: callback <lambda> (callback);
                    this->_callbacks[i] = handle;
                    return handle->promise();
                }
        }
    }
}

template <typename type> void promise <type> :: arc :: alias(const promise & that)
{
    if(that._arc->_value)
    {
        for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
        {
            this->_callbacks[i]->run(*(that._arc->_value));
            delete this->_callbacks[i];
        }
    }
    else
    {
        assert(!(that._arc->_callbacks[settings :: callbacks - 1]));

        size_t beg = 0;
        while(that._arc->_callbacks[beg]) beg++;

        for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
        {
            assert(!(that._arc->_callbacks[beg + i]));
            that._arc->_callbacks[beg + i] = this->_callbacks[i];
        }
    }

    this->_alias = that._arc;
}

template <typename type> void promise <type> :: arc :: resolve(const type & value)
{
    assert(!(this->_value));
    this->_value = value;

    for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
    {
        this->_callbacks[i]->run(*(this->_value));
        delete this->_callbacks[i];
    }
}

// promise

// Constructors

template <typename type> promise <type> :: promise() : _arc(new arc)
{
}

// Methods

template <typename type> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const type &> :: value> *> auto promise <type> :: then(const lambda & callback)
{
    return this->_arc->then(callback);
}

template <typename type> void promise <type> :: resolve(const type & value)
{
    this->_arc->resolve(value);
}

// Private methods

template <typename type> void promise <type> :: alias(const promise & that)
{
    this->_arc->alias(that);
}

#endif
