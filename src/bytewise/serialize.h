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
#include "traits.h"
#include "scanners/arithmetic.h"
#include "scanners/buffer.h"
#include "visitors/arithmetic.h"
#include "visitors/buffer.h"
#include "visitors/on.h"
#include "utils/template/enable_in.h"

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

        typedef std :: conditional_t <(size > 0), block <size>, buffer> type;

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

        template <typename otype, utils :: enable_in_t <otype, ttype> * = nullptr> serializer(otype &&);

        // Getters

        auto finalize() const;

    private:

        // Private methods

        template <size_t rsize> void read(const char (&)[rsize]);
        void read(const buffer &);
    };

    // Functions

    template <typename type, std :: enable_if_t <traits <type> :: arithmetic> * = nullptr> auto serialize(type &&);
    template <typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic)> * = nullptr> auto serialize(type &&);
};

#endif
