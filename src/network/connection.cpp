// Includes

#include "connection.h"

namespace network
{
    // arc

    // Destructor

    connection :: arc :: ~arc()
    {
        this->_socket.visit([](auto && socket)
        {
            socket.close();
        });
    }

    // Methods

    void connection :: arc :: send(const bytewise :: buffer & buffer)
    {
        this->_socket.visit([&](auto && socket)
        {
            char sbuffer[sizeof(uint32_t)];

            size_t ssize = bytewise :: bsize(buffer.size()).write(sbuffer);
            socket.send(sbuffer, ssize);
            socket.send(buffer, buffer.size());
        });
    }
}
