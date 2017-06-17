// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace bytewise
{
    template <typename, size_t> class exists;
};

#if !defined(__forward__) && !defined(__drop__bytewise__exists__h)
#define __drop__bytewise__exists__h

// Libraries

#include <stdint.h>
#include <type_traits>

namespace bytewise
{
    template <typename type, size_t index> class exists
    {
        // SFINAE

        template <bool exists> struct helper {};
        template <typename etype> static uint8_t sfinae(...);
        template <typename etype> static uint32_t sfinae(helper <etype :: template bytewise <index, false> :: exists> *);

    public:

        // Static members

        static constexpr bool value = std :: is_same <decltype(sfinae <type> (0)), uint32_t> :: value;
    };
};

#endif
