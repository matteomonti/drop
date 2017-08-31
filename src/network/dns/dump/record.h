// Forward declarations

namespace network
{
    namespace dns
    {
        namespace dump
        {
        };
    };
};

#if !defined(__forward__) && !defined(__drop__network__dns__dump__record__h)
#define __drop__network__dns__dump__record__h

// Libraries

#include <stdint.h>

// Includes

#include "name.h"
#include "string.h"
#include "network/dns/record.h"
#include "network/address.h"
#include "network/dns/bitmask.h"

namespace network :: dns :: dump
{
    template <qtype type, std :: enable_if_t <type != null> * = nullptr> void record_base(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record_base &);

    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <A> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <NS> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <CNAME> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <SOA> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <WKS> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <PTR> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <HINFO> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <MINFO> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <MX> &);
    void record(char *, size_t &, data :: hashtable <bytewise :: buffer, uint16_t> &, const :: network :: dns :: record <TXT> &);
};

#endif
