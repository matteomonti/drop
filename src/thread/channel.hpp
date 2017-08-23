#ifndef __drop__thread__channel__hpp
#define __drop__thread__channel__hpp

// Includes

#include "channel.h"
#include "utils/misc/pnew.hpp"

namespace thread
{
    // chunk

    // Constructors

    template <typename type> channel <type> :: chunk :: chunk(const size_t & size) : _buffer(utils :: pnew <data :: optional <type>> :: uniform [size] (data :: null)), _size(size), _cursor{.write = 0, .read = 0}, _next(nullptr), _last(-1)
    {
    }

    // Destructors

    template <typename type> channel <type> :: chunk :: ~chunk()
    {
        utils :: pdelete(this->_buffer, this->_size);
    }

    // Methods

    template <typename type> void channel <type> :: chunk :: push(const type & item)
    {
        if(this->_cursor.write == this->_cursor.read + this->_size)
        {
            this->_next = new chunk(this->_size * 2);
            this->_last = this->_cursor.write;

            throw const_cast <chunk *> (this->_next);
        }

        this->_buffer[(this->_cursor.write++) % this->_size] = item;
    }

    template <typename type> data :: optional <type> channel <type> :: chunk :: pop()
    {
        if(this->_cursor.read == this->_last)
        {
            chunk * next = const_cast <chunk *> (this->_next);
            delete this;
            throw next;
        }

        if(this->_cursor.read < this->_cursor.write)
        {
            type value = *(this->_buffer[(this->_cursor.read) % this->_size]);
            this->_buffer[(this->_cursor.read++) % this->_size] = data :: null;

            return value;
        }
        else
            return data :: null;
    }

    // channel

    // Constructors

    template <typename type> channel <type> :: channel()
    {
        this->_read = this->_write = new chunk(settings :: base_chunk_alloc);
    }

    // Methods

    template <typename type> void channel <type> :: push(const type & item)
    {
        try
        {
            this->_write->push(item);
        }
        catch(chunk * next)
        {
            this->_write = next;
            this->_write->push(item);
        }
    }

    template <typename type> data :: optional <type> channel <type> :: pop()
    {
        try
        {
            return this->_read->pop();
        }
        catch(chunk * next)
        {
            this->_read = next;
            return this->_read->pop();
        }
    }
};

#endif
