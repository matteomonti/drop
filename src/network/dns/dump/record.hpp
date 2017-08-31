#ifndef __drop__network__dns__dump__record__hpp
#define __drop__network__dns__dump__record__hpp

// Includes

#include "record.h"

namespace network :: dns :: dump
{
    // Functions

    template <qtype type, std :: enable_if_t <type != null> *> void record_base(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record_base & record)
    {
        name(message, cursor, shortcuts, record.name());

        reinterpret_cast <uint16_t &> (message[cursor]) = htons(type);
        reinterpret_cast <uint16_t &> (message[cursor + 2]) = htons(record.qclass());
        reinterpret_cast <uint32_t &> (message[cursor + 4]) = htonl(record.ttl());

        cursor += 8;
    }
};

#endif
