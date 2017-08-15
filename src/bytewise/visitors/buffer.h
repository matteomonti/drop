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

// Forward includes

#define __forward__
#include "bytewise/serialize.h"
#include "bytewise/deserialize.h"
#undef __forward__

// Includes

#include "bytewise/map.h"
#include "bytewise/scanners/buffer.h"

namespace bytewise :: visitors
{
    template <typename ttype> class buffer
    {
        // Friends

        template <typename, size_t, size_t> friend class :: bytewise :: serializer;
        template <typename> friend class :: bytewise :: deserializer;

        // Service nested classes

        template <typename, typename> struct resolver;

        template <typename vtype> struct resolver <vtype, path <>>
        {
            template <typename mtype> static inline void read(const mtype &, vtype &);
            template <typename mtype> static inline void write(mtype &, vtype &);
            template <typename mtype> static inline size_t size(const mtype &);
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
                    template <typename mtype> static inline size_t size(const mtype &);
                };

                template <ssize_t index, bool dummy> struct iterator
                {
                    template <typename mtype> static inline void read(const mtype &, vtype &);
                    template <typename mtype> static inline void write(mtype &, vtype &);
                    template <typename mtype> static inline size_t size(const mtype &);
                };

                struct direct
                {
                    template <typename mtype> static inline void read(const mtype &, vtype &);
                    template <typename mtype> static inline void write(mtype &, vtype &);
                    template <typename mtype> static inline size_t size(const mtype &);
                };

                template <typename mtype> static inline void read(const mtype &, vtype &);
                template <typename mtype> static inline void write(mtype &, vtype &);
                template <typename mtype> static inline size_t size(const mtype &);
            };

            template <typename mtype> static inline void read(const mtype &, vtype &);
            template <typename mtype> static inline void write(mtype &, vtype &);
            template <typename mtype> static inline size_t size(const mtype &);
        };

        template <typename, typename> struct iterator;

        template <typename vtype> struct iterator <vtype, map <>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
            static inline size_t size(const ttype &);
        };

        template <typename vtype, typename next, typename... tail> struct iterator <vtype, map <next, tail...>>
        {
            static inline void read(const ttype &, vtype &);
            static inline void write(ttype &, vtype &);
            static inline size_t size(const ttype &);
        };

        // Static methods

        template <typename vtype> static inline void read(const ttype &, vtype &);
        template <typename vtype> static inline void write(ttype &, vtype &);

        static inline size_t size(const ttype &);
    };
};

#endif
