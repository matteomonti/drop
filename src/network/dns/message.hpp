#ifndef __drop__network__dns__message__hpp
#define __drop__network__dns__message__hpp

// Includes

#include "message.h"

namespace network :: dns
{
    // Methods

    template <qtype rtype> void message :: answer(const :: network :: dns :: record <rtype> & record, const bool & authoritative)
    {
        typedef data :: variant <:: network :: dns :: record <A>, :: network :: dns :: record <NS>, :: network :: dns :: record <CNAME>, :: network :: dns :: record <SOA>, :: network :: dns :: record <WKS>, :: network :: dns :: record <PTR>, :: network :: dns :: record <HINFO>, :: network :: dns :: record <MINFO>, :: network :: dns :: record <MX>, :: network :: dns :: record <TXT>, :: network :: dns :: record <null>> variant;

        this->_type = response;
        this->_authoritative = authoritative;
        this->_rescode = success;

        utils :: pnew <variant> records(1);
        records[0](variant :: construct <:: network :: dns :: record <rtype>> (record));

        this->answers._size = 1;
        this->answers._records = records;
    }
};

#endif
