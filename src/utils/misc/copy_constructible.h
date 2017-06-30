// Forward declarations

namespace utils
{
    template <bool> class copy_constructible;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__copy_constructible__h)
#define __drop__utils__misc__copy_constructible__h

namespace utils
{
    template <> class copy_constructible <false>
    {
    public:

        // Constructors

        copy_constructible() = default;
        copy_constructible(const copy_constructible &) = delete;
        copy_constructible(copy_constructible &&) = default;

        // Operators

        copy_constructible & operator = (const copy_constructible &) = default;
        copy_constructible & operator = (copy_constructible &&) = default;
    };

    template <> class copy_constructible <true>
    {
    public:

        // Constructors

        copy_constructible() = default;
        copy_constructible(const copy_constructible &) = default;
        copy_constructible(copy_constructible &&) = default;

        // Operators

        copy_constructible & operator = (const copy_constructible &) = default;
        copy_constructible & operator = (copy_constructible &&) = default;
    };
};

#endif
