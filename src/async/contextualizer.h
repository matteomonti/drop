// Forward declarations

namespace async
{
    template <typename> class contextualizer;
};

#if !defined(__forward__) && !defined(__drop__async__contextualizer__h)
#define __drop__async__contextualizer__h

// Includes

#include "context.h"
#include "promise.h"

namespace async
{
    template <typename lambda> class contextualizer
    {
        // Members

        const lambda & _kernel;

    public:

        // Constructors

        contextualizer(const lambda &);

        // Casting

        template <typename type> operator promise <type> () const;
    };

    // Functions

    template <typename lambda> auto contextualize(const lambda &);
};

#endif
