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

    template <typename ttype> serializer <ttype> :: serializer(const ttype & target) : _cursor(0)
    {
        typedef decltype(this->_bytes) atype;

        struct yallocator
        {
            static inline void run(atype & bytes, const ttype & target)
            {
                bytes.alloc(scanners :: arithmetic <ttype> :: type :: size + sizeof(uint32_t) * scanners :: buffer <ttype> :: type :: size + visitors :: buffer <ttype> :: size(target));
            }
        };

        struct nallocator
        {
            static inline void run(atype &, const ttype &)
            {
            }
        };

        std :: conditional <(size > 0), nallocator, yallocator> :: type :: run(this->_bytes, target);

        visitors :: arithmetic <ttype> :: read(target, *this);
        visitors :: buffer <ttype> :: read(target, *this);
    }

    // Getters

    template <typename ttype> auto serializer <ttype> :: finalize() const
    {
        return this->_bytes;
    }

    // Methods

    template <typename ttype> template <size_t rsize> void serializer <ttype> :: read(const char (&bytes)[rsize])
    {
        memcpy(this->_bytes + this->_cursor, bytes, rsize);
        this->_cursor += rsize;
    }

    template <typename ttype> void serializer <ttype> :: read(const buffer & buffer)
    {
        uint32_t size = buffer.size();
        endianess :: translate(reinterpret_cast <char (&)[4]> (*(reinterpret_cast <uint32_t *> (this->_bytes + this->_cursor))), reinterpret_cast <const char (&)[sizeof(uint32_t)]> (size));

        this->_cursor += sizeof(uint32_t);
        memcpy(this->_bytes + this->_cursor, buffer, buffer.size());
    }

    // Functions

    template <typename type> auto serialize(const type & target)
    {
        return (serializer <type> (target)).finalize();
    }
};

#endif
