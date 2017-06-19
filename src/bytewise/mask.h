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
    };
};

#endif
