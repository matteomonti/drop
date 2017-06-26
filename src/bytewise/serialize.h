// Forward declarations

namespace bytewise
{
    template <typename> class serializer;
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

    public:

        // Properties

        static constexpr size_t size = scanners :: buffer <ttype> :: empty ? (scanners :: arithmetic <ttype> :: type :: size) : 0;

        // Typedefs

        typedef typename std :: conditional <(size > 0), block <size>, buffer> :: type type;

        // Service nested classes

        template <bool, bool> struct allocator;

        template <bool dummy> struct allocator <true, dummy>
        {
            static inline void alloc(type &, const ttype &);
            static inline void crop(type &, const size_t &);
        };

        template <bool dummy> struct allocator <false, dummy>
        {
            static inline void alloc(type &, const ttype &);
            static inline void crop(type &, const size_t &);
        };

    private:

        // Members

        type _bytes;
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

    template <typename type, typename std :: enable_if <std :: is_constructible <type> :: value> :: type * = nullptr> auto serialize(const type &);
};

#endif
