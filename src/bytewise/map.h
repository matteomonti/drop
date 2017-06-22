// Forward declarations libraries

#include <stddef.h>

// Forward declarations

namespace bytewise
{
    template <size_t...> class path;
    template <typename...> class map;
};

#if !defined(__forward__) && !defined(__drop__bytewise__map__h)
#define __drop__bytewise__map__h

namespace bytewise
{
    template <size_t...> class path;

    template <typename... paths> class map
    {
    public:

        // Nested classes

        template <typename> struct append;

        template <typename... apaths> struct append <map <apaths...>>
        {
            typedef map <paths..., apaths...> type;
        };

        template <size_t value> class prefix
        {
            // Service nested classes

            template <bool, typename...> struct iterator;

            template <bool dummy> struct iterator <dummy>
            {
                typedef map <> type;
            };

            template <bool dummy, size_t... steps, typename... tail> struct iterator <dummy, path <steps...>, tail...>
            {
                typedef typename map <path <value, steps...>> :: template append <typename iterator <false, tail...> :: type> :: type type;
            };

        public:

            // Typedefs

            typedef typename iterator <false, paths...> :: type type;
        };

        // Static members

        static constexpr size_t size = sizeof...(paths);
    };
};

#endif
