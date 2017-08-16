// Forward declarations

namespace network
{
    template <typename> class dispatcher;
};

#if !defined(__forward__) && !defined(__drop__network__dispatcher__h)
#define __drop__network__dispatcher__h

// Libraries

#include <stddef.h>
#include <mutex>
#include <memory>

// Includes

#include "packet/macros.h"
#include "packet/count.h"
#include "packet/proxy.h"
#include "packet/in.h"
#include "sockets/udp.h"
#include "utils/template/is_callable.h"
#include "bytewise/bytewise.h"

namespace network
{
    template <typename protocol> class dispatcher
    {
        // Forward declarations

        class arc;

        // Service nested classes

        template <typename ptype> struct packet
        {
            template <typename> struct prototype;

            template <typename... types> struct prototype <:: network :: packet :: fields <types...>>
            {
                void operator () (const types & ...);
            };

            template <typename... types> struct is_callable
            {
                template <bool, bool> struct conditional;

                template <bool dummy> struct conditional <true, dummy>
                {
                    static constexpr bool value = utils :: is_callable <prototype <typename ptype :: fields>, const types & ...> :: value;
                };

                template <bool dummy> struct conditional <false, dummy>
                {
                    static constexpr bool value = false;
                };

                static constexpr bool value = conditional <:: network :: packet :: template in <protocol, ptype> :: value, false> :: value;
            };

            template <typename ftype> struct fproxy;

            template <typename... types> struct fproxy <:: network :: packet :: fields <types...>>
            {
                // Static methods

                static inline void send(arc &, const address &, const types & ...);
            };

            typedef fproxy <typename ptype :: fields> proxy;
        };


        class arc
        {
            // Members

            sockets :: udp _socket;

            struct
            {
                std :: mutex send;
                std :: mutex receive;
            } _mutex;

        public:

            // Constructors

            arc(const sockets :: udp &);

            // Destructor

            ~arc();

            // Getters

            const int & descriptor() const;

            // Setters

            void block(const bool &);

            // Methods

            template <typename ptype, typename... types> void send(const address &, const types & ...);
        };

        // Members

        std :: shared_ptr <arc> _arc;

    public:

        // Constructors

        dispatcher(const sockets :: udp &);

        // Methods

        template <typename ptype, typename... types, std :: enable_if_t <packet <ptype> :: template is_callable <types...> :: value> * = nullptr> void send(const address &, const types & ...);
    };
};

#endif
