#if !defined(__forward__) && !defined(__drop__progressive__macros__h)
#define __drop__progressive__macros__h

// Libraries

#include <stddef.h>

// Includes

#include "count.h"
#include "base.h"

// Macros

#ifdef __COUNTER__
#define __counter__ __COUNTER__
#endif

#define progressive_indirect(scope)                                 \
                                                                    \
template <size_t, bool> struct scope;                               \
template <bool __dummy__> struct scope <:: progressive :: count     \
    <scope, __counter__> :: value, __dummy__> : public              \
    :: progressive :: base

#define progressive(scope) progressive_indirect(scope)

#endif
