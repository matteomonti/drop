// Forward declarations

namespace utils
{
    template <bool> class move_constructible;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__move_constructible__h)
#define __drop__utils__misc__move_constructible__h

namespace utils
{
    template <> class move_constructible <false>
    {
    public:

        // Constructors

        move_constructible() = default;
        move_constructible(const move_constructible &) = default;
        move_constructible(move_constructible &&) = delete;
    };

    template <> class move_constructible <true>
    {
    public:

        // Constructors

        move_constructible() = default;
        move_constructible(const move_constructible &) = default;
        move_constructible(move_constructible &&) = default;
    };
};

#endif
