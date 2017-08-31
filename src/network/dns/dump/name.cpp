// Includes

#include "name.h"

namespace network :: dns :: dump
{
    // Functions
    
    void name(char * message, size_t & wcursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: name & name)
    {
        bool compress = shortcuts.size();

        size_t rcursor = 0;

        while(rcursor < name.length())
        {
            bytewise :: buffer tail(bytewise :: buffer :: reference, const_cast <char *> (&(name[rcursor])), name.length() - rcursor);

            if(compress)
            {
                data :: optional <uint16_t> shortcut = shortcuts[tail];

                if(shortcut)
                {
                    reinterpret_cast <uint16_t &> (message[wcursor]) = htons(*shortcut | 0xc000);
                    wcursor += 2;

                    return;
                }
            }

            shortcuts.add(tail, wcursor);

            uint8_t lsize = 0;
            while(name[rcursor + lsize] != '.' && (rcursor + lsize) < name.length())
                lsize++;

            reinterpret_cast <uint8_t &> (message[wcursor++]) = lsize;
            memcpy(&(message[wcursor]), &(name[rcursor]), lsize);

            wcursor += lsize;
            rcursor += lsize + 1;
        }

        message[wcursor++] = 0;
    }
};
