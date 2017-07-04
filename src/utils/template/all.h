// Forward declarations

namespace utils
{
    template <template <typename, typename...> typename, typename...> class all;
};

#if !defined(__forward__) && !defined(__drop__utils__template__all__h)
#define __drop__utils__template__all__h

namespace utils
{
    template <template <typename, typename...> typename property> class all <property>
    {
    public:

        // Static members

        static constexpr bool value = true;
    };

    template <template <typename, typename...> typename property, typename first, typename... tail> class all <property, first, tail...>
    {
    public:

        // Static members

        static constexpr bool value = property <first> :: value && all <property, tail...> :: value;
    };
};

#endif
