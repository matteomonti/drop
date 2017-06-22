// Includes

#include "bsize.h"
#include "endianess.hpp"

namespace bytewise
{
    // Constructors

    bsize :: bsize(const size_t & value) : _value(value)
    {
    }

    bsize :: bsize(const char * buffer, const size_t & size)
    {
        size_t map[] = {1, 1, 2, 4};
        size_t length = map[*(reinterpret_cast <const uint8_t *> (buffer))];

        if(length < size)
        {
            this->_value = -1;
            return;
        }

        switch(length)
        {
            case 1:
            {
                this->_value = (*(reinterpret_cast <const uint8_t *> (buffer))) & 0x7f;
                break;
            }
            case 2:
            {
                uint16_t value;
                endianess :: to <endianess :: big> (reinterpret_cast <char (&)[sizeof(uint16_t)]> (value), reinterpret_cast <const char (&)[sizeof(uint16_t)]> (*(reinterpret_cast <const uint16_t *> (buffer))));
                this->_value = (value & 0x3fff);
                break;
            }
            case 4:
            {
                uint32_t value;
                endianess :: to <endianess :: big> (reinterpret_cast <char (&)[sizeof(uint32_t)]> (value), reinterpret_cast <const char (&)[sizeof(uint32_t)]> (*(reinterpret_cast <const uint32_t *> (buffer))));
                this->_value = (value & 0x3fffffff);
                break;
            }
        }
    }

    // Methods

    size_t bsize :: write(char * buffer)
    {
        if(this->_value < 0x80)
        {
            *(reinterpret_cast <uint8_t *> (buffer)) = this->_value;
            return 1;
        }
        else if(this->_value < 0x4000)
        {
            uint16_t value = this->_value | 0x8000;
            endianess :: to <endianess :: big> (reinterpret_cast <char (&)[sizeof(uint16_t)]> (*(reinterpret_cast <uint16_t *> (buffer))), reinterpret_cast <const char (&)[sizeof(uint16_t)]> (value));
            return 2;
        }
        else
        {
            uint32_t value = this->_value | 0xc0000000;
            endianess :: to <endianess :: big> (reinterpret_cast <char (&)[sizeof(uint32_t)]> (*(reinterpret_cast <uint32_t *> (buffer))), reinterpret_cast <const char (&)[sizeof(uint32_t)]> (value));
            return 4;
        }
    }
};
