// Forward declarations

namespace network
{
    class pool;
};

#if !defined(__forward__) && !defined(__drop__network__pool__pool__h)
#define __drop__network__pool__pool__h

// Libraries

#include <memory>
#include <thread>

// Includes

#include "queue.hpp"
#include "network/connection.hpp"
#include "async/promise.hpp"
#include "data/hashtable.hpp"
#include "thread/channel.hpp"
#include "chrono/timelock.hpp"
#include "data/variant.hpp"
#include "utils/template/function.hpp"
#include "network/dispatcher.hpp"

namespace network
{
    class pool
    {
    public:

        // Settings

        struct settings
        {
            static constexpr microtimestamp timeout = 30e6;
            static constexpr microtimestamp interval = 1e6;
        };

        // Nested classes

        class connection
        {
            // Friends

            friend class pool;

            // Service nested classes

            class arc
            {
                // Friends

                friend class pool;
                friend class connection;

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

        public:

            // Methods

            template <typename type> promise <void> send(const type &) const;
            template <typename type> promise <type> receive() const;
        };

        template <typename protocol> class dispatcher
        {
            // Friends

            friend class pool;

            // Service nested classes

            class arc
            {
                // Friends

                friend class pool;
                template <typename> friend class dispatcher;

                // Members

                pool & _pool;
                std :: shared_ptr <typename :: network :: dispatcher <protocol> :: arc> _dispatcher;

            public:

                // Constructors

                arc(pool &, const :: network :: dispatcher <protocol> &);

                // Destructor

                ~arc();
            };

            // Members

            std :: shared_ptr <arc> _arc;

            // Private constructors

            dispatcher(pool &, const :: network :: dispatcher <protocol> &);
        };

        // Service nested classes

        struct request
        {
            struct connection
            {
                pool :: connection connection;
                promise <void> promise;
                queue :: type type;
                size_t version;
            };
        };

        struct timeout
        {
            int descriptor;
            size_t version;
        };

        // Members

        queue _queue;

        volatile bool _alive;

        thread :: channel <data :: variant <request :: connection>> _new;
        data :: hashtable <int, data :: variant <request :: connection>> _pending;

        chrono :: timelock <timeout> _timeouts;

        struct
        {
            int read;
            int write;
        } _wake;

        volatile bool _awake;

        std :: mutex _mutex;
        std :: thread _thread;

    public:

        // Constructors

        pool();

        // Destructors

        ~pool();

        // Methods

        connection bind(const :: network :: connection &);
        template <typename protocol> dispatcher <protocol> bind(const :: network :: dispatcher <protocol> &);
        
    private:

        // Private methods

        template <typename type> promise <void> send(const connection &, const type &);
        template <typename type> promise <type> receive(const connection &);

        void run();
        void wake();

        // Static private members

        static size_t version;
    };
};

#endif
