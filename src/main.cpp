#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "network/address.h"

int main()
{
    network :: address my_address("google.com", 80);
    std :: cout << (my_address == network :: address("google.com", 80)) << std :: endl;
}

#endif
