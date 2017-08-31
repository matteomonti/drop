#ifndef __drop__network__dns__dump__query__hpp
#define __drop__network__dns__dump__query__hpp

// Includes

#include "query.h"

namespace network :: dns :: dump
{
    template <qtype type, typename std :: enable_if_t <type != null> *> void query(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: query <type> & query)
    {
        name(message, cursor, shortcuts, query.name());

        reinterpret_cast <uint16_t &> (message[cursor]) = htons(type);
        reinterpret_cast <uint16_t &> (message[cursor + 2]) = htons(query.qclass());

        cursor += 4;
    }
};

#endif
