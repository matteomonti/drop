#ifndef __drop__bytewise__deserialize__hpp
#define __drop__bytewise__deserialize__hpp

// Includes

#include "deserialize.h"
#include "block.hpp"
#include "visitors/arithmetic.hpp"
#include "visitors/buffer.hpp"
#include "bsize.h"

namespace bytewise
{
    // Constructors

    template <typename ttype> deserializer <ttype> :: deserializer(const typename std :: conditional <(size > 0), block <size>, buffer> :: type & bytes) : _bytes(bytes), _cursor(0)
    {
        visitors :: arithmetic <ttype> :: write(this->_target, *this);
        visitors :: buffer <ttype> :: write(this->_target, *this);
    }

    // Getters

    template <typename ttype> ttype deserializer <ttype> :: finalize() const
    {
        return this->_target;
    }

    // Methods

    template <typename ttype> template <size_t rsize> void deserializer <ttype> :: write(char (&bytes)[rsize])
    {
        memcpy(bytes, this->_bytes + this->_cursor, rsize); // TODO: check for exceptions
        this->_cursor += rsize;
    }

    template <typename ttype> void deserializer <ttype> :: write(buffer & buffer)
    {
        bsize bsize(this->_bytes + this->_cursor, 4); // TODO: check for exceptions, allow only proper size

        this->_cursor += bsize.bytes();
        buffer.alloc(bsize.value()); // TODO: check for exceptions (value = -1)

        memcpy(buffer, this->_bytes + this->_cursor, bsize.value());
        this->_cursor += bsize.value();
    }

    // Functions

    template <typename type, typename std :: enable_if <std :: is_constructible <type> :: value> :: type *> type deserialize(const typename std :: conditional <(deserializer <type> :: size > 0), block <deserializer <type> :: size>, buffer> :: type & bytes)
    {
        return (deserializer <type> (bytes)).finalize();
    }
};

#endif
