#ifndef __drop__data__hashtable__hpp
#define __drop__data__hashtable__hpp

// Includes

#include "hashtable.h"
#include "optional.hpp"
#include "utils/misc/pnew.hpp"

namespace data
{
    // Settings

    template <typename ktype, typename vtype> constexpr size_t hashtable <ktype, vtype> :: settings :: base_alloc;
    template <typename ktype, typename vtype> constexpr size_t hashtable <ktype, vtype> :: settings :: expand_threshold;
    template <typename ktype, typename vtype> constexpr size_t hashtable <ktype, vtype> :: settings :: contract_threshold;

    // Constructors

    template <typename ktype, typename vtype> hashtable <ktype, vtype> :: hashtable() : _entries(utils :: pnew <optional <entry>> :: uniform [settings :: base_alloc] (null)), _size(0), _alloc(settings :: base_alloc)
    {
    }

    // Destructor

    template <typename ktype, typename vtype> hashtable <ktype, vtype> :: ~hashtable()
    {
        utils :: pdelete(this->_entries, this->_alloc);
    }

    // Methods

    template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: add(const ktype & key, const vtype & value)
    {
        if(this->_alloc / (this->_size + 1) < settings :: expand_threshold)
            this->realloc(this->_alloc * 2);

        size_t index = hash(key) % this->_alloc;

        while(this->_entries[index])
            index = (index + 1) % this->_alloc;

        this->_entries[index] = entry{.key = key, .value = value};
        this->_size++;
    }

    template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: remove(const ktype & key)
    {
        optional <size_t> si = this->slot(key);
        if(!si)
            return;

        size_t i = *si;

        if(this->_alloc / (this->_size + 1) > settings :: contract_threshold && this->_alloc > settings :: base_alloc)
        {
            this->_entries[i] = null;
            this->realloc(this->_alloc / 2);
        }
        else
        {
            size_t j = i;
            size_t k;

            while(true)
            {
                this->_entries[i] = null;

                do
                {
                    j = (j + 1) % this->_alloc;

                    if(!(this->_entries[j]))
                        goto end;

                    k = hash(this->_entries[j]->key) % this->_alloc;
                } while((i <= j) ? ((i < k) && (k <= j)) : ((i < k) || (k <= j)));

                this->_entries[i] = this->_entries[j];
                i = j;
            }

            end:;
            this->_size--;
        }
    }

    template <typename ktype, typename vtype> template <typename lambda, std :: enable_if_t <utils :: is_callable <lambda, const ktype &, const vtype &> :: value> *> void hashtable <ktype, vtype> :: each(const lambda & callback)
    {
        for(size_t i = 0; i < this->_alloc; i++)
            if(this->_entries[i])
                callback(this->_entries[i]->key, this->_entries[i]->value);
    }

    // Private methods

    template <typename ktype, typename vtype> optional <size_t> hashtable <ktype, vtype> :: slot(const ktype & key) const
    {
        for(size_t index = hash(key) % this->_alloc;; index = (index + 1) % this->_alloc)
        {
            if(!(this->_entries[index]))
                return null;

            if(this->_entries[index]->key == key)
                return index;
        }
    }

    template <typename ktype, typename vtype> void hashtable <ktype, vtype> :: realloc(const size_t & alloc)
    {
        optional <entry> * old = this->_entries;

        size_t old_alloc = this->_alloc;
        this->_alloc = alloc;

        this->_size = 0;
        this->_entries = utils :: pnew <optional <entry>> :: uniform [this->_alloc] (null);

        for(size_t i = 0; i < old_alloc; i++)
            if(old[i])
                this->add(old[i]->key, old[i]->value);

        utils :: pdelete(old, old_alloc);
    }

    // Operators

    template <typename ktype, typename vtype> optional <vtype> hashtable <ktype, vtype> :: operator [] (const ktype & key) const
    {
        optional <size_t> si = this->slot(key);
        if(!si)
            return null;

        return this->_entries[*si]->value;
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

    template <typename ktype, typename vtype> size_t hashtable <ktype, vtype> :: hash(const bytewise :: buffer & key)
    {
        return (size_t) PMurHash32(0, key, key.size());
    }
};

#endif
