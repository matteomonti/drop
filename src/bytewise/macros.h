#if !defined(__forward__) && !defined(__drop__bytewise__macros__h)
#define __drop__bytewise__macros__h

// Forward includes

#define __forward__
#include "exists.h"
#include "proxy.h"
#include "on.h"
#undef __forward__

// Includes

#include "progressive/macros.h"
#include "utils/template/enable_in.h"

#define bytewise_indirect(name)                                     \
                                                                    \
template <typename, size_t> friend class :: bytewise :: exists;     \
template <typename, size_t> friend class :: bytewise :: proxy;      \
template <typename, typename> friend class :: bytewise :: on;       \
                                                                    \
progressive(__bytewise__)                                           \
{                                                                   \
    template <typename, size_t> friend class :: bytewise :: proxy;  \
                                                                    \
    typedef decltype(self :: name) type;                            \
                                                                    \
    static constexpr const size_t offset()                          \
    {                                                               \
        return offsetof(self, name);                                \
    }                                                               \
                                                                    \
    template <typename __self__, utils :: enable_in_t <__self__,    \
        self> * = nullptr> static inline auto && get(__self__       \
            && parent)                                              \
    {                                                               \
        return parent.name;                                         \
    }                                                               \
};

#define bytewise(name) bytewise_indirect(name)

#endif
