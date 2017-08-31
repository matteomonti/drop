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

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <NS> & record)
    {
        record_base <NS> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;
        name(message, cursor, shortcuts, record.nameserver());

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <CNAME> & record)
    {
        record_base <CNAME> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;
        name(message, cursor, shortcuts, record.cname());

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <SOA> & record)
    {
        record_base <SOA> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;

        name(message, cursor, shortcuts, record.mname());
        name(message, cursor, shortcuts, record.rname());
        reinterpret_cast <uint32_t &> (message[cursor]) = htonl(record.serial());
        reinterpret_cast <uint32_t &> (message[cursor + 4]) = htonl(record.refresh());
        reinterpret_cast <uint32_t &> (message[cursor + 8]) = htonl(record.retry());
        reinterpret_cast <uint32_t &> (message[cursor + 12]) = htonl(record.expire());
        reinterpret_cast <uint32_t &> (message[cursor + 16]) = htonl(record.minimum());

        cursor += 20;
        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <WKS> & record)
    {
        record_base <WKS> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;

        reinterpret_cast <class address :: ip &> (message[cursor]) = record.address();
        reinterpret_cast <uint8_t &> (message[cursor + 4]) = record.protocol();
        memcpy(&(message[cursor + 5]), record.bitmask(), record.bitmask().size());

        cursor += (5 + record.bitmask().size());
        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <PTR> & record)
    {
        record_base <PTR> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;
        name(message, cursor, shortcuts, record.pointer());

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <HINFO> & record)
    {
        record_base <HINFO> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;

        string(message, cursor, record.cpu());
        string(message, cursor, record.os());

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <MINFO> & record)
    {
        record_base <MINFO> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;

        name(message, cursor, shortcuts, record.rmailbox());
        name(message, cursor, shortcuts, record.emailbox());

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <MX> & record)
    {
        record_base <MX> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;
        reinterpret_cast <uint16_t &> (message[cursor]) = htons(record.preference());
        cursor += 2;

        name(message, cursor, shortcuts, record.exchange());

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }

    void record(char * message, size_t & cursor, data :: hashtable <bytewise :: buffer, uint16_t> & shortcuts, const :: network :: dns :: record <TXT> & record)
    {
        record_base <TXT> (message, cursor, shortcuts, record);
        size_t rscursor = cursor;

        cursor += 2;

        for(size_t i = 0; i < record.count(); i++)
            string(message, cursor, record[i]);

        reinterpret_cast <uint16_t &> (message[rscursor]) = htons(cursor - (rscursor + 2));
    }
};
