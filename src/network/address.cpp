// Includes

#include "address.h"

namespace network
{
    // host_not_found

    const char * address :: host_not_found :: what() const noexcept
    {
        return "Host not found.";
    }

    // ip

    // Constructors

    address :: ip :: ip()
    {
        this->_ip.s_addr = htonl(INADDR_ANY);
    }

    address :: ip :: ip(const char * host)
    {
        hostent * record = gethostbyname(host);

        if(record)
            memcpy(&(this->_ip), record->h_addr, sizeof(in_addr));
        else
            throw host_not_found();
    }

    address :: ip :: ip(const address & address)
    {
        this->_ip.s_addr = address._address.sin_addr.s_addr;
    }

    // Operators

    bool address :: ip :: operator == (const ip & rho) const
    {
        return this->_ip.s_addr == rho._ip.s_addr;
    }

    // Casting

    address :: ip :: operator in_addr & ()
    {
        return this->_ip;
    }

    address :: ip :: operator const in_addr & () const
    {
        return this->_ip;
    }

    // port

    // Constructors

    address :: port :: port() : _port(htons(0))
    {
    }

    address :: port :: port(const uint16_t & port) : _port(htons(port))
    {
    }

    address :: port :: port(const address & address) : _port(address._address.sin_port)
    {
    }

    // Operators

    bool address :: port :: operator == (const port & rho) const
    {
        return this->_port == rho._port;
    }

    // Casting

    address :: port :: operator in_port_t & ()
    {
        return this->_port;
    }

    address :: port :: operator const in_port_t & () const
    {
        return this->_port;
    }

    // address

    // Constructors

    address :: address() : address(ip(), port())
    {
    }

    address :: address(const char * host, const uint16_t & port) : address((class ip){host}, (class port){port})
    {
    }

    address :: address(const class ip & ip, const class port & port)
    {
        this->_address.sin_family = AF_INET;
        this->_address.sin_addr = (const in_addr &) ip;
        this->_address.sin_port = (const in_port_t &) port;

        #ifdef __APPLE__
        memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));
        #endif
    }

    address :: address(const sockaddr_in & address) : _address(address)
    {
    }

    // Getters

    class address :: ip address :: ip() const
    {
        return (class ip)(*this);
    }

    class address :: port address :: port() const
    {
        return (class port)(*this);
    }

    // Operators

    bool address :: operator == (const address & rho) const
    {
        return this->_address.sin_addr.s_addr == rho._address.sin_addr.s_addr && this->_address.sin_port == rho._address.sin_port;
    }

    bool address :: operator == (const sockaddr_in & rho) const
    {
        return this->_address.sin_addr.s_addr == rho.sin_addr.s_addr && this->_address.sin_port == rho.sin_port;
    }

    // Casting

    address :: operator bool () const
    {
        return this->_address.sin_addr.s_addr || this->_address.sin_port;
    }

    address :: operator sockaddr_in & ()
    {
        return this->_address;
    }

    address :: operator const sockaddr_in & () const
    {
        return this->_address;
    }

    // Ostream integration

    std :: ostream & operator << (std :: ostream & out, const class address :: ip & ip)
    {
        char buffer[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, &ip, buffer, INET_ADDRSTRLEN);
        return out << buffer;
    }

    std :: ostream & operator << (std :: ostream & out, const class address :: port & port)
    {
        return out << ntohs((const in_port_t &) port);
    }

    std :: ostream & operator << (std :: ostream & out, const address & address)
    {
        return out << "[" << address.ip() << ":" << address.port() << "]";
    }
};
