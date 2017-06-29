// Forward declarations

namespace utils
{
    template <bool> class movable;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__movable__h)
#define __drop__utils__misc__movable__h

namespace utils
{
    template <> class movable <false>
    {
    public:

        // Constructors

        movable() = default;
        movable(const movable &) = default;
        movable(movable &&) = delete;
    };

    template <> class movable <true>
    {
    public:

        // Constructors

        movable() = default;
        movable(const movable &) = default;
        movable(movable &&) = default;
    };
};

#endif
