#ifdef __main__

#include <iostream>
#include <type_traits>
#include <string>
#include <iomanip>

#include "network/acceptors/tcp.h"

int main()
{
    network :: acceptors :: tcp :: sync my_acceptor(1235);
    network :: connection my_connection = my_acceptor.accept();
}

#endif
