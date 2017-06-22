#ifndef __drop__bytewise__serialize__hpp
#define __drop__bytewise__serialize__hpp

// Includes

#include "serialize.h"
#include "block.hpp"
#include "visitors/arithmetic.hpp"
#include "visitors/buffer.hpp"
#include "bsize.h"

namespace bytewise
{
    // Constructors

    template <typename ttype> serializer <ttype> :: serializer(const ttype & target) : _cursor(0)
    {
        typedef decltype(this->_bytes) atype;

        struct yallocator
        {
            static inline void alloc(atype & bytes, const ttype & target)
            {
                bytes.alloc(scanners :: arithmetic <ttype> :: type :: size + sizeof(uint32_t) * scanners :: buffer <ttype> :: type :: size + visitors :: buffer <ttype> :: size(target));
            }

            static inline void crop(atype & bytes, const size_t & cursor)
            {
                bytes.alloc(cursor);
            }
        };

        struct nallocator
        {
            static inline void alloc(atype &, const ttype &)
            {
            }

            static inline void crop(atype &, const size_t &)
            {
            }
        };

        std :: conditional <(size > 0), nallocator, yallocator> :: type :: alloc(this->_bytes, target);

        visitors :: arithmetic <ttype> :: read(target, *this);
        visitors :: buffer <ttype> :: read(target, *this);

        std :: conditional <(size > 0), nallocator, yallocator> :: type :: crop(this->_bytes, this->_cursor);
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
        bsize bsize = buffer.size();
        this->_cursor += bsize.write(this->_bytes + this->_cursor);

        memcpy(this->_bytes + this->_cursor, buffer, buffer.size());
        this->_cursor += buffer.size();
    }

    // Functions

    template <typename type> auto serialize(const type & target)
    {
        return (serializer <type> (target)).finalize();
    }
};

#endif
