// Forward declarations

namespace bytewise
{
    template <typename> class deserializer;
};

#if !defined(__forward__) && !defined(__drop__bytewise__deserialize__h)
#define __drop__bytewise__deserialize__h

// Libraries

#include <stddef.h>
#include <stdint.h>
#include <exception>

// Includes

#include "block.h"
#include "buffer.h"
#include "scanners/arithmetic.h"
#include "scanners/buffer.h"
#include "visitors/arithmetic.h"
#include "visitors/buffer.h"

namespace bytewise
{
    template <typename ttype> class deserializer
    {
        // Friends

        template <typename> friend class visitors :: arithmetic;
        template <typename> friend class visitors :: buffer;

    public:

        // Exceptions

        class overflow : public std :: exception
        {
            const char * what() const noexcept;
        };

        // Properties

        static constexpr size_t size = scanners :: buffer <ttype> :: empty ? (scanners :: arithmetic <ttype> :: type :: size) : 0;

        // Typedefs

        typedef typename std :: conditional <(size > 0), block <size>, buffer> :: type type;

    private:

        // Members

        ttype _target;
        const type & _bytes;
        size_t _cursor;

    public:

        // Constructors

        deserializer(const type &);

        // Getters

        ttype finalize() const;

    private:

        // Private methods

        template <size_t rsize> void write(char (&)[rsize]);
        void write(buffer &);
    };

    // Functions

    template <typename type, typename std :: enable_if <std :: is_constructible <type> :: value> :: type * = nullptr> type deserialize(const typename std :: conditional <(deserializer <type> :: size > 0), block <deserializer <type> :: size>, buffer> :: type &);
};

#endif
