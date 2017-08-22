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
#include <exception>

// Includes

#include "packet/macros.h"
#include "packet/count.h"
#include "packet/proxy.h"
#include "packet/in.h"
#include "sockets/udp.h"
#include "utils/template/is_callable.h"
#include "bytewise/bytewise.h"
#include "utils/template/are_same.h"
#include "data/variant.hpp"

namespace network
{
    template <typename protocol> class dispatcher
    {
        // Friends

        friend class pool;

    public:

        // Exceptions

        class wrong_header : public std :: exception
        {
            const char * what() const noexcept;
        };

    private:

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
            // Friend classes

            friend class pool;

            // Service nested classes

            struct remote
            {
                // Static methods

                static inline bool in(const address &);
                template <typename rtype, typename... rtypes> static inline bool in(const address &, const rtype &, const rtypes & ...);

                static inline bool match(const address &);
                template <typename rtype, typename... rtypes> static inline bool match(const address &, const rtype &, const rtypes & ...);
            };

            struct message
            {
                // Nested classes

                template <typename, typename> struct deserializer;

                template <typename ptype, typename... types> struct deserializer <ptype, :: network :: packet :: fields <types...>>
                {
                    // Static methods

                    static inline ptype run(const sockets :: udp :: packet &);
                };

                template <typename> struct wrapper;

                template <typename... ptypes> struct wrapper <data :: variant <ptypes...>>
                {
                    // Static methods

                    template <typename ptype> static inline data :: variant <ptypes...> run(const ptype &);
                };

                template <typename ptype> struct wrapper
                {
                    // Static methods

                    static inline ptype run(const ptype &);
                };

                // Static methods

                template <typename ret_type, typename... ptypes, std :: enable_if_t <sizeof...(ptypes) == 0> * = nullptr> static inline ret_type interpret(const size_t &, const sockets :: udp :: packet &);
                template <typename ret_type, typename ptype, typename...ptypes> static inline ret_type interpret(const size_t &, const sockets :: udp :: packet &);
            };

            // Members

            sockets :: udp _socket;

            struct
            {
                std :: mutex send;
                std :: mutex receive;
            } _mutex;

            volatile bool _locked;

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
            template <typename ptype, typename... ptypes, typename... rtypes> std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype> receive(const rtypes & ...);
        };

        // Members

        std :: shared_ptr <arc> _arc;

    public:

        // Constructors

        dispatcher(const sockets :: udp &);

        // Methods

        template <typename ptype, typename... types, std :: enable_if_t <packet <ptype> :: template is_callable <types...> :: value> * = nullptr> void send(const address &, const types & ...);
        template <typename ptype, typename... ptypes, typename... rtypes, std :: enable_if_t <:: network :: packet :: template in <protocol, ptype, ptypes...> :: value && utils :: are_same <address, rtypes...> :: value> * = nullptr> std :: conditional_t <(sizeof...(ptypes) > 0), data :: variant <ptype, ptypes...>, ptype> receive(const rtypes & ...);
    };
};

#endif
