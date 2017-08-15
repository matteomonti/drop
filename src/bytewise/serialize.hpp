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
#include "tuple.hpp"

namespace bytewise
{
    // allocator <true, dummy>

    template <typename ttype, size_t pad_beg, size_t pad_end> template <bool dummy> void serializer <ttype, pad_beg, pad_end> :: allocator <true, dummy> :: alloc(type & bytes, const ttype & target)
    {
        bytes.alloc(scanners :: arithmetic <ttype> :: type :: size + sizeof(uint32_t) * scanners :: buffer <ttype> :: type :: size + visitors :: buffer <ttype> :: size(target) + pad_beg + pad_end);
    }

    template <typename ttype, size_t pad_beg, size_t pad_end> template <bool dummy> void serializer <ttype, pad_beg, pad_end> :: allocator <true, dummy> :: crop(type & bytes, const size_t & cursor)
    {
        bytes.alloc(cursor);
    }

    // allocator <false, dummy>

    template <typename ttype, size_t pad_beg, size_t pad_end> template <bool dummy> void serializer <ttype, pad_beg, pad_end> :: allocator <false, dummy> :: alloc(type &, const ttype &)
    {
    }

    template <typename ttype, size_t pad_beg, size_t pad_end> template <bool dummy> void serializer <ttype, pad_beg, pad_end> :: allocator <false, dummy> :: crop(type &, const size_t &)
    {
    }

    // allocator <false, dummy>

    // serializer

    // Constructors

    template <typename ttype, size_t pad_beg, size_t pad_end> template <typename otype, utils :: enable_in_t <otype, ttype> *> serializer <ttype, pad_beg, pad_end> :: serializer(otype && target) : _cursor(pad_beg)
    {
        visitors :: on :: read(target);
        allocator <(traits <ttype> :: size == 0), false> :: alloc(this->_bytes, target);

        visitors :: arithmetic <ttype> :: read(target, *this);
        visitors :: buffer <ttype> :: read(target, *this);

        allocator <(traits <ttype> :: size == 0), false> :: crop(this->_bytes, this->_cursor + pad_end);
    }

    // Getters

    template <typename ttype, size_t pad_beg, size_t pad_end> auto serializer <ttype, pad_beg, pad_end> :: finalize() const
    {
        return this->_bytes;
    }

    // Methods

    template <typename ttype, size_t pad_beg, size_t pad_end> template <size_t rsize> void serializer <ttype, pad_beg, pad_end> :: read(const char (&bytes)[rsize])
    {
        memcpy(((char *) this->_bytes) + this->_cursor, bytes, rsize);
        this->_cursor += rsize;
    }

    template <typename ttype, size_t pad_beg, size_t pad_end> void serializer <ttype, pad_beg, pad_end> :: read(const buffer & buffer)
    {
        bsize bsize = buffer.size();
        this->_cursor += bsize.write(this->_bytes + this->_cursor);

        memcpy(this->_bytes + this->_cursor, buffer, buffer.size());
        this->_cursor += buffer.size();
    }

    // Functions

    template <typename... opts, typename type, std :: enable_if_t <traits <type> :: arithmetic> *> auto serialize(type && target)
    {
        static constexpr size_t size = sizeof(std :: remove_const_t <std :: remove_reference_t <type>>);

        block <size + options :: template pack <opts...> :: pad :: beg + options :: template pack <opts...> :: pad :: end> buffer;
        endianess :: translate(reinterpret_cast <char (&)[size]> (*((char *) buffer + options :: template pack <opts...> :: pad :: beg)), reinterpret_cast <const char (&)[size]> (target));
        return buffer;
    }

    template <typename... opts, typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic)> *> auto serialize(type && target)
    {
        return (serializer <std :: remove_const_t <std :: remove_reference_t <type>>, options :: template pack <opts...> :: pad :: beg, options :: template pack <opts...> :: pad :: end> (target)).finalize();
    }

    template <typename... opts, typename ftype, typename stype, typename... ttypes> auto serialize(ftype && first, stype && second, ttypes && ... tail)
    {
        return serialize <opts...> (tuple <std :: remove_const_t <std :: remove_reference_t <ftype>>, std :: remove_const_t <std :: remove_reference_t <stype>>, std :: remove_const_t <std :: remove_reference_t <ttypes>>...> (first, second, tail...));
    }
};

#endif
