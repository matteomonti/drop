#ifdef __main__

#include <iostream>
#include <unistd.h>
#include <thread>

#include "network/packet/packet.hpp"

int main()
{
    network :: packet :: packet <int> my_packet({"127.0.0.1", 1234}, 44);

    my_packet.visit([](const int & value)
    {
        std :: cout << value << std :: endl;
    });

    my_packet.visit([](const network :: address & remote, const int & value)
    {
        std :: cout << remote << ": " << value << std :: endl;
    });


    network :: packet :: packet <int, double> my_other_packet({"127.0.0.1", 1234}, {44, 55.6});

    my_other_packet.visit([](const int & int_value, const double & double_value)
    {
        std :: cout << int_value << ", " << double_value << std :: endl;
    });

    my_other_packet.visit([](const network :: address & remote, const int & int_value, const double & double_value)
    {
        std :: cout << remote << ": " << int_value << ", " << double_value << std :: endl;
    });
}

#endif
