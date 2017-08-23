// Forward declarations

namespace utils
{
    template <typename...> class distinct;
};

#if !defined(__forward__) && !defined(__drop__utils__template__distinct__h)
#define __drop__utils__template__distinct__h

// Includes

#include "enable_in.h"

namespace utils
{
    template <> class distinct <>
    {
    public:

        // Static members

        static constexpr bool value = true;
    };

    template <typename needle, typename... haystack> class distinct <needle, haystack...>
    {
    public:

        // Static members

        static constexpr bool value = !(in <needle, haystack...> :: value) && distinct <haystack...> :: value;
    };
};

#endif
