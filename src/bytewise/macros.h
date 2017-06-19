#if !defined(__forward__) && !defined(__drop__bytewise__macros__h)
#define __drop__bytewise__macros__h

// Forward includes

#define __forward__
#include "exists.h"
#include "proxy.h"
#undef __forward__

// Includes

#include "progressive/macros.h"

#define bytewise_indirect(name)                                     \
                                                                    \
template <typename, size_t> friend class :: bytewise :: exists;     \
template <typename, size_t> friend class :: bytewise :: proxy;      \
                                                                    \
progressive(bytewise)                                               \
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
