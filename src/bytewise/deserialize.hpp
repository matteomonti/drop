#ifndef __drop__bytewise__deserialize__hpp
#define __drop__bytewise__deserialize__hpp

// Includes

#include "deserialize.h"
#include "block.hpp"
#include "visitors/arithmetic.hpp"
#include "visitors/buffer.hpp"
#include "visitors/on.hpp"
#include "bsize.h"
#include "tuple.hpp"

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
        visitors :: on :: write(this->_target);
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

        std :: conditional <(traits <ttype> :: size == 0), yexcept, nexcept> :: type :: check(this->_bytes, this->_cursor);

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

    template <typename type, size_t size, std :: enable_if_t <traits <type> :: arithmetic && (size >= sizeof(type))> *> type deserialize(const block <size> & bytes)
    {
        type target;
        endianess :: translate(reinterpret_cast <char (&)[sizeof(type)]> (target), reinterpret_cast <const char (&)[sizeof(type)]> (bytes));
        return target;
    }

    template <typename type, std :: enable_if_t <traits <type> :: arithmetic> *> type deserialize(const buffer & bytes)
    {
        if(bytes.size() < sizeof(type))
            throw typename deserializer <type> :: overflow();

        return deserialize <type> (reinterpret_cast <const block <sizeof(type)> &> (*((const char *) bytes)));
    }

    template <typename type, size_t size, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic) && (traits <type> :: size > 0) && (size >= traits <type> :: size)> *> type deserialize(const block <size> & bytes)
    {
        return (deserializer <std :: remove_const_t <std :: remove_reference_t <type>>> (reinterpret_cast <const block <traits <type> :: size> &> (bytes))).finalize();
    }

    template <typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic) && (traits <type> :: size > 0)> *> type deserialize(const buffer & bytes)
    {
        if(bytes.size() < traits <type> :: size)
            throw typename deserializer <type> :: overflow();

        return deserialize <type> (reinterpret_cast <const block <traits <type> :: size> &> (*((const char *) bytes)));
    }

    template <typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic) && (traits <type> :: size == 0)> *> type deserialize(const buffer & bytes)
    {
        return (deserializer <std :: remove_const_t <std :: remove_reference_t <type>>> (bytes)).finalize();
    }

    template <typename ftype, typename stype, typename... ttypes, typename btype> tuple <ftype, stype, ttypes...> deserialize(const btype & bytes)
    {
        return deserialize <tuple <ftype, stype, ttypes...>> (bytes);
    }
};

#endif
