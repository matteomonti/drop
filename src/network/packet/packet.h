// Forward declarations

namespace network
{
    namespace packet
    {
        template <typename...> class packet;
    };
};

#if !defined(__forward__) && !defined(__drop__network__packet__packet__h)
#define __drop__network__packet__packet__h

// Libraries

#include <type_traits>

// Includes

#include "bytewise/tuple.hpp"
#include "network/address.h"
#include "utils/template/is_callable.h"
#include "macros.h"

namespace network :: packet
{
    template <typename type> class packet <type>
    {
        // Members

        address _remote;
        type _message;

    public:

        // Typedefs

        typedef :: network :: packet :: fields <type> fields;

        // Constructors

        packet(const address &, const type &);

        // Methods

        template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const address &, const type &> :: value> * = nullptr> void visit(const lambda &) const;
        template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const type &> :: value> * = nullptr> void visit(const lambda &) const;
    };

    template <typename... types> class packet
    {
        // Typedefs

        typedef :: network :: packet :: fields <types...> fields;

        // Members

        address _remote;
        bytewise :: tuple <types...> _message;

    public:

        // Constructors

        packet(const address &, const bytewise :: tuple <types...> &);

        // Methods

        template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const address &, const types & ...> :: value> * = nullptr> void visit(const lambda &) const;
        template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const types & ...> :: value> * = nullptr> void visit(const lambda &) const;
    };
};

#endif
