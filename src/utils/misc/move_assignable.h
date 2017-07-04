// Forward declarations

namespace utils
{
    template <bool> class move_assignable;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__move_assignable__h)
#define __drop__utils__misc__move_assignable__h

namespace utils
{
    template <> class move_assignable <false>
    {
    public:

        // Constructors

        move_assignable() = default;
        move_assignable(const move_assignable &) = default;
        move_assignable(move_assignable &&) = default;

        // Operators

        move_assignable & operator = (const move_assignable &) = default;
        move_assignable & operator = (move_assignable &&) = delete;
    };

    template <> class move_assignable <true>
    {
    public:

        // Constructors

        move_assignable() = default;
        move_assignable(const move_assignable &) = default;
        move_assignable(move_assignable &&) = default;

        // Operators

        move_assignable & operator = (const move_assignable &) = default;
        move_assignable & operator = (move_assignable &&) = default;
    };
};

#endif
