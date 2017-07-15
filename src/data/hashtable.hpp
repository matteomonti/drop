#ifndef __drop__data__hashtable__hpp
#define __drop__data__hashtable__hpp

// Includes

#include "hashtable.h"
#include "optional.hpp"

namespace data
{
    // Constructors

    template <typename ktype, typename vtype> hashtable <ktype, vtype> :: hashtable() : _entries(new std :: aligned_storage_t <sizeof(optional <entry>), alignof(optional <entry>)> [settings :: base_alloc]), _size(0), _alloc(settings :: base_alloc)
    {
        for(size_t i = 0; i < this->_alloc; i++)
            new (&(this->_entries[i])) optional <entry> (null);
    }

    // Destructor

    template <typename ktype, typename vtype> hashtable <ktype, vtype> :: ~hashtable()
    {
        for(size_t i = 0; i < this->_alloc; i++)
            reinterpret_cast <optional <entry> &> (this->_entries[i]).~optional();

        delete [] this->_entries;
    }

    // Methods

    template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: add(const ktype & key, const vtype & value)
    {
        if(this->_alloc / (this->_size + 1) < settings :: expand_threshold)
            this->realloc(this->_alloc * 2);

        size_t index = hash(key) % this->_alloc;

        while(reinterpret_cast <optional <entry> &> (this->_entries[index]))
            index = (index + 1) % this->_alloc;

        reinterpret_cast <optional <entry> &> (this->_entries[index]) = {.key = key, .value = value};
        this->_size++;
    }

    template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: remove(const ktype & key)
    {
        size_t i = this->slot(key);

        if(this->_alloc / (this->_size + 1) > settings :: contract_threshold && this->_alloc > settings :: base_alloc)
        {
            reinterpret_cast <optional <entry> &> (this->_entries[i]) = null;
            this->realloc(this->_alloc / 2);
        }
        else
        {
            size_t j = i;
            size_t k;

            while(true)
            {
                reinterpret_cast <optional <entry> &> (this->_entries[i]) = null;

                do
                {
                    j = (j + 1) % this->_alloc;

                    if(!reinterpret_cast <optional <entry> &> (this->_entries[j]))
                        goto end;

                    k = hash(reinterpret_cast <optional <entry> &> (this->_entries[j])->key) % this->_alloc;
                } while((i <= j) ? ((i < k) && (k <= j)) : ((i < k) || (k <= j)));

                reinterpret_cast <optional <entry> &> (this->_items[i]) = reinterpret_cast <optional <entry> &> (this->_items[j]);
                i = j;
            }

            end:;
            this->_size--;
        }
    }

    // Private static methods

    template <typename ktype, typename vtype> template <typename type, std :: enable_if_t <std :: is_arithmetic <type> :: value && sizeof(type) == 4> *> size_t hashtable <ktype, vtype> :: hash(const type & key)
    {
        uint32_t hash = reinterpret_cast <const uint32_t &> (key);

        int prime = 0x27d4eb2d;
        hash = (hash ^ 61) ^ (hash >> 16);
        hash = hash + (hash << 3);
        hash = hash ^ (hash >> 4);
        hash = hash * prime;
        hash = hash ^ (hash >> 15);

        return hash;
    }

    template <typename ktype, typename vtype> template <typename type, std :: enable_if_t <std :: is_arithmetic <type> :: value && sizeof(type) == 8> *> size_t hashtable <ktype, vtype> :: hash(const type & key)
    {
        uint64_t hash = reinterpret_cast <const uint64_t &> (key);

        hash = (~hash) + (hash << 21);
        hash = hash ^ (hash >> 24);
        hash = (hash + (hash << 3)) + (hash << 8);
        hash = hash ^ (hash >> 14);
        hash = (hash + (hash << 2)) + (hash << 4);
        hash = hash ^ (hash >> 28);
        hash = hash + (hash << 31);

        return hash;
    }
};

#endif
