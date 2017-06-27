#ifndef __drop__bytewise__on__hpp
#define __drop__bytewise__on__hpp

// Includes

#include "on.h"

namespace bytewise
{

    // emitter <true, dummy>

    template <typename ttype, typename etype> template <bool dummy> inline void on <ttype, etype> :: emitter <true, dummy> :: emit(ttype & target)
    {
        target.on(etype {});
    }

    // emitter <false, dummy>

    template <typename ttype, typename etype> template <bool dummy> inline void on <ttype, etype> :: emitter <false, dummy> :: emit(ttype & target)
    {
    }

    // on

    // Static methods

    template <typename ttype, typename etype> inline void on <ttype, etype> :: emit(ttype & target)
    {
        emitter <enable :: value, false> :: emit(target);
    }
};

#endif
