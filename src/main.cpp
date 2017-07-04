#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "network/acceptors/tcp.h"
#include "network/connectors/tcp.h"

int main()
{
    network :: connection my_connection = network :: connectors :: tcp :: sync :: connect({"google.com", 80});
    std :: cout << "Connection open" << std :: endl;
}

#endif
