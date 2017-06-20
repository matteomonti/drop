// Forward declarations

namespace bytewise
{
    namespace visitors
    {
        template <typename> class buffer;
    };
};

#if !defined(__forward__) && !defined(__drop__bytewise__visitors__buffer__h)
#define __drop__bytewise__visitors__buffer__h

// Includes

#include "bytewise/map.h"
#include "bytewise/scanners/buffer.h"

namespace bytewise :: visitors
{
    template <typename ttype> class buffer
    {
    public: // Remove me

        // Service nested classes

        template <typename, typename> struct resolver;

        template <typename vtype> struct resolver <vtype, path <>>
        {
            template <typename mtype> static inline void read(const mtype &, vtype &);
            template <typename mtype> static inline void write(mtype &, vtype &);
        };

        template <typename vtype, size_t next, size_t... tail> struct resolver <vtype, path <next, tail...>>
        {
            struct unroll
            {
                template <ssize_t, bool> struct iterator;

                template <bool dummy> struct iterator <-1, dummy>
                {
                    template <typename mtype> static inline void read(const mtype &, vtype &);
                    template <typename mtype> static inline void write(mtype &, vtype &);
                };

                template <ssize_t index, bool dummy> struct iterator
                {
                    template <typename mtype> static inline void read(const mtype &, vtype &);
                    template <typename mtype> static inline void write(mtype &, vtype &);
                };

                struct direct
                {
                    template <typename mtype> static inline void read(const mtype &, vtype &);
                    template <typename mtype> static inline void write(mtype &, vtype &);
                };
                
                template <typename mtype> static inline void read(const mtype &, vtype &);
                template <typename mtype> static inline void write(mtype &, vtype &);
            };

            template <typename mtype> static inline void read(const mtype &, vtype &);
            template <typename mtype> static inline void write(mtype &, vtype &);
        };

        template <typename, typename> struct iterator;

        template <typename vtype> struct iterator <vtype, map <>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
        };

        template <typename vtype, typename next, typename... tail> struct iterator <vtype, map <next, tail...>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
        };

        // Static methods

        template <typename vtype> static inline void read(const ttype &, vtype &);
        template <typename vtype> static inline void write(ttype &, vtype &);
    };
};

#endif
