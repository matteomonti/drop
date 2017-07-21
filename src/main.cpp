#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/sockets/udp.h"

uint16_t local, remote;
network :: sockets :: udp my_socket;

void receiver()
{
    while(true)
    {
        auto packet = my_socket.receive();
        std :: cout << packet.message() << std :: endl;
    }
}

int main(int narg, char ** args)
{
    if(narg < 3)
    {
        std :: cout << "./main.out local_port remote_port" << std :: endl;
        return -1;
    }

    local = atoi(args[1]);
    remote = atoi(args[2]);

    my_socket.bind(local);
    std :: thread receiver_thread(receiver);

    while(true)
    {
        char buffer[network :: sockets :: udp :: settings :: mtu];
        std :: cin.getline(buffer, network :: sockets :: udp :: settings :: mtu);

        my_socket.send({"localhost", remote}, buffer, strlen(buffer));
    }
}

#endif
