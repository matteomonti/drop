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
    template <typename functor, typename arg> class is_callable <functor, arg>
    {
    public: // REMOVE ME

        // Service nested classes

        typedef std :: remove_const_t <std :: remove_reference_t <arg>> clean;
        static constexpr bool const_arg = std :: is_const <std :: remove_reference_t <arg>> :: value;

        template <typename atype = clean> struct copy_sfinae
        {
            template <typename ftype, void (ftype :: *)(atype)> struct mhelper {};
            template <typename ftype, void (ftype :: *)(atype) const> struct chelper {};

            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(mhelper <ftype, &ftype :: operator ()> *);
            template <typename ftype> static uint32_t sfinae(chelper <ftype, &ftype :: operator ()> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <functor> (0)), uint32_t> :: value;
        };

        template <typename atype = clean> struct const_reference_sfinae
        {
            template <typename ftype, void (ftype :: *)(const atype &)> struct mhelper {};
            template <typename ftype, void (ftype :: *)(const atype &) const> struct chelper {};

            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(mhelper <ftype, &ftype :: operator ()> *);
            template <typename ftype> static uint32_t sfinae(chelper <ftype, &ftype :: operator ()> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <functor> (0)), uint32_t> :: value;
        };

        template <typename atype = clean> struct reference_sfinae
        {
            template <typename ftype, void (ftype :: *)(atype &)> struct mhelper {};
            template <typename ftype, void (ftype :: *)(atype &) const> struct chelper {};

            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(mhelper <ftype, &ftype :: operator ()> *);
            template <typename ftype> static uint32_t sfinae(chelper <ftype, &ftype :: operator ()> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <functor> (0)), uint32_t> :: value;
        };

        struct callable_sfinae
        {
            template <typename ftype> static uint8_t sfinae(...);
            template <typename ftype> static uint32_t sfinae(std :: result_of_t <ftype(arg)> *);

            static constexpr bool value = std :: is_same <decltype(sfinae <functor> (0)), uint32_t> :: value;
        };

        struct hidden {};

        static constexpr bool universal = callable_sfinae :: value && (copy_sfinae <hidden> :: value || const_reference_sfinae <hidden> :: value || (reference_sfinae <hidden> :: value && !const_arg));
        static constexpr bool direct = callable_sfinae :: value && (copy_sfinae <> :: value || const_reference_sfinae <> :: value || (reference_sfinae <> :: value && !const_arg));
        static constexpr bool value = callable_sfinae :: value;
    };
};

#endif
