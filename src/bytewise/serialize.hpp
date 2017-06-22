#ifndef __drop__bytewise__serialize__hpp
#define __drop__bytewise__serialize__hpp

// Includes

#include "serialize.h"
#include "block.hpp"
#include "visitors/arithmetic.hpp"
#include "visitors/buffer.hpp"

namespace bytewise
{
    // Constructors

    template <typename type> serialize <type> :: serialize(const type & target) : _cursor(0)
    {
        typedef decltype(this->_bytes) atype;

        struct yallocator
        {
            static inline void run(atype & bytes, const type & target)
            {
                bytes.alloc(scanners :: arithmetic <type> :: type :: size + sizeof(uint32_t) * scanners :: buffer <type> :: type :: size + visitors :: buffer <type> :: size(target));
            }
        };

        struct nallocator
        {
            static inline void run(atype &, const type &)
            {
            }
        };

        std :: conditional <fix_alloc, nallocator, yallocator> :: type :: run(this->_bytes, target);

        visitors :: arithmetic <type> :: read(target, *this);
        visitors :: buffer <type> :: read(target, *this);
    }

    // Private methods

    template <typename type> template <size_t rsize> void serialize <type> :: read(const char (&bytes)[rsize])
    {
        memcpy(this->_bytes + this->_cursor, bytes, rsize);
        this->_cursor += rsize;
    }

    template <typename type> void serialize <type> :: read(const buffer & buffer)
    {
        uint32_t size = buffer.size();
        endianess :: translate(reinterpret_cast <char (&)[4]> (*(reinterpret_cast <uint32_t *> (this->_bytes + this->_cursor))), reinterpret_cast <const char (&)[sizeof(uint32_t)]> (size));

        this->_cursor += sizeof(uint32_t);
        memcpy(this->_bytes + this->_cursor, buffer, buffer.size());
    }

    // Casting

    template <typename type> serialize <type> :: operator const typename std :: conditional <serialize <type> :: fix_alloc, block <serialize <type> :: size>, buffer> :: type & ()
    {
        return this->_bytes;
    }
};

#endif
