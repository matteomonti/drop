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

#include <type_traits>
#include <stddef.h>

// Forward includes

#define __forward__
#include "exists.h"
#include "proxy.h"
#undef __forward__

// Includes

#include "progressive/macros.h"
#include "packet.hpp"

// Macros

#define $packet_indirect(name, ...)                                 \
                                                                    \
template <typename, size_t> friend class :: network :: packet ::    \
    exists;                                                         \
template <typename, size_t> friend class :: network :: packet ::    \
    proxy;                                                          \
                                                                    \
$progressive(__packet__), public :: network :: packet :: packet     \
    <__VA_ARGS__>                                                   \
{                                                                   \
public:                                                             \
    template <typename... types, std :: enable_if_t <std ::         \
        is_constructible <:: network :: packet :: packet            \
        <__VA_ARGS__>, types...> :: value> * = nullptr> __packet__  \
        (types && ... args) : :: network :: packet :: packet        \
        <__VA_ARGS__> (args...)                                     \
        {                                                           \
        }                                                           \
};                                                                  \
                                                                    \
typedef $last(__packet__) name;

#define $packet(name, ...) $packet_indirect(name, __VA_ARGS__)

#endif
