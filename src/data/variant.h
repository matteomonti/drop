// Forward declarations

namespace data
{
    template <typename...> class variant;
};

#if !defined(__forward__) && !defined(__drop__data__variant__h)
#define __drop__data__variant__h

namespace data
{
    template <typename... types> class variant
    {
    };
};

#endif
