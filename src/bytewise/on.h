// Forward declarations

namespace bytewise
{
    template <typename, typename> class on;

    struct read;
    struct write;
};

#if !defined(__forward__) && !defined(__drop__bytewise__on__h)
#define __drop__bytewise__on__h

// Libraries

#include <stdint.h>
#include <type_traits>

// Includes

#include "count.h"
#include "utils/template/enable_in.h"

namespace bytewise
{
    template <typename ttype, typename etype> class on
    {
        // Service nested classes

        struct enable
        {
            template <typename htype, void (htype :: *) (etype)> struct mhelper {};
            template <typename htype> static uint8_t msfinae(...);
            template <typename htype> static uint32_t msfinae(mhelper <htype, &htype :: on> *);

            template <typename htype, void (htype :: *) (etype) const> struct chelper {};
            template <typename htype> static uint8_t csfinae(...);
            template <typename htype> static uint32_t csfinae(chelper <htype, &htype :: on> *);

            static constexpr bool mutable_on = std :: is_same <decltype(msfinae <ttype> (0)), uint32_t> :: value;
            static constexpr bool const_on = std :: is_same <decltype(csfinae <ttype> (0)), uint32_t> :: value;

            static constexpr bool mutable_value = mutable_on && (count <ttype> :: value > 0);
            static constexpr bool const_value = const_on && (count <ttype> :: value > 0);
        };

        template <bool, bool> struct emitter;

        template <bool dummy> struct emitter <true, dummy>
        {
            template <typename otype, utils :: enable_in_t <otype, ttype> * = nullptr> static inline void emit(otype &&);
        };

        template <bool dummy> struct emitter <false, dummy>
        {
            template <typename otype, utils :: enable_in_t <otype, ttype> * = nullptr> static inline void emit(otype &&);
        };

    public:

        // Static methods

        static inline void emit(ttype &);
        static inline void emit(const ttype &);
    };

    struct read
    {
    };

    struct write
    {
    };
};

#endif
