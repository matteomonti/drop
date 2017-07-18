// Includes

#include "connection.h"

namespace network
{
    // arc

    // Destructor

    connection :: arc :: ~arc()
    {
        this->_socket.visit([](auto && socket)
        {
            socket.close();
        });
    }

    // Methods

    void connection :: arc :: send(const bytewise :: buffer & buffer)
    {
        this->_socket.visit([&](auto && socket)
        {
            char sbuffer[sizeof(uint32_t)];

            size_t ssize = bytewise :: bsize(buffer.size()).write(sbuffer);
            socket.send(sbuffer, ssize);
            socket.send(buffer, buffer.size());
        });
    }

    // Private methods

    void connection :: arc :: receive_setup(const size_t & size)
    {
        this->_read.size = size;
        this->_read.cursor = 0;

        if(this->_read.size)
            this->_read.buffer.data.alloc(this->_read.size);
    }

    bool connection :: arc :: receive_step()
    {
        bool completed;

        this->_socket.visit([&](auto && socket)
        {
            if(!(this->_read.size))
            {
                socket.receive((char *) (this->_read.buffer.size) + (this->_read.cursor)++, 1);
                bytewise :: bsize bsize(this->_read.buffer.size, this->_read.cursor);

                if(bsize.value() > -1)
                    this->receive_setup(bsize.value());

                completed = false;
            }
            else
            {
                this->_read.cursor += socket.receive((char * ) (this->_read.buffer.data) + this->_read.cursor, this->_read.size - this->_read.cursor);
                completed = (this->_read.cursor == this->_read.size);
            }
        });

        return completed;
    }
}
