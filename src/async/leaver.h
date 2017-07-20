// Forward declarations

namespace async
{
    template <typename, typename, typename> class leaver;
};

#if !defined(__forward__) && !defined(__drop__async__leaver__h)
#define __drop__async__leaver__h

// Includes

#include "context.h"

namespace async
{
    template <typename type, typename lambda, typename ttype> class leaver
    {
        // Members

        context <type, lambda> & _context;
        ssize_t _entrypoint;
        ttype & _target;

    public:

        // Constructors

        leaver(context <type, lambda> &, const ssize_t &, ttype &);

        // Operators

        auto operator = (const promise <ttype> &) const;
    };

    // Functions

    template <typename type, typename lambda> auto leave(context <type, lambda> &, const ssize_t &, const promise <void> &);
    template <typename type, typename lambda, typename ttype> leaver <type, lambda, ttype> leave(context <type, lambda> &, const ssize_t &, ttype &);
};

#endif
