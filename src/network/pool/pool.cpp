// Includes

#include "pool.hpp"

namespace network
{
    // arc

    // Constructors

    pool :: connection :: arc :: arc(pool & pool, const :: network :: connection & connection) : _pool(pool), _connection(connection._arc)
    {
        this->_connection->_mutex.send.lock();
        this->_connection->_mutex.receive.lock();
    }

    // Destructor

    pool :: connection :: arc :: ~arc()
    {
        this->_connection->_mutex.send.unlock();
        this->_connection->_mutex.receive.unlock();
    }

    // connection

    // Private constructors

    pool :: connection :: connection(pool & pool, const :: network :: connection & connection) : _arc(new arc(pool, connection))
    {
    }

    // pool

    pool :: connection pool :: bind(const :: network :: connection & connection)
    {
        return (class connection){*this, connection};
    }
};
