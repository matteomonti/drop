// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace bytewise
{
    template <size_t> class block;
};

#if !defined(__forward__) && !defined(__drop__bytewise__block__h)
#define __drop__bytewise__block__h

// Libraries

#include <string.h>

namespace bytewise
{
    template <size_t alloc> class block
    {
        // Typedefs

        typedef char array[alloc];

        // Members

        char _bytes[alloc];

    public:

        // Constructors

        block();
        block(const char *);
        block(const block &);

        // Operators

        char & operator [] (const size_t &);
        const char & operator [] (const size_t &) const;

        // Casting

        operator array & ();
        operator const array & () const;

        operator char * ();
        operator const char * () const;

        // Static members

        static constexpr size_t size = alloc;
    };
};

#endif
