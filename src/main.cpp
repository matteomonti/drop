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
        try
        {
            auto packet = my_socket.receive();

            if(packet)
                std :: cout << packet.message() << std :: endl;
            else
                std :: cout << "(silence)" << std :: endl;
        }
        catch(...)
        {
            std :: cout << "Exception" << std :: endl;
        }

        usleep(1.e6);
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
    my_socket.block(false);

    std :: thread receiver_thread(receiver);

    while(true)
    {
        char buffer[network :: sockets :: udp :: settings :: mtu];
        std :: cin.getline(buffer, network :: sockets :: udp :: settings :: mtu);

        my_socket.send({"localhost", remote}, buffer, strlen(buffer));
    }
}

#endif
