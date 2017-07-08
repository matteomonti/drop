#if !defined(__forward__) && !defined(__drop__progressive__macros__h)
#define __drop__progressive__macros__h

// Libraries

#include <stddef.h>

// Includes

#include "count.h"
#include "base.h"
#include "utils/preprocessor/counter.h"

// Macros

#define progressive_indirect(scope)                                 \
                                                                    \
template <template <size_t, bool> typename, size_t, size_t> friend  \
    class :: progressive :: exists;                                 \
template <size_t, bool> class scope;                                \
template <bool __dummy__> class scope <:: progressive :: count      \
    <scope, __counter__> :: value, __dummy__> : public              \
    :: progressive :: base

#define progressive(scope) progressive_indirect(scope)

#endif
