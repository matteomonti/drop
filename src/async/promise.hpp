#ifndef __drop__async__promise__hpp
#define __drop__async__promise__hpp

// Includes

#include "promise.h"

// callback

// Constructors

template <typename type> template <typename lambda> promise <type> :: callback <lambda> :: callback(const lambda & callback) : _callback(callback)
{
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: callback <lambda> :: run(const promise <type> :: arc & arc)
{
    this->_callback(arc.value());
}

// arc

// Constructors

template <typename type> promise <type> :: arc :: arc() : _value(data :: null)
{
    memset(this->_callbacks, '\0', sizeof(void *) * settings :: callbacks);
}

// Getters

template <typename type> const type & promise <type> :: arc :: value() const
{
    return *(this->_value);
}

// Methods

template <typename type> template <typename lambda> void promise <type> :: arc :: then(const lambda & callback)
{
    if(this->_value)
        callback(*(this->_value));
    else
    {
        assert(!(this->_callbacks[settings :: callbacks - 1]));

        for(size_t i = 0; i < settings :: callbacks; i++)
            if(!(this->_callbacks[i]))
            {
                this->_callbacks[i] = new promise <type> :: callback <lambda> (callback);
                break;
            }
    }
}

template <typename type> void promise <type> :: arc :: resolve(const type & value)
{
    assert(!(this->_value));
    this->_value = value;

    for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
        this->_callbacks[i]->run(*this);
}

// promise

// Constructors

template <typename type> promise <type> :: promise() : _arc(new arc)
{
}

// Methods

template <typename type> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const type &> :: value> *> void promise <type> :: then(const lambda & callback)
{
    this->_arc->then(callback);
}

template <typename type> void promise <type> :: resolve(const type & value)
{
    this->_arc->resolve(value);
}

#endif
