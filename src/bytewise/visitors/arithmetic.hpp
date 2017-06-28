#ifndef __drop__bytewise__visitors__arithmetic__hpp
#define __drop__bytewise__visitors__arithmetic__hpp

// Includes

#include "arithmetic.h"
#include "bytewise/endianess.hpp"

namespace bytewise :: visitors
{
    // iterator <vtype, mask <>>

    template <typename ttype> template <typename vtype> inline void arithmetic <ttype> :: iterator <vtype, mask <>> :: read(const ttype &, vtype &)
    {
    }

    template <typename ttype> template <typename vtype> inline void arithmetic <ttype> :: iterator <vtype, mask <>> :: write(ttype &, vtype &)
    {
    }

    // iterator <vtype, mask <range <beg, end, true>, tail...>>

    template <typename ttype> template <typename vtype, size_t beg, size_t end, typename... tail> inline void arithmetic <ttype> :: iterator <vtype, mask <range <beg, end, true>, tail...>> :: read(const ttype & target, vtype & visitor)
    {
        char buffer[end - beg];
        endianess :: swap(buffer, (reinterpret_cast <const selector <beg, end, false> &> (target)).value);

        visitor.read(buffer);
        iterator <vtype, mask <tail...>> :: read(target, visitor);
    }

    template <typename ttype> template <typename vtype, size_t beg, size_t end, typename... tail> inline void arithmetic <ttype> :: iterator <vtype, mask <range <beg, end, true>, tail...>> :: write(ttype & target, vtype & visitor)
    {
        char buffer[end - beg];
        visitor.write(buffer);

        endianess :: swap((reinterpret_cast <selector <beg, end, false> &> (target)).value, buffer);
        iterator <vtype, mask <tail...>> :: write(target, visitor);
    }

    // iterator <vtype, mask <range <beg, end, false>, tail...>>

    template <typename ttype> template <typename vtype, size_t beg, size_t end, typename... tail> inline void arithmetic <ttype> :: iterator <vtype, mask <range <beg, end, false>, tail...>> :: read(const ttype & target, vtype & visitor)
    {
        visitor.read((reinterpret_cast <const selector <beg, end, false> &> (target)).value);
        iterator <vtype, mask <tail...>> :: read(target, visitor);
    }

    template <typename ttype> template <typename vtype, size_t beg, size_t end, typename... tail> inline void arithmetic <ttype> :: iterator <vtype, mask <range <beg, end, false>, tail...>> :: write(ttype & target, vtype & visitor)
    {
        visitor.write((reinterpret_cast <selector <beg, end, false> &> (target)).value);
        iterator <vtype, mask <tail...>> :: write(target, visitor);
    }

    // arithmetic

    template <typename ttype> template <typename vtype> inline void arithmetic <ttype> :: read(const ttype & target, vtype & visitor)
    {
        iterator <vtype, typename scanners :: arithmetic <ttype> :: type :: compress :: type> :: read(target, visitor);
    }

    template <typename ttype> template <typename vtype> inline void arithmetic <ttype> :: write(ttype & target, vtype & visitor)
    {
        iterator <vtype, typename scanners :: arithmetic <ttype> :: type :: compress :: type> :: write(target, visitor);
    }
};

#endif
