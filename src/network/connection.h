// Forward declarations

namespace network
{
    class connection;
};

#if !defined(__forward__) && !defined(__drop__network__connection__h)
#define __drop__network__connection__h

// Libraries

#include <memory>
#include <type_traits>

// Includes

#include "data/variant.hpp"
#include "sockets/tcp.h"
#include "utils/template/enable_in.h"

namespace network
{
    class connection
    {
        // Service nested classes

        class arc
        {
            // Friends

            friend class connection;

            // Members

            data :: variant <sockets :: tcp> _socket;

            // Constructors

            template <typename type> arc(const type &);
        };

        // Members

        std :: shared_ptr <arc> _arc;

    public:

        // Constructors

        template <typename type, utils :: enable_in_t <type, sockets :: tcp> * = nullptr> connection(const type &);
    };
};

#endif
