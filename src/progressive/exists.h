// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace progressive
{
    template <template <size_t, bool> typename, size_t, size_t> class exists;
};

#if !defined(__forward__) && !defined(__drop__progressive__exists__h)
#define __drop__progressive__exists__h

// Libraries

#include <stdint.h>
#include <type_traits>

namespace progressive
{
    template <template <size_t, bool> typename scope, size_t index, size_t shuffle> class exists
    {
        // SFINAE

        template <bool exists> struct helper {};
        template <template <size_t, bool> typename sscope> static uint8_t sfinae(...);
        template <template <size_t, bool> typename sscope> static uint32_t sfinae(helper <sscope <index, false> :: exists> *);

    public:

        // Static members

        static constexpr bool value = std :: is_same <decltype(sfinae <scope> (0)), uint32_t> :: value;
    };
};

#endif
