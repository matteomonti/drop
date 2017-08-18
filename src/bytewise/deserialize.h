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
#include "traits.h"
#include "scanners/arithmetic.h"
#include "scanners/buffer.h"
#include "visitors/arithmetic.h"
#include "visitors/buffer.h"
#include "visitors/on.h"
#include "tuple.h"

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

        // Typedefs

        typedef std :: conditional_t <(traits <ttype> :: size > 0), block <traits <ttype> :: size>, buffer> type;

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

    template <typename type, size_t size, std :: enable_if_t <traits <type> :: arithmetic && (size >= sizeof(type))> * = nullptr> type deserialize(const block <size> &);
    template <typename type, std :: enable_if_t <traits <type> :: arithmetic> * = nullptr> type deserialize(const buffer &);

    template <typename type, size_t size, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic) && (traits <type> :: size > 0) && (size >= traits <type> :: size)> * = nullptr> type deserialize(const block <size> &);
    template <typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic) && (traits <type> :: size > 0)> * = nullptr> type deserialize(const buffer &);

    template <typename type, std :: enable_if_t <traits <type> :: enabled && !(traits <type> :: arithmetic) && (traits <type> :: size == 0)> * = nullptr> type deserialize(const buffer &);

    template <typename ftype, typename stype, typename... ttypes, typename btype> tuple <ftype, stype, ttypes...> deserialize(const btype &); // TODO: Add check for types to accept only bytewise enabled types or buffers
};

#endif
