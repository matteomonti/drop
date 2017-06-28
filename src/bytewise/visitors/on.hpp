#ifndef __drop__bytewise__visitors__on__hpp
#define __drop__bytewise__visitors__on__hpp

// Includes

#include "on.h"
#include "bytewise/on.hpp"
#include "bytewise/proxy.hpp"

namespace bytewise :: visitors
{
    // member_iterator <-1, dummy>

    template <bool dummy> template <typename mtype> inline void on :: member_iterator <-1, dummy> :: read(mtype &&)
    {
    }

    template <bool dummy> template <typename mtype> inline void on :: member_iterator <-1, dummy> :: write(mtype &&)
    {
    }

    // member_iterator <index, dummy>

    template <ssize_t index, bool dummy> template <typename mtype> inline void on :: member_iterator <index, dummy> :: read(mtype && member)
    {
        member_iterator <index - 1, dummy> :: read(member);
        :: bytewise :: visitors :: on :: read(proxy <clean <mtype>, index> :: get(member));
    }

    template <ssize_t index, bool dummy> template <typename mtype> inline void on :: member_iterator <index, dummy> :: write(mtype && member)
    {
        member_iterator <index - 1, dummy> :: write(member);
        :: bytewise :: visitors :: on :: write(proxy <clean <mtype>, index> :: get(member));
    }

    // array_iterator <index, dummy>

    template <bool dummy> template <typename mtype> inline void on :: array_iterator <-1, dummy> :: read(mtype &&)
    {
    }

    template <bool dummy> template <typename mtype> inline void on :: array_iterator <-1, dummy> :: write(mtype &&)
    {
    }

    // array_iterator <index, dummy>

    template <ssize_t index, bool dummy> template <typename mtype> inline void on :: array_iterator <index, dummy> :: read(mtype && member)
    {
        array_iterator <index - 1, dummy> :: read(member);
        :: bytewise :: visitors :: on :: read(member[index]);
    }

    template <ssize_t index, bool dummy> template <typename mtype> inline void on :: array_iterator <index, dummy> :: write(mtype && member)
    {
        array_iterator <index - 1, dummy> :: write(member);
        :: bytewise :: visitors :: on :: write(member[index]);
    }

    // null_iterator

    template <typename mtype> inline void on :: null_iterator :: read(mtype &&)
    {
    }

    template <typename mtype> inline void on :: null_iterator :: write(mtype &&)
    {
    }

    // on

    template <typename mtype> inline void on :: read(mtype && member)
    {
        :: bytewise :: on <clean <mtype>, :: bytewise :: read> :: emit(member);

        std :: conditional_t
        <
            std :: is_class <root <mtype>> :: value,
            std :: conditional_t
            <
                std :: is_array <clean <mtype>> :: value,
                array_iterator <(ssize_t) (std :: extent <clean <mtype>> :: value) - 1, false>,
                member_iterator <(ssize_t) (count <clean <mtype>> :: value) - 1, false>
            >,
            null_iterator
        > :: read(member);
    }

    template <typename mtype> inline void on :: write(mtype && member)
    {
        std :: conditional_t
        <
            std :: is_class <root <mtype>> :: value,
            std :: conditional_t
            <
                std :: is_array <clean <mtype>> :: value,
                array_iterator <(ssize_t) (std :: extent <clean <mtype>> :: value) - 1, false>,
                member_iterator <(ssize_t) (count <clean <mtype>> :: value) - 1, false>
            >,
            null_iterator
        > :: write(member);

        :: bytewise :: on <clean <mtype>, :: bytewise :: write> :: emit(member);
    }
};

#endif
