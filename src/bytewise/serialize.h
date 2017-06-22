// Forward declarations

namespace bytewise
{
    template <typename> class serialize;
};

#if !defined(__forward__) && !defined(__drop__bytewise__serialize__h)
#define __drop__bytewise__serialize__h

// Libraries

#include <stddef.h>
#include <stdint.h>

// Includes

#include "block.h"
#include "buffer.h"
#include "scanners/arithmetic.h"
#include "scanners/buffer.h"
#include "visitors/arithmetic.h"
#include "visitors/buffer.h"

namespace bytewise
{
    template <typename type> class serialize
    {
        // Friends

        template <typename> friend class visitors :: arithmetic;
        template <typename> friend class visitors :: buffer;

        // Properties

        static constexpr bool fix_alloc = scanners :: buffer <type> :: empty;
        static constexpr size_t size = fix_alloc ? (scanners :: arithmetic <type> :: type :: size) : 0;

        // Members

        typename std :: conditional <fix_alloc, block <size>, buffer> :: type _bytes;
        size_t _cursor;

    public:

        // Constructors

        serialize(const type &);

    private:

        // Private methods

        template <size_t rsize> void read(const char (&)[rsize]);
        void read(const buffer &);

    public:

        // Casting

        operator const typename std :: conditional <fix_alloc, block <size>, buffer> :: type & ();
    };
};

#endif
