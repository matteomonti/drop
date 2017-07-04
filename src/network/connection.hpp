#ifndef __drop__network__connection__hpp
#define __drop__network__connection__hpp

// Includes

#include "connection.h"

namespace network
{
    // arc

    // Constructors

    template <typename type> connection :: arc :: arc(const type & socket) : _socket(decltype(_socket) :: construct <type> (socket))
    {
    }

    // connection

    // Private constructors

    template <typename type, utils :: enable_in_t <type, sockets :: tcp> *> connection :: connection(const type & socket) : _arc(new arc(socket))
    {
    }
}

#endif
