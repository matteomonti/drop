// Forward declarations

namespace network
{
    namespace dns
    {
        class bitmask;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__bitmask__h)
#define __drop__network__dns__bitmask__h

// Libraries

#include <string.h>
#include <stddef.h>
#include <stdint.h>

namespace network :: dns
{
    class bitmask
    {
        // Settings

        struct settings
        {
            static constexpr size_t max_size = 128;
        };

        // Members

        uint8_t _mask[settings :: max_size];
        size_t _size;

    public:

        // Constructors

        bitmask(const char *, const size_t &);

        // Getters

        const size_t & size() const;

        // Operators

        bool operator [] (const size_t &) const;

        // Casting

        operator const char * () const;
    };
};

#endif
