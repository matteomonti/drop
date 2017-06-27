// Forward declarations

namespace bytewise
{
    template <typename, typename> class on;

    struct read;
    struct write;
};

#if !defined(__forward__) && !defined(__drop__bytewise__on__h)
#define __drop__bytewise__on__h

// Libraries

#include <stdint.h>
#include <type_traits>

// Includes

#include "count.h"

namespace bytewise
{
    template <typename ttype, typename etype> class on
    {
    public: // REMOVE ME

        // Service nested classes

        struct enable
        {
            template <typename htype, void (htype :: *) (etype)> struct helper {};
            template <typename htype> static uint8_t sfinae(...);
            template <typename htype> static uint32_t sfinae(helper <htype, &htype :: on> *);

            static constexpr bool has_on = std :: is_same <decltype(sfinae <ttype> (0)), uint32_t> :: value;
            static constexpr bool value = has_on && (count <ttype> :: value > 0);
        };
    };

    struct read
    {
    };

    struct write
    {
    };
};

#endif
