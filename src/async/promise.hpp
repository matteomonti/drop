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

template <typename type> promise <type> :: arc :: arc()
{
}

// Getters

template <typename type> const type & promise <type> :: arc :: value() const
{
    return *(this->_value);
}

// promise

// Constructors

template <typename type> promise <type> :: promise() : _arc(new arc)
{
}

#endif
