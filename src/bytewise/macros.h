#if !defined(__forward__) && !defined(__drop__bytewise__macros__h)
#define __drop__bytewise__macros__h

// Includes

#include "progressive/macros.h"

#define bytewise_indirect(name)                                     \
                                                                    \
progressive(bytewise)                                               \
{                                                                   \
    static inline auto & get(self & parent)                         \
    {                                                               \
        return parent.name;                                         \
    }                                                               \
                                                                    \
    static inline const auto & get(const self & parent)             \
    {                                                               \
        return parent.name;                                         \
    }                                                               \
};

#define bytewise(name) bytewise_indirect(name)

#endif
