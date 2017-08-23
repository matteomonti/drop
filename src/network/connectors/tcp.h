// Forward declarations

namespace network
{
    namespace connectors
    {
        class tcp;
    };
};

#if !defined(__forward__) && !defined(__drop__network__connectors__tcp__h)
#define __drop__network__connectors__tcp__h

// Libraries

#include <thread>
#include <exception>

// Includes

#include "network/address.h"
#include "network/sockets/tcp.h"
#include "network/connection.hpp"
#include "data/hashtable.hpp"
#include "network/pool/queue.hpp"
#include "async/promise.hpp"
#include "thread/channel.hpp"
#include "chrono/timelock.hpp"

namespace network :: connectors
{
    class tcp
    {
    public:

        // Nested classes

        class sync
        {
        public:

            // Static methods

            static connection connect(const address &);
        };

        class async
        {
        public:

            struct settings
            {
                static constexpr microtimestamp timeout = 10e6;
                static constexpr microtimestamp interval = 1e6;
            };

        private:

            // Service nested classes

            struct request
            {
                sockets :: tcp socket;
                promise <connection> promise;
                size_t version;
            };

            struct timeout
            {
                int descriptor;
                size_t version;
            };

            // Members

            queue _queue;

            volatile bool _alive;

            thread :: channel <request> _new;
            data :: hashtable <int, request> _pending;

            chrono :: timelock <timeout> _timeouts;

            struct
            {
                int read;
                int write;
            } _wake;

            std :: mutex _mutex;
            std :: thread _thread;

        public:

            // Constructors

            async();

            // Destructor

            ~async();

            // Methods

            promise <connection> connect(const address &);

        private:

            // Private methods

            void run();
            void wake();

            // Static members

            static size_t version;
        };
    };
};

#endif
