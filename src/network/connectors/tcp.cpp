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

    // Settings

    constexpr microtimestamp tcp :: async :: settings :: timeout;
    constexpr microtimestamp tcp :: async :: settings :: interval;

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

    // Methods

    promise <connection> tcp :: async :: connect(const address & remote)
    {
        request request;
        request.socket.block(false);

        this->_mutex.lock();

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

        this->_mutex.unlock();
        return request.promise;
    }

    // Private methods

    void tcp :: async :: run()
    {
        while(true)
        {
            size_t count = this->_queue.select(settings :: interval);

            if(!(this->_alive))
                break;

            for(size_t i = 0; i < count; i++)
            {
                if(this->_queue[i].type() == queue :: read)
                {
                    char buffer[1];
                    read(this->_wake.read, buffer, 1);
                }
                else
                {
                    data :: optional <request> request = this->_pending[this->_queue[i].descriptor()];
                    assert(request);

                    this->_pending.remove(this->_queue[i].descriptor());
                    this->_queue.remove <queue :: write> (this->_queue[i].descriptor());

                    try
                    {
                        request->socket.rethrow();
                        request->promise.resolve(connection(request->socket));
                    }
                    catch(...)
                    {
                        request->promise.reject(std :: current_exception());
                    }
                }
            }

            while(data :: optional <timeout> timeout = this->_timeouts.pop())
            {
                data :: optional <request> request = this->_pending[timeout->descriptor];

                if(request && request->version == timeout->version)
                {
                    this->_pending.remove(timeout->descriptor);
                    this->_queue.remove <queue :: write> (timeout->descriptor);

                    request->socket.close();
                    request->promise.reject(sockets :: connect_timeout());
                }
            }

            while(data :: optional <request> request = this->_new.pop())
            {
                this->_queue.add <queue :: write> (request->socket.descriptor());

                request->version = version++;
                this->_pending.add(request->socket.descriptor(), *request);
                this->_timeouts.push({.descriptor = request->socket.descriptor(), .version = request->version}, microtime() + settings :: timeout);
            }
        }
    }

    void tcp :: async :: wake()
    {
        char buffer[] = {'\0'};
        write(this->_wake.write, buffer, 1);
    }

    // Static members

    size_t tcp :: async :: version = 0;
};
