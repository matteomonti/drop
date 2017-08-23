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

        namespace pad
        {
            template <size_t> class beg;
            template <size_t> class end;
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

        // Searchers

        template <typename, typename...> struct has_atomic;

        template <typename needle> struct has_atomic <needle>
        {
            static constexpr bool value = false;
        };

        template <typename needle, typename first, typename... haystack> struct has_atomic <needle, first, haystack...>
        {
            static constexpr bool value = std :: is_same <needle, first> :: value || has_atomic <needle, haystack...> :: value;
        };

        template <template <size_t> typename, typename...> struct integral;

        template <template <size_t> typename needle> struct integral <needle>
        {
            static constexpr bool defined = false;
            static constexpr size_t value = 0;
        };

        template <template <size_t> typename needle, size_t optvalue, typename... haystack> struct integral <needle, needle <optvalue>, haystack...>
        {
            static constexpr bool defined = true;
            static constexpr size_t value = optvalue;
        };

        template <template <size_t> typename needle, typename first, typename... haystack> struct integral <needle, first, haystack...>
        {
            static constexpr bool defined = integral <needle, haystack...> :: defined;
            static constexpr size_t value = integral <needle, haystack...> :: value;
        };

        // Endianess

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

        static constexpr :: bytewise :: endianess :: type endianess = endianess_switch <has_atomic <endianess :: little, opts...> :: value, has_atomic <endianess :: big, opts...> :: value, has_atomic <endianess :: network, opts...> :: value, has_atomic <endianess :: local, opts...> :: value, false> :: value;

        struct pad
        {
            static constexpr size_t beg = (integral <:: bytewise :: options :: pad :: beg, opts...> :: defined ? integral <:: bytewise :: options :: pad :: beg, opts...> :: value : 0);
            static constexpr size_t end = (integral <:: bytewise :: options :: pad :: end, opts...> :: defined ? integral <:: bytewise :: options :: pad :: end, opts...> :: value : 0);
        };
    };
};

#endif
