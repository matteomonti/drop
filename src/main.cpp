#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "network/sockets/tcp.h"

int main()
{
    network :: sockets :: tcp my_tcp_socket;
    my_tcp_socket.bind(1236);
    my_tcp_socket.listen();

    network :: sockets :: tcp my_connection = my_tcp_socket.accept();
    my_connection.receive_timeout(5e6);
    my_connection.send("Hello, World!", 13);

    char buffer[1024];
    memset(buffer, '\0', 1024);
    my_connection.receive(buffer, 1024);

    std :: cout << buffer << std :: endl;

    my_connection.close();
    my_tcp_socket.close();
}

#endif
