// Forward declarations

namespace bytewise
{
    namespace visitors
    {
        template <typename> class arithmetic;
    };
};

#if !defined(__forward__) && !defined(__drop__bytewise__visitors__arithmetic__h)
#define __drop__bytewise__visitors__arithmetic__h

// Includes

#include "bytewise/mask.h"
#include "bytewise/scanners/arithmetic.h"

namespace bytewise :: visitors
{
    template <typename ttype> class arithmetic
    {
        // Service nested classes

        template <size_t, size_t, bool> struct selector;

        #pragma pack(push, 1)

        template <bool dummy> struct selector <0, sizeof(ttype), dummy>
        {
            char value[sizeof(ttype)];
        };

        template <size_t end, bool dummy> struct selector <0, end, dummy>
        {
            char value[end];
            char tail[sizeof(ttype) - end];
        };

        template <size_t beg, bool dummy> struct selector <beg, sizeof(ttype), dummy>
        {
            char head[beg];
            char value[sizeof(ttype) - beg];
        };

        template <size_t beg, size_t end, bool dummy> struct selector
        {
            char head[beg];
            char value[end - beg];
            char tail[sizeof(ttype) - end];
        };

        #pragma pack(pop)

        template <typename, typename> struct iterator;

        template <typename vtype> struct iterator <vtype, mask <>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
        };

        template <typename vtype, size_t beg, size_t end, typename... tail> struct iterator <vtype, mask <range <beg, end, true>, tail...>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
        };

        template <typename vtype, size_t beg, size_t end, typename... tail> struct iterator <vtype, mask <range <beg, end, false>, tail...>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
        };

    public: // REMOVE ME

        // Static methods

        template <typename vtype> static inline void read(const ttype &, vtype &);
        template <typename vtype> static inline void write(ttype &, vtype &);
    };
};

#endif
