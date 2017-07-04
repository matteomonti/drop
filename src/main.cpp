#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "network/connection.hpp"

int main()
{
    network :: sockets :: tcp my_tcp_socket;
    my_tcp_socket.bind(1234);
    my_tcp_socket.listen();
    network :: sockets :: tcp my_inbound_connection = my_tcp_socket.accept();

    network :: connection my_connection(my_inbound_connection);
}

#endif
