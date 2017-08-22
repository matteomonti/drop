// Forward declarations

namespace utils
{
    template <typename> class function;
};

#if !defined(__forward__) && !defined(__drop__utils__template__function__h)
#define __drop__utils__template__function__h

// Libraries

#include <type_traits>
#include <memory>

// Includes

#include "is_callable.h"

namespace utils
{
    template <typename ret_type, typename... types> class function <ret_type (types...)>
    {
        // Service nested classes

        class base
        {
        public:

            // Operators

            virtual ret_type operator () (types && ...);
        };

        template <typename lambda> class wrapper : public base
        {
            // Members

            lambda _functor;

        public:

            // Constructors

            wrapper(const lambda &);

            // Operators

            ret_type operator () (types && ...);
        };

        // Members

        std :: unique_ptr <base> _functor;

    public:

        // Constructors

        function();
        template <typename lambda, std :: enable_if_t <is_callable <lambda, types...> :: value && std :: is_same <std :: result_of_t <lambda(types...)>, ret_type> :: value> * = nullptr> function(const lambda &);

        // Methods

        void release();

        // Operators

        ret_type operator () (types && ...) const;
        template <typename lambda, std :: enable_if_t <is_callable <lambda, types...> :: value && std :: is_same <std :: result_of_t <lambda(types...)>, ret_type> :: value> * = nullptr> void operator = (const lambda &);
    };
};

#endif
