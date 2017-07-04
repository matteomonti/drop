// Forward declarations

namespace utils
{
    template <typename type, type, type...> class static_max;
};

#if !defined(__forward__) && !defined(__drop__utils__template__static_max__h)
#define __drop__utils__template__static_max__h

namespace utils
{
    template <typename type, type arg, type... args> class static_max;

    template <typename type, type arg> class static_max <type, arg>
    {
    public:

        // Static members

        static constexpr type value = arg;
    };

    template <typename type, type arg, type next, type... tail> class static_max <type, arg, next, tail...>
    {
    public:

        // Static members

        static constexpr type value = (arg > static_max <type, next, tail...> :: value ? arg : static_max <type, next, tail...> :: value);
    };
};

#endif
