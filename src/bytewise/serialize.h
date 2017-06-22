// Forward declarations

namespace bytewise
{
    template <typename> class serializer;
    template <typename type> auto serialize(const type &);
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
    template <typename ttype> class serializer
    {
        // Friends

        template <typename> friend class visitors :: arithmetic;
        template <typename> friend class visitors :: buffer;

        // Properties

        static constexpr size_t size = scanners :: buffer <ttype> :: empty ? (scanners :: arithmetic <ttype> :: type :: size) : 0;

        // Members

        typename std :: conditional <(size > 0), block <size>, buffer> :: type _bytes;
        size_t _cursor;

    public:

        // Constructors

        serializer(const ttype &);

        // Getters

        auto finalize() const;

    private:

        // Private methods

        template <size_t rsize> void read(const char (&)[rsize]);
        void read(const buffer &);
    };

    // Functions

    template <typename type> auto serialize(const type &);
};

#endif
