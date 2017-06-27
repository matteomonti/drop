#ifndef __drop__bytewise__on__hpp
#define __drop__bytewise__on__hpp

// Includes

#include "on.h"

namespace bytewise
{

    // emitter <true, dummy>

    template <typename ttype, typename etype> template <bool dummy> template <typename otype, utils :: enable_in_t <otype, ttype> *> inline void on <ttype, etype> :: emitter <true, dummy> :: emit(otype && target)
    {
        target.on(etype {});
    }

    // emitter <false, dummy>

    template <typename ttype, typename etype> template <bool dummy> template <typename otype, utils :: enable_in_t <otype, ttype> *> inline void on <ttype, etype> :: emitter <false, dummy> :: emit(otype && target)
    {
    }

    // on

    // Static methods

    template <typename ttype, typename etype> inline void on <ttype, etype> :: emit(ttype & target)
    {
        emitter <enable :: mutable_value || enable :: const_value, false> :: emit(target);
    }

    template <typename ttype, typename etype> inline void on <ttype, etype> :: emit(const ttype & target)
    {
        emitter <enable :: const_value, false> :: emit(target);
    }
};

#endif
