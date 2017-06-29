// Forward declarations

namespace utils
{
    template <bool> class copiable;
};

#if !defined(__forward__) && !defined(__drop__utils__misc__copiable__h)
#define __drop__utils__misc__copiable__h

namespace utils
{
    template <> class copiable <false>
    {
    public:

        // Constructors

        copiable() = default;
        copiable(const copiable &) = delete;
        copiable(copiable &&) = default;
    };

    template <> class copiable <true>
    {
    public:

        // Constructors

        copiable() = default;
        copiable(const copiable &) = default;
        copiable(copiable &&) = default;
    };
};

#endif
