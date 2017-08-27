// Forward declarations

namespace network
{
    namespace dns
    {
        class name;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__name__h)
#define __drop__network__dns__name__h

// Libraries

#include <string.h>
#include <stddef.h>

namespace network :: dns
{
    class name
    {
    public:

        // Settings

        struct settings
        {
            static constexpr size_t max_size = 256;
        };

    private:

        // Members

        char _name[settings :: max_size];
        size_t _length;

    public:

        // Constructors

        name(const char *, const size_t &);
        name(const char *);

        // Getters

        const size_t & length() const;

        // Casting

        operator const char * () const;
    };
};

#endif
