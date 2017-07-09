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
        ssize_t _entrypoint;
        promise <type> _promise;

    public:

        // Constructors

        context(const lambda &);

        // Getters

        const ssize_t & entrypoint() const;
        const promise <type> & promise() const;

        // Methods

        exit leave(const ssize_t &, const class :: promise <void> &);
        template <typename ttype> exit leave(const ssize_t &, ttype &, const class :: promise <ttype> &);
        template <typename... rtypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(rtypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(rtypes) == 1)> * = nullptr> exit resolve(const rtypes & ...);
        void run();
    };

    // Functions

    template <typename type, typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <type, lambda> &> :: value> * = nullptr> promise <type> contextualize(const lambda &);
};

#endif
