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
        this->_write.buffer.data = buffer;
        this->_write.ssize = bytewise :: bsize(buffer.size()).write(this->_write.buffer.size);
        this->_write.cursor = 0;
    }

    connection :: step connection :: arc :: send_step()
    {
        step status;

        this->_socket.visit([&](auto && socket)
        {
            if(this->_write.ssize)
            {
                socket.send(this->_write.buffer.size, this->_write.ssize);
                this->_write.ssize = 0;

                status = more;
            }
            else
            {
                size_t sent = socket.send((char *) (this->_write.buffer.data) + this->_write.cursor, this->_write.buffer.data.size() - this->_write.cursor);
                this->_write.cursor += sent;

                status = ((this->_write.cursor == this->_write.buffer.data.size()) ? completed : (sent ? more : wait));
            }
        });

        return status;
    }

    void connection :: arc :: receive_setup(const size_t & size)
    {
        this->_read.size = size;
        this->_read.cursor = 0;

        if(this->_read.size)
            this->_read.buffer.data.alloc(this->_read.size);
    }

    connection :: step connection :: arc :: receive_step()
    {
        step status;

        this->_socket.visit([&](auto && socket)
        {
            if(!(this->_read.size))
            {
                size_t received = socket.receive((char *) (this->_read.buffer.size) + (this->_read.cursor)++, 1);
                bytewise :: bsize bsize(this->_read.buffer.size, this->_read.cursor);

                if(bsize.value() > -1)
                    this->receive_setup(bsize.value());

                status = (received ? more : wait);
            }
            else
            {
                size_t received = socket.receive((char *) (this->_read.buffer.data) + this->_read.cursor, this->_read.size - this->_read.cursor);
                this->_read.cursor += received;

                status = ((this->_read.cursor == this->_read.size) ? completed : (received ? more : wait));
            }
        });

        return status;
    }
}
