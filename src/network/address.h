// Forward declarations

namespace network
{
    class address;
};

#if !defined(__forward__) && !defined(__drop__network__address__h)
#define __drop__network__address__h

// Libraries

#include <stddef.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <iostream>

// Includes

#include "bytewise/bytewise.h"

namespace network
{
    class address
    {
    public:

        // Exceptions

        class host_not_found : public std :: exception
        {
            const char * what() const noexcept;
        };

        // Nested classes

        class ip
        {
            // Self

            typedef ip self;

            // Members

            in_addr _ip;

            // Bytewise

            bytewise(_ip, endianess :: local);

        public:

            // Constructors

            ip();
            ip(const char *);
            ip(const address &);

            // Operators

            bool operator == (const ip &) const;

            // Casting

            explicit operator in_addr & ();
            explicit operator const in_addr & () const;
        };

        class port
        {
            // Self

            typedef port self;

            // Members

            in_port_t _port;

            // Bytewise

            bytewise(_port, endianess :: local);

        public:

            // Constructors

            port();
            port(const uint16_t &);
            port(const address &);

            // Operators

            bool operator == (const port &) const;

            // Casting

            explicit operator in_port_t & ();
            explicit operator const in_port_t & () const;
        };

    private:

        // Self

        typedef address self;

        // Members

        sockaddr_in _address;

        // Bytewise

        bytewise(_address.sin_addr.s_addr, endianess :: local);
        bytewise(_address.sin_port, endianess :: local);

    public:

        // Constructors

        address();
        address(const char *, const uint16_t &);
        address(const class ip &, const class port &);
        address(const sockaddr_in &);

        // Getters

        class ip ip() const;
        class port port() const;

        // Operators

        bool operator == (const address &) const;
        bool operator == (const sockaddr_in &) const;

        // Casting

        operator bool () const;

        operator sockaddr_in & ();
        operator const sockaddr_in & () const;
    };

    // Ostream integration

    std :: ostream & operator << (std :: ostream &, const class address :: ip &);
    std :: ostream & operator << (std :: ostream &, const class address :: port &);
    std :: ostream & operator << (std :: ostream &, const address &);
};

#endif
