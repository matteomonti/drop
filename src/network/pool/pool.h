// Forward declarations

namespace network
{
    class pool;
};

#if !defined(__forward__) && !defined(__drop__network__pool__pool__h)
#define __drop__network__pool__pool__h

// Libraries

#include <memory>

// Includes

#include "queue.hpp"
#include "network/connection.hpp"

namespace network
{
    class pool
    {
    public:

        // Nested classes

        class connection
        {
            // Friends

            friend class pool;

            // Service nested classes

            class arc
            {
                // Members

                pool & _pool;
                std :: shared_ptr <:: network :: connection :: arc> _connection;

            public:

                // Constructors

                arc(pool &, const :: network :: connection &);

                // Destructor

                ~arc();
            };

            // Members

            std :: shared_ptr <arc> _arc;

            // Private constructors

            connection(pool &, const :: network :: connection &);
        };

        // Methods

        connection bind(const :: network :: connection &);
    };
};

#endif
