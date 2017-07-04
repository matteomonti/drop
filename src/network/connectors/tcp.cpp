// Includes

#include "tcp.h"

namespace network :: connectors
{
    // sync

    // Static methods

    connection tcp :: sync :: connect(const address & remote)
    {
        sockets :: tcp socket;
        socket.connect(remote);
        return connection(socket);
    }
};
