// Forward declarations

namespace utils
{
    template <bool> class copy_assignable;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__copy_assignable__h)
#define __drop__utils__misc__copy_assignable__h

namespace utils
{
    template <> class copy_assignable <false>
    {
    public:

        // Constructors

        copy_assignable() = default;
        copy_assignable(const copy_assignable &) = default;
        copy_assignable(copy_assignable &&) = default;

        // Operators

        copy_assignable & operator = (const copy_assignable &) = delete;
        copy_assignable & operator = (copy_assignable &&) = default;
    };

    template <> class copy_assignable <true>
    {
    public:

        // Constructors

        copy_assignable() = default;
        copy_assignable(const copy_assignable &) = default;
        copy_assignable(copy_assignable &&) = default;

        // Operators

        copy_assignable & operator = (const copy_assignable &) = default;
        copy_assignable & operator = (copy_assignable &&) = default;
    };
};

#endif
