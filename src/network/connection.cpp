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

    // Private methods

    void connection :: arc :: send_setup(const bytewise :: buffer & buffer)
    {
        this->_write.buffer.alloc(buffer.size() + sizeof(uint32_t));

        size_t ssize = bytewise :: bsize(buffer.size()).write(this->_write.buffer);
        memcpy((char *) (this->_write.buffer) + ssize, buffer, buffer.size());

        this->_write.buffer.alloc(buffer.size() + ssize);
        this->_write.cursor = 0;
    }

    bool connection :: arc :: send_step()
    {
        bool completed;

        this->_socket.visit([&](auto && socket)
        {
            this->_write.cursor += socket.send((char *) (this->_write.buffer) + this->_write.cursor, this->_write.buffer.size() - this->_write.cursor);
            completed = (this->_write.cursor == this->_write.buffer.size());
        });

        return completed;
    }

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
                this->_read.cursor += socket.receive((char *) (this->_read.buffer.data) + this->_read.cursor, this->_read.size - this->_read.cursor);
                completed = (this->_read.cursor == this->_read.size);
            }
        });

        return completed;
    }
}
