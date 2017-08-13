// Includes

#include "buffer.h"

namespace bytewise
{
    // Constructors

    buffer :: buffer() : _size(0), _alloc(0)
    {
    }

    buffer :: buffer(const char * bytes, const size_t & size) : _bytes(new char [size + 1]), _size(size), _alloc(size)
    {
        memcpy(this->_bytes, bytes, size);
        this->_bytes[this->_alloc] = '\0';
    }

    buffer :: buffer(const char * bytes) : buffer(bytes, strlen(bytes))
    {
    }

    buffer :: buffer(char * bytes, const size_t & size, class reference) : _bytes(bytes), _size(size), _alloc(0)
    {
    }

    buffer :: buffer(const buffer & that) : buffer(that._bytes, that._size)
    {
    }

    buffer :: buffer(buffer && that) : _bytes(that._bytes), _size(that._size), _alloc(that._alloc)
    {
        that._alloc = 0;
    }

    // Destructor

    buffer :: ~buffer()
    {
        if(this->_alloc)
            delete [] this->_bytes;
    }

    // Getters

    const size_t & buffer :: size() const
    {
        return this->_size;
    }

    // Methods

    void buffer :: alloc(const size_t & size)
    {
        if(this->_alloc < size)
        {
            if(this->_alloc)
              delete [] this->_bytes;

            this->_alloc = size;
            this->_bytes = new char[this->_alloc + 1];
            this->_bytes[this->_alloc] = '\0';
        }

        this->_size = size;
    }

    // Operators

    char & buffer :: operator [] (const size_t & index)
    {
        return this->_bytes[index];
    }

    const char & buffer :: operator [] (const size_t & index) const
    {
        return this->_bytes[index];
    }

    buffer & buffer :: operator = (const buffer & that)
    {
        this->alloc(that._size);
        memcpy(this->_bytes, that._bytes, this->_size);

        return *this;
    }

    buffer & buffer :: operator = (buffer && that)
    {
        if(this->_alloc)
            delete [] this->_bytes;

        this->_size = that._size;
        this->_alloc = that._alloc;
        this->_bytes = that._bytes;

        that._alloc = 0;

        return *this;
    }

    // Casting

    buffer :: operator char * ()
    {
        return this->_bytes;
    }

    buffer :: operator const char * () const
    {
        return this->_bytes;
    }

    // Static members declarations

    class buffer :: reference buffer :: reference;
};
