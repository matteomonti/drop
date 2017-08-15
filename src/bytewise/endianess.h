// Forward declarations

namespace bytewise
{
    class endianess;
};

#if !defined(__forward__) && !defined(__drop__bytewise__endianess__h)
#define __drop__bytewise__endianess__h

// Libraries

#include <stdint.h>
#include <type_traits>

namespace bytewise
{
    class endianess
    {
    public:

        // Nested enums

        enum type {little, big};

        // Macros

        #ifdef __BYTE_ORDER
            #if __BYTE_ORDER == __BIG_ENDIAN
                #define __drop__bytewise__endianess__endianess big
            #endif

            #if __BYTE_ORDER == __LITTLE_ENDIAN
                #define __drop__bytewise__endianess__endianess little
            #endif
        #endif

        #ifdef __BIG_ENDIAN__
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef __LITTLE_ENDIAN__
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef __ARMEB__
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef __ARMEL__
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef __THUMBEB__
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef __THUMBEL__
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef __AARCH64EB__
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef __AARCH64EL__
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef _MIPSEB
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef _MIPSEL
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef __MIPSEB
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef __MIPSEL
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef __MIPSEB__
            #define __drop__bytewise__endianess__endianess big
        #endif

        #ifdef __MIPSEL__
            #define __drop__bytewise__endianess__endianess little
        #endif

        #ifdef __BYTE_ORDER__
            #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
                #define __drop__bytewise__endianess__endianess big
            #endif

            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
                #define __drop__bytewise__endianess__endianess little
            #endif
        #endif

        #ifdef __FLOAT_WORD_ORDER__
            #if __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
                #define __drop__bytewise__endianess__endianess big
            #endif

            #if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
                #define __drop__bytewise__endianess__endianess little
            #endif
        #endif

    private:

        // Service nested classes

        template <size_t, bool = false> struct int_t;

        template <bool dummy> struct int_t <1, dummy>
        {
            typedef int8_t type;
        };

        template <bool dummy> struct int_t <2, dummy>
        {
            typedef int16_t type;
        };

        template <bool dummy> struct int_t <4, dummy>
        {
            typedef int32_t type;
        };

        template <bool dummy> struct int_t <8, dummy>
        {
            typedef int64_t type;
        };

        template <bool dummy> struct int_t <16, dummy>
        {
            struct type
            {
                int64_t high;
                int64_t low;
            };
        };

    public:

        // Static members

        static constexpr type local = __drop__bytewise__endianess__endianess;
        static constexpr type network = little;

        static constexpr bool foreign = (local != network);

        // Static methods

        static inline void swap(char (&)[1], const char (&)[1]);
        static inline void swap(char (&)[2], const char (&)[2]);
        static inline void swap(char (&)[4], const char (&)[4]);
        static inline void swap(char (&)[8], const char (&)[8]);
        static inline void swap(char (&)[16], const char (&)[16]);

        template <type target, size_t size, std :: enable_if_t <size == 1 || size == 2 || size == 4 || size == 8 || size == 16> * = nullptr> static inline void to(char (&)[size], const char (&)[size]);
        template <size_t size, std :: enable_if_t <size == 1 || size == 2 || size == 4 || size == 8 || size == 16> * = nullptr> static inline void translate(char (&)[size], const char (&)[size]);
    };
};

#endif
