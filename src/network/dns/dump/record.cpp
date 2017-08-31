// Includes

#include "record.hpp"

namespace network :: dns :: dump
{
    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <A> & record)
    {
        record_base <A> (message, cursor, shortcuts, record);

        reinterpret_cast <uint16_t &> (message[cursor]) = htons(4);
        reinterpret_cast <class address :: ip &> (message[cursor + 2]) = record.address();

        cursor += 6;
    }
};
