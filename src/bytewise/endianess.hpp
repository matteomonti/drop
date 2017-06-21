#ifndef __drop__bytewise__endianess__hpp
#define __drop__bytewise__endianess__hpp

// Includes

#include "endianess.h"

namespace bytewise
{
    // Static methods

    inline void endianess :: swap(char (&destination)[2], const char (&source)[2])
    {
        reinterpret_cast <int16_t &> (destination) = __builtin_bswap16(reinterpret_cast <const int16_t &> (source));
    }

    inline void endianess :: swap(char (&destination)[4], const char (&source)[4])
    {
        reinterpret_cast <int32_t &> (destination) = __builtin_bswap32(reinterpret_cast <const int32_t &> (source));
    }

    inline void endianess :: swap(char (&destination)[8], const char (&source)[8])
    {
        reinterpret_cast <int64_t &> (destination) = __builtin_bswap64(reinterpret_cast <const int64_t &> (source));
    }

    inline void endianess :: swap(char (&destination)[16], const char (&source)[16])
    {
        struct mask
        {
            int64_t high;
            int64_t low;
        };

        (reinterpret_cast <mask &> (destination)).high = __builtin_bswap64((reinterpret_cast <const mask &> (source)).low);
        (reinterpret_cast <mask &> (destination)).low = __builtin_bswap64((reinterpret_cast <const mask &> (source)).high);
    }

    template <size_t size, typename std :: enable_if <size == 2 || size == 4 || size == 8 || size == 16> :: type *> inline void endianess :: translate(char (&destination)[size], const char (&source)[size])
    {
        struct yswap
        {
            static inline void run(char (&destination)[size], const char (&source)[size])
            {
                endianess :: swap(destination, source);
            }
        };

        struct nswap
        {
            static inline void run(char (&destination)[size], const char (&source)[size])
            {
                reinterpret_cast <typename int_t <size> :: type &> (destination) = reinterpret_cast <const typename int_t <size> :: type &> (source);
            }
        };

        std :: conditional <endianess :: foreign, yswap, nswap> :: type :: run(destination, source);
    }
};

#endif
