// Forward declarations

namespace async
{
    template <typename, typename> class context;
};

#if !defined(__forward__) && !defined(__drop__async__context__h)
#define __drop__async__context__h

// Includes

#include "promise.h"
#include "utils/template/is_callable.h"

namespace async
{
    template <typename type, typename lambda> class context
    {
        // Service nested classes

        struct exit
        {
        };

    private:

        // Members

        lambda _kernel;
        size_t _entrypoint;
        promise <type> _promise;

    public:

        // Constructors

        context(const lambda &);

        // Getters

        const size_t & entrypoint() const;
        const promise <type> & promise() const;

        // Methods

        exit leave(const size_t &);
        exit resolve(const type &);
        void run();
    };

    // Functions

    template <typename type, typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <type, lambda> &> :: value> * = nullptr> context <type, lambda> * contextualize(const lambda &);
};

#endif
