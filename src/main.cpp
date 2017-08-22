#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/pool/pool.hpp"
#include "async/async.h"
#include "chrono/crontab.h"
#include "network/dispatcher.hpp"

network :: pool pool;

class protocol
{
    // Self

    typedef protocol self;

public:

    // Protocol

    $packet(packet, int);
    $packet(other_packet, int, double);
};

int main()
{
    network :: sockets :: udp socket;
    network :: dispatcher <protocol> sync_dispatcher(socket);

    network :: pool :: dispatcher <protocol> dispatcher = pool.bind(sync_dispatcher);
}

#endif
