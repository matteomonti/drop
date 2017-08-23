// Forward declarations

namespace async
{
    template <typename, typename> class context;
};

#if !defined(__forward__) && !defined(__drop__async__context__h)
#define __drop__async__context__h

// Libraries

#include <exception>

// Includes

#include "promise.h"
#include "utils/template/is_callable.h"
#include "data/optional.hpp"

namespace async
{
    template <typename type, typename lambda> class context
    {
    public:

        // Settings

        struct settings
        {
            static constexpr size_t handlers = 16;
        };

    private:

        // Service nested classes

        struct exit
        {
            bool resume = false;
        };

        // Members

        lambda _kernel;
        ssize_t _entrypoint;
        promise <type> _promise;

        struct
        {
            ssize_t entrypoints[settings :: handlers];
            size_t size;
        } _handlers;

        std :: exception_ptr _exception;

    public:

        // Public members

        bool flag;

        // Constructors

        context(const lambda &);

        // Getters

        const ssize_t & entrypoint() const;
        const promise <type> & promise() const;

        // Methods

        void handler();
        void handler(const ssize_t &);

        void rethrow();

        exit leave(const ssize_t &, const class :: promise <void> &);
        template <typename ttype> exit leave(const ssize_t &, ttype &, const class :: promise <ttype> &);

        template <typename... rtypes, std :: enable_if_t <(std :: is_same <type, void> :: value && sizeof...(rtypes) == 0) || (!(std :: is_same <type, void> :: value) && sizeof...(rtypes) == 1)> * = nullptr> exit resolve(const rtypes & ...);
        void run();
    };

    // Functions

    template <typename type, typename lambda, std :: enable_if_t <utils :: is_callable <lambda, context <type, lambda> &> :: value> * = nullptr> promise <type> contextualize(const lambda &);
};

#endif
