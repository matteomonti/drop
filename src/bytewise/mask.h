// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace bytewise
{
    template <size_t, size_t, bool> class range;
    template <typename...> class mask;
};

#if !defined(__forward__) && !defined(__drop__bytewise__mask__h)
#define __drop__bytewise__mask__h

namespace bytewise
{
    template <size_t, size_t, bool> class range;

    template <typename... ranges> class mask
    {
    public:

        // Nested classes

        template <typename> struct append;

        template <typename... aranges> struct append <mask <aranges...>>
        {
            typedef mask <ranges..., aranges...> type;
        };

        template <size_t value> class shift
        {
            // Service nested classes

            template <bool, typename...> struct iterator;

            template <bool dummy> struct iterator <dummy>
            {
                typedef mask <> type;
            };

            template <bool dummy, size_t beg, size_t end, bool swap, typename... tail> struct iterator <dummy, range <beg, end, swap>, tail...>
            {
                typedef typename mask <range <beg + value, end + value, swap>> :: template append <typename iterator <false, tail...> :: type> :: type type;
            };

        public:

            // Typedefs

            typedef typename iterator <false, ranges...> :: type type;
        };

        class compress
        {
        public: // REMOVE ME

            // Service nested classes

            template <typename, size_t> struct min;

            template <size_t inf> struct min <mask <>, inf>
            {
                static constexpr size_t beg = -1;
                static constexpr size_t end = -1;
                static constexpr bool swap = false;
            };

            template <size_t rbeg, size_t rend, bool rswap, typename... tail, size_t inf> struct min <mask <range <rbeg, rend, rswap>, tail...>, inf>
            {
                static constexpr bool better = (rbeg >= inf && rbeg < min <mask <tail...>, inf> :: beg);

                static constexpr size_t beg = better ? rbeg : min <mask <tail...>, inf> :: beg;
                static constexpr size_t end = better ? rend : min <mask <tail...>, inf> :: end;
                static constexpr bool swap = better ? rswap : min <mask <tail...>, inf> :: swap;
            };

            template <size_t, bool> struct sort;

            template <bool dummy> struct sort <0, dummy>
            {
                static constexpr size_t beg = min <mask <ranges...>, 0> :: beg;
                static constexpr size_t end = min <mask <ranges...>, 0> :: end;
                static constexpr bool swap = min <mask <ranges...>, 0> :: swap;

                typedef mask <range <beg, end, swap>> type;
            };

            template <size_t index, bool dummy> struct sort
            {
                static constexpr size_t inf = sort <index - 1, false> :: beg + 1;

                static constexpr size_t beg = min <mask <ranges...>, inf> :: beg;
                static constexpr size_t end = min <mask <ranges...>, inf> :: end;
                static constexpr bool swap = min <mask <ranges...>, inf> :: swap;

                typedef typename sort <index - 1, false> :: type :: template append <mask <range <beg, end, swap>>> :: type type;
            };

            template <typename> struct merge;

            template <size_t beg, size_t end, bool swap> struct merge <mask <range <beg, end, swap>>>
            {
                typedef mask <range <beg, end, swap>> type;
            };

            template <size_t abeg, size_t aend, bool aswap, size_t bbeg, size_t bend, size_t bswap, typename... tail> struct merge <mask <range <abeg, aend, aswap>, range <bbeg, bend, bswap>, tail...>>
            {
                typedef typename std :: conditional
                <
                    (!aswap && !bswap && aend == bbeg),
                    typename merge <mask <range <abeg, bend, false>, tail...>> :: type,
                    typename mask <range <abeg, aend, aswap>> :: template append <typename merge <mask <range <bbeg, bend, bswap>, tail...>> :: type> :: type
                > :: type type;
            };

        public:

            // Typedefs

            typedef typename std :: conditional
            <
                (sizeof...(ranges) > 0),
                typename merge <typename sort <sizeof...(ranges) - 1, false> :: type> :: type,
                mask <>
            > :: type type;
        };
    };
};

#endif
