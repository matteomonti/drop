// Includes

#include "tcp.h"

namespace network :: connectors
{
    // sync

    // Static methods

    connection tcp :: sync :: connect(const address & remote)
    {
        sockets :: tcp socket;
        socket.connect(remote);
        return connection(socket);
    }

    // async

    promise <connection> tcp :: async :: connect(const address & remote)
    {
        request request;
        request.socket.block(false);
        try
        {
            request.socket.connect(remote);
            this->_new.push(request);
            this->wake();
        }
        catch(...)
        {
            request.promise.reject(std :: current_exception());
        }

        return request.promise;
    }

    // Constructors

    tcp :: async :: async() : _alive(true)
    {
        int wake[2];
        pipe(wake);

        this->_wake.read = wake[0];
        this->_wake.write = wake[1];

        this->_queue.add <queue :: read> (this->_wake.read);

        this->_thread = std :: thread(&async :: run, this);
    }

    // Destructor

    tcp :: async :: ~async()
    {
        this->_alive = false;
        this->wake();
        this->_thread.join();

        close(this->_wake.read);
        close(this->_wake.write);
    }

    // Private methods

    void tcp :: async :: run()
    {
        while(true)
        {
            size_t count = this->_queue.select();

            if(!(this->_alive))
                break;

            for(size_t i = 0; i < count; i++)
            {
                if(this->_queue[i].type() == queue :: read)
                {
                    std :: cout << "Wake" << std :: endl;

                    char buffer[1];
                    read(this->_wake.read, buffer, 1);
                }
                else
                {
                    data :: optional <request> request = this->_pending[this->_queue[i].descriptor()];
                    assert(request);

                    this->_pending.remove(this->_queue[i].descriptor());
                    this->_queue.remove <queue :: write> (this->_queue[i].descriptor());

                    request->promise.resolve(connection(request->socket));
                }
            }

            while(data :: optional <request> request = this->_new.pop())
            {
                std :: cout << "Adding " << request->socket.descriptor() << std :: endl;
                this->_queue.add <queue :: write> (request->socket.descriptor());
                this->_pending.add(request->socket.descriptor(), *request);
            }
        }
    }

    void tcp :: async :: wake()
    {
        char buffer[] = {'\0'};
        write(this->_wake.write, buffer, 1);
    }
};
