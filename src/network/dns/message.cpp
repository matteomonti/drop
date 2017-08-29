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

    // records

    // Getters

    const size_t & message :: records :: size() const
    {
        return this->_size;
    }

    // Operators

    const data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>> & message :: records :: operator [] (const size_t & index) const
    {
        return this->_records[index];
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
            {
                queries[q](parse :: query(message, size, cursor));
                this->queries._queries[q].visit([this](:: network :: dns :: query <null> &)
                {
                    this->_valid = false;
                });
            }
        }

        this->answers._size = ntohs(reinterpret_cast <const uint16_t &> (message[6]));

        if(this->answers._size)
        {
            utils :: pnew <data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>>> records(this->answers._size);
            this->answers._records = records;

            size_t cursor = 12;

            for(size_t q = 0; q < this->answers._size; q++)
            {
                records[q](parse :: record(message, size, cursor));
                this->answers._records[q].visit([this](:: network :: dns :: record <null> &)
                {
                    this->_valid = false;
                });
            }
        }

        this->authorities._size = ntohs(reinterpret_cast <const uint16_t &> (message[8]));

        if(this->authorities._size)
        {
            utils :: pnew <data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>>> records(this->authorities._size);
            this->authorities._records = records;

            size_t cursor = 12;

            for(size_t q = 0; q < this->authorities._size; q++)
            {
                records[q](parse :: record(message, size, cursor));
                this->authorities._records[q].visit([this](:: network :: dns :: record <null> &)
                {
                    this->_valid = false;
                });
            }
        }

        this->extras._size = ntohs(reinterpret_cast <const uint16_t &> (message[10]));

        if(this->extras._size)
        {
            utils :: pnew <data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>>> records(this->extras._size);
            this->extras._records = records;

            size_t cursor = 12;

            for(size_t q = 0; q < this->extras._size; q++)
            {
                records[q](parse :: record(message, size, cursor));
                this->extras._records[q].visit([this](:: network :: dns :: record <null> &)
                {
                    this->_valid = false;
                });
            }
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
