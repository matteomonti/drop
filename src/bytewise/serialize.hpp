#ifndef __drop__bytewise__serialize__hpp
#define __drop__bytewise__serialize__hpp

// Includes

#include "serialize.h"
#include "block.hpp"
#include "visitors/arithmetic.hpp"
#include "visitors/buffer.hpp"
#include "visitors/on.hpp"
#include "bsize.h"
#include "endianess.hpp"

namespace bytewise
{
    // allocator <true, dummy>

    template <typename ttype> template <bool dummy> void serializer <ttype> :: allocator <true, dummy> :: alloc(type & bytes, const ttype & target)
    {
        bytes.alloc(scanners :: arithmetic <ttype> :: type :: size + sizeof(uint32_t) * scanners :: buffer <ttype> :: type :: size + visitors :: buffer <ttype> :: size(target));
    }

    template <typename ttype> template <bool dummy> void serializer <ttype> :: allocator <true, dummy> :: crop(type & bytes, const size_t & cursor)
    {
        bytes.alloc(cursor);
    }

    // allocator <false, dummy>

    template <typename ttype> template <bool dummy> void serializer <ttype> :: allocator <false, dummy> :: alloc(type &, const ttype &)
    {
    }

    template <typename ttype> template <bool dummy> void serializer <ttype> :: allocator <false, dummy> :: crop(type &, const size_t &)
    {
    }

    // allocator <false, dummy>

    // serializer

    // Constructors

    template <typename ttype> template <typename otype, utils :: enable_in_t <otype, ttype> *> serializer <ttype> :: serializer(otype && target) : _cursor(0)
    {
        visitors :: on :: read(target);
        allocator <(size == 0), false> :: alloc(this->_bytes, target);

        visitors :: arithmetic <ttype> :: read(target, *this);
        visitors :: buffer <ttype> :: read(target, *this);

        allocator <(size == 0), false> :: crop(this->_bytes, this->_cursor);

    }

    // Getters

    template <typename ttype> auto serializer <ttype> :: finalize() const
    {
        return this->_bytes;
    }

    // Methods

    template <typename ttype> template <size_t rsize> void serializer <ttype> :: read(const char (&bytes)[rsize])
    {
        memcpy(((char *) this->_bytes) + this->_cursor, bytes, rsize);
        this->_cursor += rsize;
    }

    template <typename ttype> void serializer <ttype> :: read(const buffer & buffer)
    {
        bsize bsize = buffer.size();
        this->_cursor += bsize.write(this->_bytes + this->_cursor);

        memcpy(this->_bytes + this->_cursor, buffer, buffer.size());
        this->_cursor += buffer.size();
    }

    // Functions

    template <typename type, std :: enable_if_t <traits <type> :: arithmetic> *> auto serialize(type && target)
    {
        static constexpr size_t size = sizeof(std :: remove_const_t <std :: remove_reference_t <type>>);

        block <size> buffer;
        endianess :: translate(reinterpret_cast <char (&)[size]> (buffer), reinterpret_cast <const char (&)[size]> (target));
        return buffer;
    }

    template <typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic)> *> auto serialize(type && target)
    {
        return (serializer <std :: remove_const_t <std :: remove_reference_t <type>>> (target)).finalize();
    }
};

#endif
