// Forward declarations

namespace network
{
    namespace packet
    {
        template <typename...> class fields;
    };
};

#if !defined(__forward__) && !defined(__drop__network__packet__macros__h)
#define __drop__network__packet__macros__h

// Libraries

#include <stddef.h>

// Forward includes

#define __forward__
#include "exists.h"
#include "proxy.h"
#undef __forward__

// Includes

#include "progressive/macros.h"

// Macros

#define $packet_indirect(name, ...)                                 \
                                                                    \
template <typename, size_t> friend class :: network :: packet ::    \
    exists;                                                         \
template <typename, size_t> friend class :: network :: packet ::    \
    proxy;                                                          \
                                                                    \
$progressive(__packet__)                                            \
{                                                                   \
    template <typename, size_t> friend class :: network :: packet   \
        :: exists;                                                  \
                                                                    \
    typedef :: network :: packet :: fields <__VA_ARGS__> fields;    \
};

#define $packet(name, ...) $packet_indirect(name, __VA_ARGS__)

#endif
