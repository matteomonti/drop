// Forward declarations

namespace bytewise
{
    class buffer;
};

#if !defined(__forward__) && !defined(__drop__bytewise__buffer__h)
#define __drop__bytewise__buffer__h

// Libraries

#include <stddef.h>
#include <string.h>

namespace bytewise
{
    class buffer
    {
        // Members

        char * _bytes;
        size_t _size;
        size_t _alloc;

    public:

        // Constructors

        buffer();
        buffer(const char *, const size_t &);
        buffer(const char *);
        buffer(const buffer &);
        buffer(buffer &&);

        // Destructor

        ~buffer();

        // Methods

        void alloc(const size_t &);

        // Operators

        char & operator [] (const size_t &);
        const char & operator [] (const size_t &) const;

        buffer & operator = (const buffer &);
        buffer & operator = (buffer &&);

        // Casting

        operator char * ();
        operator const char * () const;
    };
};

#endif
