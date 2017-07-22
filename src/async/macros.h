#if !defined(__forward__) && !defined(__drop__async__macros__h)
#define __drop__async__macros__h

// Includes

#include "contextualizer.hpp"
#include "leaver.hpp"
#include "utils/preprocessor/counter.h"

// Macros

#define $async(body)                                                \
                                                                    \
return :: async :: contextualize([=](auto & context) mutable        \
{                                                                   \
    context.flag = false;                                           \
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

#define $await_indirect(target, entrypoint)                         \
                                                                    \
context.flag = true;                                                \
case entrypoint:;                                                   \
if(context.flag)                                                    \
    return leave(context, entrypoint, target)

#define $await(target) $await_indirect(target, __counter__)

#define $try_indirect(body, handlers, entrypoint)                   \
                                                                    \
context.handler(entrypoint);                                        \
{                                                                   \
    body                                                            \
}                                                                   \
context.handler();                                                  \
if(false)                                                           \
{                                                                   \
    case entrypoint:;                                               \
    try                                                             \
    {                                                               \
        context.rethrow();                                          \
    }                                                               \
    handlers                                                        \
}

#define $try(body, handlers) $try_indirect(body, handlers, __counter__)

#define $return(...) return context.resolve(__VA_ARGS__)

#endif
