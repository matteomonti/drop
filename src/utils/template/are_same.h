// Forward declarations

namespace utils
{
    template <typename, typename...> struct are_same;
};

#if !defined(__forward__) && !defined(__drop__utils__template__are_same__h)
#define __drop__utils__template__are_same__h

// Libraries

#include <type_traits>

namespace utils
{
    template <typename type> struct are_same <type>
    {
        static constexpr bool value = true;
    };

    template <typename type, typename first, typename... types> struct are_same <type, first, types...>
    {
        static constexpr bool value = std :: is_same <type, first> :: value && are_same <type, types...> :: value;
    };
};

#endif
