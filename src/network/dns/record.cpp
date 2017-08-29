// Includes

#include "record.h"

namespace network :: dns
{
    // record_base

    // Private constructors

    record_base :: record_base(const class name & name, const enum qclass & qclass, const uint32_t & ttl) : _name(name), _qclass(qclass), _ttl(ttl)
    {
    }

    // Getters

    const name & record_base :: name() const
    {
        return this->_name;
    }

    const qclass & record_base :: qclass() const
    {
        return this->_qclass;
    }

    const uint32_t & record_base :: ttl() const
    {
        return this->_ttl;
    }

    // record <A>

    // Constructors

    record <A> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class address :: ip & address) : record_base(name, qclass, ttl), _address(address)
    {
    }

    // Getters

    const class address :: ip & record <A> :: address() const
    {
        return this->_address;
    }

    // record <NS>

    // Constructors

    record <NS> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class name & nameserver) : record_base(name, qclass, ttl), _nameserver(nameserver)
    {
    }

    // Getters

    const class name & record <NS> :: nameserver() const
    {
        return this->_nameserver;
    }

    // record <CNAME>

    // Constructors

    record <CNAME> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class name & cname) : record_base(name, qclass, ttl), _cname(cname)
    {
    }

    // Getters

    const class name & record <CNAME> :: cname() const
    {
        return this->_cname;
    }

    // record <SOA>

    // Constructors

    record <SOA> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class name & mname, const class name & rname, const uint32_t & serial, const uint32_t & refresh, const uint32_t & retry, const uint32_t & expire, const uint32_t & minimum) : record_base(name, qclass, ttl), _mname(mname), _rname(rname), _serial(serial), _refresh(refresh), _retry(retry), _expire(expire), _minimum(minimum)
    {
    }

    // Getters

    const class name & record <SOA> :: mname() const
    {
        return this->_mname;
    }

    const class name & record <SOA> :: rname() const
    {
        return this->_rname;
    }

    const uint32_t & record <SOA> :: serial() const
    {
        return this->_serial;
    }

    const uint32_t & record <SOA> :: refresh() const
    {
        return this->_refresh;
    }

    const uint32_t & record <SOA> :: retry() const
    {
        return this->_retry;
    }

    const uint32_t & record <SOA> :: expire() const
    {
        return this->_expire;
    }

    const uint32_t & record <SOA> :: minimum() const
    {
        return this->_minimum;
    }

    // record <WKS>

    // Constructors

    record <WKS> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class address :: ip & address, const enum protocol & protocol, const class bitmask & bitmask) : record_base(name, qclass, ttl), _address(address), _protocol(protocol), _bitmask(bitmask)
    {
    }

    // Getters

    const class address :: ip & record <WKS> :: address() const
    {
        return this->_address;
    }

    const enum protocol & record <WKS> :: protocol() const
    {
        return this->_protocol;
    }

    const class bitmask & record <WKS> :: bitmask() const
    {
        return this->_bitmask;
    }

    // record <PTR>

    // Constructors

    record <PTR> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class name & pointer) : record_base(name, qclass, ttl), _pointer(pointer)
    {
    }

    // Getters

    const class name & record <PTR> :: pointer() const
    {
        return this->_pointer;
    }

    // record <HINFO>

    // Constructors

    record <HINFO> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const string & cpu, const string & os) : record_base(name, qclass, ttl), _cpu(cpu), _os(os)
    {
    }

    // Getters

    const string & record <HINFO> :: cpu() const
    {
        return this->_cpu;
    }

    const string & record <HINFO> :: os() const
    {
        return this->_os;
    }

    // record <MINFO>

    // Constructors

    record <MINFO> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const class name & rmailbox, const class name & emailbox) : record_base(name, qclass, ttl), _rmailbox(rmailbox), _emailbox(emailbox)
    {
    }

    // Getters

    const class name & record <MINFO> :: rmailbox() const
    {
        return this->_rmailbox;
    }

    const class name & record <MINFO> :: emailbox() const
    {
        return this->_emailbox;
    }

    // record <MX>

    // Constructors

    record <MX> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const uint16_t & preference, const class name & exchange) : record_base(name, qclass, ttl), _preference(preference), _exchange(exchange)
    {
    }

    // Getters

    const uint16_t & record <MX> :: preference() const
    {
        return this->_preference;
    }

    const class name & record <MX> :: exchange() const
    {
        return this->_exchange;
    }

    // record <TXT>

    // Settings

    constexpr size_t record <TXT> :: settings :: max_texts;

    // Constructors

    record <TXT> :: record(const class name & name, const enum qclass & qclass, const uint32_t & ttl, const string * texts, const size_t & count) : record_base(name, qclass, ttl), _count(count)
    {
        for(size_t i = 0; i < this->_count; i++)
            this->_texts[i] = texts[i];
    }

    // Getters

    const size_t & record <TXT> :: count() const
    {
        return this->_count;
    }

    // Operators

    const string & record <TXT> :: operator [] (const size_t & index) const
    {
        return this->_texts[index];
    }
};
