// Forward declarations

namespace network
{
    namespace acceptors
    {
        class tcp;
    };
};

#if !defined(__forward__) && !defined(__drop__network__acceptors__tcp__h)
#define __drop__network__acceptors__tcp__h

// Libraries

#include <stdint.h>
#include <type_traits>
#include <thread>
#include <mutex>

// Includes

#include "network/sockets/tcp.h"
#include "network/connection.hpp"
#include "utils/template/is_callable.h"
#include "network/connectors/tcp.h"

namespace network :: acceptors
{
    class tcp
    {
    public:

        // Nested classes

        class sync
        {
            // Members

            sockets :: tcp _socket;

        public:

            // Constructors

            sync(const uint16_t &);

            // Methods

            connection accept();
        };

        class async
        {
        public:

            // Settings

            struct settings
            {
                static constexpr size_t callbacks = 16;
            };

        private:

            // Service nested classes

            class callback_base
            {
            public:

                // Destructor

                virtual ~callback_base();

                // Methods

                virtual void run(const connection &) = 0;
            };

            template <typename lambda> class callback : public callback_base
            {
                // Members

                lambda _callback;

            public:

                // Constructors

                callback(const lambda &);

                // Methods

                void run(const connection &);
            };

            // Members

            sync _acceptor;
            uint16_t _port;
            volatile bool _alive;

            callback_base * _callbacks[settings :: callbacks];

            std :: mutex _mutex;
            std :: thread _thread;

        public:

            // Constructors

            async(const uint16_t &);

            // Destructor

            ~async();

            // Methods

            template <typename etype, typename lambda, typename std :: enable_if_t <std :: is_same <etype, connection> :: value && utils :: is_callable <lambda, const connection &> :: value> * = nullptr> void on(const lambda &);
            void clear();

        private:

            // Private methods

            void run();
            void wake();
        };
    };
};

#endif
