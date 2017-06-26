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
    // overflow

    template <typename ttype> const char * deserializer <ttype> :: overflow :: what() const noexcept
    {
        return "Buffer overflow: reading beyond the end of buffer.";
    };

    // deserializer

    // Constructors

    template <typename ttype> deserializer <ttype> :: deserializer(const type & bytes) : _bytes(bytes), _cursor(0)
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
        struct yexcept
        {
            static inline void check(const type & bytes, const size_t & cursor)
            {
                if(bytes.size() < cursor + rsize)
                    throw overflow();
            }
        };

        struct nexcept
        {
            static inline void check(const type &, const size_t &)
            {
            }
        };

        std :: conditional <(size == 0), yexcept, nexcept> :: type :: check(this->_bytes, this->_cursor);

        memcpy(bytes, this->_bytes + this->_cursor, rsize);
        this->_cursor += rsize;
    }

    template <typename ttype> void deserializer <ttype> :: write(buffer & buffer)
    {
        bsize bsize(this->_bytes + this->_cursor, this->_bytes.size() - this->_cursor);

        if(bsize.value() == -1)
            throw overflow();

        this->_cursor += bsize.bytes();

        if(this->_bytes.size() < this->_cursor + bsize.value())
            throw overflow();

        buffer.alloc(bsize.value());
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
