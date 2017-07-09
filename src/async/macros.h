#if !defined(__forward__) && !defined(__drop__async__macros__h)
#define __drop__async__macros__h

// Includes

#include "contextualizer.hpp"
#include "leaver.hpp"
#include "utils/preprocessor/counter.h"

// Macros

#define async(body)                                                 \
                                                                    \
return :: async :: contextualize([=](auto & context) mutable        \
{                                                                   \
    bool __return__ = false;                                        \
                                                                    \
    switch(context.entrypoint())                                    \
    {                                                               \
        default:                                                    \
            assert(false);                                          \
        case -1:;                                                   \
        {                                                           \
            body                                                    \
        }                                                           \
    };                                                              \
});

#define await_indirect(target, entrypoint)                          \
                                                                    \
__return__ = true;                                                  \
case entrypoint:;                                                   \
if(__return__)                                                      \
    return leave(context, entrypoint, target)

#define await(target) await_indirect(target, __counter__)

#endif
