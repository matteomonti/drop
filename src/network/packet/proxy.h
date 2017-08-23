// Forward declarations

namespace network
{
    namespace packet
    {
        template <typename, size_t> class proxy;
    };
};

#if !defined(__forward__) && !defined(__drop__network__packet__proxy__h)
#define __drop__network__packet__proxy__h

namespace network :: packet
{
    template <typename ptype, size_t index> class proxy
    {
    public:

        // Typedefs

        typedef typename ptype :: template __packet__ <index, false> type;
    };

    // Aliases

    template <typename ptype, size_t index> using proxy_t = typename proxy <ptype, index> :: type;
};

#endif
