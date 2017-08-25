// Includes

#include "message.h"

namespace network :: dns
{
    // recursion

    // Getters

    const bool & message :: recursion :: desired() const
    {
        return this->_desired;
    }

    const bool & message :: recursion :: available() const
    {
        return this->_available;
    }

    // queries

    // Getters

    const size_t & message :: queries :: size() const
    {
        return this->_size;
    }

    // Operators

    const data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>> & message :: queries :: operator [] (const size_t & index) const
    {
        return this->_queries[index];
    }

    // message

    // Constructors

    message :: message(const char * message, const size_t & size) : _valid(true)
    {
        if(size < 12)
        {
            this->_valid = false;
            return;
        }

        this->_id = ntohs(reinterpret_cast <const uint16_t &> (message[0]));

        this->_type = (reinterpret_cast <const unsigned char &> (message[2]) & 0x80) ? response : query;
        this->_opcode = static_cast <enum opcode> ((reinterpret_cast <const unsigned char &> (message[2]) >> 3) & 0x7);
        this->_authoritative = reinterpret_cast <const unsigned char &> (message[2]) & 0x4;
        this->_truncated = reinterpret_cast <const unsigned char &> (message[2]) & 0x2;
        this->recursion._desired = reinterpret_cast <const unsigned char &> (message[2]) & 0x1;
        this->recursion._available = reinterpret_cast <const unsigned char &> (message[3]) & 0x80;
        this->_rescode = static_cast <enum rescode> (reinterpret_cast <const unsigned char &> (message[3]) & 0xf);

        this->queries._size = ntohs(reinterpret_cast <const uint16_t &> (message[4]));

        if(this->queries._size)
        {
            utils :: pnew <data :: variant <:: network :: dns :: query <A>, :: network :: dns :: query <NS>, :: network :: dns :: query <CNAME>, :: network :: dns :: query <SOA>, :: network :: dns :: query <WKS>, :: network :: dns :: query <PTR>, :: network :: dns :: query <HINFO>, :: network :: dns :: query <MINFO>, :: network :: dns :: query <MX>, :: network :: dns :: query <TXT>, :: network :: dns :: query <null>>> queries(this->queries._size);
            this->queries._queries = queries;

            size_t cursor = 12;

            for(size_t q = 0; q < this->queries._size; q++)
                queries[q](parse :: query(message, size, cursor));
        }
    }

    // Destructor

    message :: ~message()
    {
        if(this->queries._size)
            utils :: pdelete(this->queries._queries, this->queries._size);
    }

    // Getters

    const uint16_t & message :: id() const
    {
        return this->_id;
    }

    const enum message :: type & message :: type() const
    {
        return this->_type;
    }

    const enum message :: opcode & message :: opcode() const
    {
        return this->_opcode;
    }

    const bool & message :: authoritative() const
    {
        return this->_authoritative;
    }

    const bool & message :: truncated() const
    {
        return this->_truncated;
    }

    const enum message :: rescode & message :: rescode() const
    {
        return this->_rescode;
    }
};
