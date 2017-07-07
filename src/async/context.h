// Forward declarations

namespace async
{
    template <typename> class context;
};

#if !defined(__forward__) && !defined(__drop__async__context__h)
#define __drop__async__context__h

// Includes

#include "promise.h"
#include "utils/template/is_callable.h"
#include "data/optional.h"

namespace async
{
    template <typename lambda> class context
    {
        // Members

        lambda _kernel;

    public:

        // Constructors

        context(const lambda &);

        // Methods

        void run();
    };

    // Functions

    template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <lambda> &> :: value> * = nullptr> context <lambda> * contextualize(const lambda &);
};

#endif
