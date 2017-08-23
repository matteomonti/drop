// Forward declarations

namespace utils
{
    template <typename, typename...> class is_callable;
};

#if !defined(__forward__) && !defined(__drop__utils__template__is_callable__h)
#define __drop__utils__template__is_callable__h

// Libraries

#include <type_traits>
#include <stdint.h>

namespace utils
{
    template <typename functor, typename... args> class is_callable
    {
        // Service nested classes

        template <typename stype> struct callable_sfinae
        {
            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(std :: result_of_t <ftype(args...)> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <stype> (0)), uint32_t> :: value;
        };

        template <bool, bool> struct return_conditional;

        template <bool dummy> struct return_conditional <true, dummy>
        {
            typedef std :: result_of_t <functor(args...)> type;
        };

        template <bool dummy> struct return_conditional <false, dummy>
        {
            typedef void type;
        };

    public:

        // Static members

        static constexpr bool value = callable_sfinae <functor> :: value;
        typedef typename return_conditional <value, false> :: type return_type;
    };

    template <typename functor, typename arg> class is_callable <functor, arg>
    {
        // Service nested classes

        typedef std :: remove_const_t <std :: remove_reference_t <arg>> clean;
        static constexpr bool const_arg = std :: is_const <std :: remove_reference_t <arg>> :: value;

        template <typename stype> struct copy_sfinae
        {
            template <typename ftype, void (ftype :: *)(clean)> struct mhelper {};
            template <typename ftype, void (ftype :: *)(clean) const> struct chelper {};

            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(mhelper <ftype, &ftype :: operator ()> *);
            template <typename ftype> static uint32_t sfinae(chelper <ftype, &ftype :: operator ()> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <stype> (0)), uint32_t> :: value;
        };

        template <typename stype> struct const_reference_sfinae
        {
            template <typename ftype, void (ftype :: *)(const clean &)> struct mhelper {};
            template <typename ftype, void (ftype :: *)(const clean &) const> struct chelper {};

            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(mhelper <ftype, &ftype :: operator ()> *);
            template <typename ftype> static uint32_t sfinae(chelper <ftype, &ftype :: operator ()> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <stype> (0)), uint32_t> :: value;
        };

        template <typename stype> struct reference_sfinae
        {
            template <typename ftype, void (ftype :: *)(clean &)> struct mhelper {};
            template <typename ftype, void (ftype :: *)(clean &) const> struct chelper {};

            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(mhelper <ftype, &ftype :: operator ()> *);
            template <typename ftype> static uint32_t sfinae(chelper <ftype, &ftype :: operator ()> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <stype> (0)), uint32_t> :: value;
        };

        template <typename stype> struct callable_sfinae
        {
            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(std :: result_of_t <ftype(arg)> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <stype> (0)), uint32_t> :: value;
        };

        template <typename, bool> struct conditional_const_check;

        template <typename stype> struct conditional_const_check <stype, false>
        {
            static constexpr bool value = false;
        };

        template <typename stype> struct conditional_const_check <stype, true>
        {
            static constexpr bool value = const_reference_sfinae <functor> :: value;
        };

    public:

        // Static methods

        static constexpr bool direct = callable_sfinae <functor> :: value && (copy_sfinae <functor> :: value || (reference_sfinae <functor> :: value && !const_arg) || conditional_const_check <functor, !(reference_sfinae <functor> :: value && !const_arg)> :: value);
        static constexpr bool value = callable_sfinae <functor> :: value;
    };
};

#endif
