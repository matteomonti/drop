// Forward declarations

namespace utils
{
    template <typename, typename...> class in;
    template <typename, typename...> class enable_in;
};

#if !defined(__forward__) && !defined(__drop__utils__template__enable_in__h)
#define __drop__utils__template__enable_in__h

// Libraries

#include <type_traits>

namespace utils
{
    template <typename needle> class in <needle>
    {
    public:

        // Static members

        static constexpr bool value = false;
    };

    template <typename needle, typename first, typename... haystack> class in <needle, first, haystack...>
    {
    public:

        // Static members

        static constexpr bool value = std :: is_same <needle, first> :: value || in <needle, haystack...> :: value;
    };

    template <typename needle, typename... haystack> class enable_in : public std :: enable_if <in <std :: remove_const_t <std :: remove_reference_t <needle>>, haystack...> :: value>
    {
    };

    template <typename needle, typename... haystack> using enable_in_t = typename enable_in <needle, haystack...> :: type;
};

#endif
