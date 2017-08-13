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
#include <utility>

namespace bytewise
{
    class buffer
    {
    public:

        // Nested classes

        class reference
        {
        };

    private:

        // Members

        char * _bytes;
        size_t _size;
        size_t _alloc;

    public:

        // Constructors

        buffer();
        buffer(const char *, const size_t &);
        buffer(const char *);

        buffer(char *, const size_t &, class reference);

        buffer(const buffer &);
        buffer(buffer &&);

        // Destructor

        ~buffer();

        // Getters

        const size_t & size() const;

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

        // Static members

        static reference reference;
    };
};

#endif
