// Forward declarations

namespace network
{
    namespace dns
    {
        class string;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__string__h)
#define __drop__network__dns__string__h

// Libraries

#include <string.h>
#include <stddef.h>

namespace network :: dns
{
    class string
    {
    public:

        // Settings

        struct settings
        {
            static constexpr size_t max_length = 256;
        };

    private:

        // Members

        char _value[settings :: max_length];
        size_t _length;

    public:

        // Constructors

        string();
        string(const char *, const size_t &);
        string(const char *);

        // Getters

        const size_t & length() const;

        // Casting

        operator const char * () const;
    };
};

#endif
