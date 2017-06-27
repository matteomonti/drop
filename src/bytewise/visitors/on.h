// Forward declarations

namespace bytewise
{
    namespace visitors
    {
        class on;
    };
};

#if !defined(__forward__) && !defined(__drop__bytewise__visitors__on__h)
#define __drop__bytewise__visitors__on__h

// Libraries

#include <stddef.h>
#include <type_traits>

// Includes

#include "bytewise/on.h"
#include "bytewise/count.h"

namespace bytewise :: visitors
{
    class on
    {
    public: // REMOVE ME

        template <typename mtype> using clean = std :: remove_const_t <std :: remove_reference_t <mtype>>;
        template <typename mtype> using root = std :: remove_all_extents_t <clean <mtype>>;

        template <ssize_t, bool> struct member_iterator;

        template <bool dummy> struct member_iterator <-1, dummy>
        {
            template <typename mtype> static inline void read(mtype &&);
            template <typename mtype> static inline void write(mtype &&);
        };

        template <ssize_t index, bool dummy> struct member_iterator
        {
            template <typename mtype> static inline void read(mtype &&);
            template <typename mtype> static inline void write(mtype &&);
        };

        template <ssize_t, bool> struct array_iterator;

        template <bool dummy> struct array_iterator <-1, dummy>
        {
            template <typename mtype> static inline void read(mtype &&);
            template <typename mtype> static inline void write(mtype &&);
        };

        template <ssize_t index, bool dummy> struct array_iterator
        {
            template <typename mtype> static inline void read(mtype &&);
            template <typename mtype> static inline void write(mtype &&);
        };

        struct null_iterator
        {
            template <typename mtype> static inline void read(mtype &&);
            template <typename mtype> static inline void write(mtype &&);
        };

        template <typename mtype> static inline void read(mtype &&);
        template <typename mtype> static inline void write(mtype &&);
    };
};

#endif
