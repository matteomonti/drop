// Forward declarations

namespace bytewise
{
    namespace options
    {
        template <typename...> class pack;

        namespace endianess
        {
            class little;
            class big;
            class network;
            class local;
        };
    };
};

#if !defined(__forward__) && !defined(__drop__bytewise__options__h)
#define __drop__bytewise__options__h

// Libraries

#include <type_traits>

// Includes

#include "endianess.h"

namespace bytewise :: options
{
    template <typename... opts> class pack
    {
        // Service nested classes

        template <typename, typename...> struct has;

        template <typename needle> struct has <needle>
        {
            static constexpr bool value = false;
        };

        template <typename needle, typename first, typename... haystack> struct has <needle, first, haystack...>
        {
            static constexpr bool value = std :: is_same <needle, first> :: value || has <needle, haystack...> :: value;
        };

        template <bool, bool, bool, bool, bool> struct endianess_switch
        {
            static constexpr :: bytewise :: endianess :: type value = :: bytewise :: endianess :: network;
        };

        template <bool dummy> struct endianess_switch <true, false, false, false, dummy>
        {
            static constexpr :: bytewise :: endianess :: type value = :: bytewise :: endianess :: little;
        };

        template <bool dummy> struct endianess_switch <false, true, false, false, dummy>
        {
            static constexpr :: bytewise :: endianess :: type value = :: bytewise :: endianess :: big;
        };

        template <bool dummy> struct endianess_switch <false, false, true, false, dummy>
        {
            static constexpr :: bytewise :: endianess :: type value = :: bytewise :: endianess :: network;
        };

        template <bool dummy> struct endianess_switch <false, false, false, true, dummy>
        {
            static constexpr :: bytewise :: endianess :: type value = :: bytewise :: endianess :: local;
        };

    public:

        // Static members

        static constexpr :: bytewise :: endianess :: type endianess = endianess_switch <has <endianess :: little, opts...> :: value, has <endianess :: big, opts...> :: value, has <endianess :: network, opts...> :: value, has <endianess :: local, opts...> :: value, false> :: value;
    };
};

#endif
