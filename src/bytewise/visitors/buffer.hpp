#ifndef __drop__bytewise__visitors__buffer__hpp
#define __drop__bytewise__visitors__buffer__hpp

// Includes

#include "buffer.h"
#include "bytewise/proxy.hpp"

namespace bytewise :: visitors
{
    // resolver <vtype, path <>>

    template <typename ttype> template <typename vtype> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <>> :: read(const mtype & buffer, vtype & visitor)
    {
        visitor.read(buffer);
    }

    template <typename ttype> template <typename vtype> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <>> :: write(mtype & buffer, vtype & visitor)
    {
        visitor.write(buffer);
    }

    // iterator <-1, dummy>

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <bool dummy> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: iterator <-1, dummy> :: read(const mtype & member, vtype & visitor)
    {
    }

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <bool dummy> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: iterator <-1, dummy> :: write(mtype & member, vtype & visitor)
    {
    }

    // iterator <index, dummy>

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <ssize_t index, bool dummy> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: iterator <index, dummy> :: read(const mtype & member, vtype & visitor)
    {
        iterator <index - 1, false> :: read(member, visitor);
        unroll :: read(member[index], visitor);
    }

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <ssize_t index, bool dummy> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: iterator <index, dummy> :: write(mtype & member, vtype & visitor)
    {
        iterator <index - 1, false> :: write(member, visitor);
        unroll :: write(member[index], visitor);
    }

    // direct

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: direct :: read(const mtype & member, vtype & visitor)
    {
        resolver <vtype, path <tail...>> :: read(member, visitor);
    }

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: direct :: write(mtype & member, vtype & visitor)
    {
        resolver <vtype, path <tail...>> :: write(member, visitor);
    }

    // unroll

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: read(const mtype & member, vtype & visitor)
    {
        std :: conditional
        <
            std :: is_array <mtype> :: value,
            iterator <(ssize_t)(std :: extent <mtype> :: value) - 1, false>,
            direct
        > :: type :: read(member, visitor);
    }

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: unroll :: write(mtype & member, vtype & visitor)
    {
        std :: conditional
        <
            std :: is_array <mtype> :: value,
            iterator <(ssize_t)(std :: extent <mtype> :: value) - 1, false>,
            direct
        > :: type :: write(member, visitor);
    }

    // resolver <vtype, path <next, tail...>>

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: read(const mtype & member, vtype & visitor)
    {
        unroll :: read(proxy <mtype, next> :: get(member), visitor);
    }

    template <typename ttype> template <typename vtype, size_t next, size_t... tail> template <typename mtype> inline void buffer <ttype> :: resolver <vtype, path <next, tail...>> :: write(mtype & member, vtype & visitor)
    {
        unroll :: write(proxy <mtype, next> :: get(member), visitor);
    }

    // iterator <vtype, map <>>

    template <typename ttype> template <typename vtype> inline void buffer <ttype> :: iterator <vtype, map <>> :: read(const ttype &, vtype &)
    {
    }

    template <typename ttype> template <typename vtype> inline void buffer <ttype> :: iterator <vtype, map <>> :: write(ttype &, vtype &)
    {
    }

    // iterator <vtype, map <next, tail...>>

    template <typename ttype> template <typename vtype, typename next, typename... tail> inline void buffer <ttype> :: iterator <vtype, map <next, tail...>> :: read(const ttype & target, vtype & visitor)
    {
        resolver <vtype, next> :: read(target, visitor);
        iterator <vtype, map <tail...>> :: read(target, visitor);
    }

    template <typename ttype> template <typename vtype, typename next, typename... tail> inline void buffer <ttype> :: iterator <vtype, map <next, tail...>> :: write(ttype & target, vtype & visitor)
    {
        resolver <vtype, next> :: write(target, visitor);
        iterator <vtype, map <tail...>> :: write(target, visitor);
    }

    // buffer <ttype>

    template <typename ttype> template <typename vtype> inline void buffer <ttype> :: read(const ttype & target, vtype & visitor)
    {
        iterator <vtype, typename scanners :: buffer <ttype> :: type> :: read(target, visitor);
    }

    template <typename ttype> template <typename vtype> inline void buffer <ttype> :: write(ttype & target, vtype & visitor)
    {
        iterator <vtype, typename scanners :: buffer <ttype> :: type> :: write(target, visitor);
    }
};
#endif
