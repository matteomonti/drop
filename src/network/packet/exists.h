// Forward declarations

namespace network
{
    namespace packet
    {
        template <typename, size_t> class exists;
    };
};

#if !defined(__forward__) && !defined(__drop__network__packet__exists__h)
#define __drop__network__packet__exists__h

// Libraries

#include <stdint.h>
#include <type_traits>

namespace network :: packet
{
    template <typename type, size_t index> class exists
    {
        // SFINAE

        template <bool exists> struct helper {};
        template <typename etype> static uint8_t sfinae(...);
        template <typename etype> static uint32_t sfinae(helper <etype :: template __packet__ <index, false> :: exists> *);

    public:

        // Static members

        static constexpr bool value = std :: is_same <decltype(sfinae <type> (0)), uint32_t> :: value;
    };
};

#endif
