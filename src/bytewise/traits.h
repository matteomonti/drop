// Forward declarations

namespace bytewise
{
    template <typename> class traits;
};

#if !defined(__forward__) && !defined(__drop__bytewise__traits__h)
#define __drop__bytewise__traits__h

// Libraries

#include <type_traits>

// Includes

#include "count.h"

namespace bytewise
{
    template <typename type> class traits
    {
        // Typedefs

        typedef std :: remove_const_t <std :: remove_reference_t <type>> clean;

    public:

        // Static members

        static constexpr bool enabled = std :: is_constructible <clean> :: value && (std :: is_arithmetic <clean> :: value || count <clean> :: value > 0);
        static constexpr bool arithmetic = std :: is_arithmetic <clean> :: value;
    };
};

#endif
