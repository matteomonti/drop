// Forward declarations

namespace network
{
    namespace packet
    {
        template <typename> class count;
    };
};

#if !defined(__forward__) && !defined(__drop__network__packet__count__h)
#define __drop__network__packet__count__h

// Libraries

#include <stddef.h>
#include <stdint.h>
#include <type_traits>

// Includes

#include "exists.h"

namespace network
{
    namespace packet
    {
        template <typename ctype> class count
        {
            // Service nested classes

            template <size_t, bool> struct iterator;

            template <size_t index> struct iterator <index, false>
            {
                static constexpr size_t value = index;
            };

            template <size_t index> struct iterator <index, true>
            {
                static constexpr size_t value = iterator <index + 1, exists <ctype, index + 1> :: value> :: value;
            };

        public:

            // Static members

            static constexpr size_t value = iterator <0, exists <ctype, 0> :: value> :: value;
            static constexpr size_t size = (value <= 256 ? 1 : (value <= 65536 ? 2 : 4));

            // Typedefs

            typedef std :: conditional_t <size == 1, uint8_t, std :: conditional_t <size == 2, uint16_t, uint32_t>> type;
        };
    };
};

#endif
