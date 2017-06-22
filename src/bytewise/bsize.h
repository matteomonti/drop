// Forward declarations

namespace bytewise
{
    class bsize;
};

#if !defined(__forward__) && !defined(__drop__bytewise__bsize__h)
#define __drop__bytewise__bsize__h

// Libraries

#include <stddef.h>
#include <unistd.h>

namespace bytewise
{
    class bsize
    {
        // Members

        ssize_t _value;

    public:

        // Constructors

        bsize(const size_t &);
        bsize(const char *, const size_t &);

        // Getters

        const ssize_t & value();
        size_t bytes();

        // Methods

        size_t write(char *);
    };
};

#endif
