// Forward declarations

namespace network
{
    namespace dns
    {
        class message;
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__message__h)
#define __drop__network__dns__message__h

// Libraries

#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

// Includes

#include "data/variant.hpp"
#include "utils/misc/pnew.hpp"
#include "query.hpp"
#include "parse/query.h"
#include "dump/query.hpp"
#include "record.h"
#include "parse/record.h"
#include "dump/record.h"

namespace network :: dns
{
    class message
    {
    public:

        // Nested enums

        enum type {query, response};
        enum opcode {standard = 0, inverse = 1, status = 2};
        enum rescode {success = 0, format = 1, server = 2, name = 3, unimplemented = 4, refused = 5};

        // Nested classes

        struct dump
        {
            char message[512];
            size_t size;
        };

    private:

        // Service nested classes

        class recursion
        {
            // Friends

            friend class message;

            // Members

            bool _desired;
            bool _available;

        public:

            // Getters

            const bool & desired() const;
            const bool & available() const;
        };

        class queries
        {
            // Friends

            friend class message;

            // Members

            data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> * _queries;
            size_t _size;

        public:

            // Getters

            const size_t & size() const;

            // Operators

            const data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> & operator [] (const size_t &) const;
        };

        class records
        {
            // Friends

            friend class message;

            // Members

            data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>> * _records;
            size_t _size;

        public:

            // Getters

            const size_t & size() const;

            // Operators

            const data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>> & operator [] (const size_t &) const;
        };

        // Members

        bool _valid;

        uint16_t _id;
        type _type;
        opcode _opcode;
        bool _authoritative;
        bool _truncated;

        rescode _rescode;

    public:

        // Public members

        recursion recursion;
        queries queries;
        records answers;
        records authorities;
        records extras;

        // Constructors

        message(const char *, const size_t &);

        // Destructor

        ~message();

        // Getters

        const uint16_t & id() const;
        const type & type() const;
        const opcode & opcode() const;
        const bool & authoritative() const;
        const bool & truncated() const;
        const rescode & rescode() const;

        // Methods

        template <qtype rtype> void answer(const :: network :: dns :: record <rtype> &, const bool &);

        class dump dump() const;
    };
};

#endif
