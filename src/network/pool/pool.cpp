// Includes

#include "pool.hpp"

namespace network
{
    // arc

    // Constructors

    pool :: connection :: arc :: arc(pool & pool, const :: network :: connection & connection) : _pool(pool), _connection(connection._arc)
    {
        this->_connection->_mutex.send.lock();
        this->_connection->_mutex.receive.lock();

        this->_connection->_locked = true;
        this->_connection->block(false);

        this->_connection->_mutex.send.unlock();
        this->_connection->_mutex.receive.unlock();
    }

    // Destructor

    pool :: connection :: arc :: ~arc()
    {
        this->_connection->_mutex.send.lock();
        this->_connection->_mutex.receive.lock();

        this->_connection->_locked = false;
        this->_connection->block(true);

        this->_connection->_mutex.send.unlock();
        this->_connection->_mutex.receive.unlock();
    }

    // connection

    // Private constructors

    pool :: connection :: connection(pool & pool, const :: network :: connection & connection) : _arc(new arc(pool, connection))
    {
    }

    // pool

    // Constructors

    pool :: pool() : _alive(true)
    {
        int wake[2];
        pipe(wake);

        this->_wake.read = wake[0];
        this->_wake.write = wake[1];

        fcntl(this->_wake.read, F_SETFL, O_NONBLOCK);
        this->_queue.add <queue :: read> (this->_wake.read);

        this->_thread = std :: thread(&pool :: run, this);
    }

    // Destructors

    pool :: ~pool()
    {
        this->_alive = false;
        this->wake();
        this->_thread.join();

        close(this->_wake.read);
        close(this->_wake.write);
    }

    // Methods

    pool :: connection pool :: bind(const :: network :: connection & connection)
    {
        return {*this, connection};
    }

    // Private methods

    void pool :: run()
    {
        while(true)
        {
            this->_awake = false;
            size_t count = this->_queue.select(settings :: interval);
            this->_awake = true;

            if(!(this->_alive))
                break;

            for(size_t i = 0; i < count; i++)
            {
                if(this->_queue[i].descriptor() == this->_wake.read)
                {
                    char buffer[1];
                    while(read(this->_wake.read, buffer, 1) >= 0);

                    continue;
                }

                data :: optional <data :: variant <request :: connection, request :: dispatcher>> request = this->_pending[this->_queue[i].descriptor()];
                assert(request);

                request->visit([&](request :: connection & request)
                {
                    try
                    {
                        queue :: type type = this->_queue[i].type();
                        :: network :: connection :: step status;

                        while((status = (type == queue :: read ? request.connection._arc->_connection->receive_step() : request.connection._arc->_connection->send_step())) == :: network :: connection :: more);

                        if(status == :: network :: connection :: wait)
                            return;

                        request.promise.resolve();
                    }
                    catch(...)
                    {
                        request.promise.reject(std :: current_exception());
                    }

                    this->_pending.remove(this->_queue[i].descriptor());

                    if(this->_queue[i].type() == queue :: read)
                        this->_queue.remove <queue :: read> (this->_queue[i].descriptor());
                    else
                        this->_queue.remove <queue :: write> (this->_queue[i].descriptor());
                }, [&](request :: dispatcher & request)
                {
                    if(this->_queue[i].type() == queue :: read)
                    {
                        this->_queue.remove <queue :: read> (this->_queue[i].descriptor());
                    }
                    else
                    {
                        request.resolve();
                        this->_queue.remove <queue :: write> (this->_queue[i].descriptor());
                    }
                });
            }

            while(data :: optional <timeout> timeout = this->_timeouts.pop())
            {
                data :: optional <data :: variant <request :: connection, request :: dispatcher>> request = this->_pending[timeout->descriptor];

                if(request)
                {
                    request->visit([&](request :: connection & request)
                    {
                        if(request.version == timeout->version)
                        {
                            this->_pending.remove(timeout->descriptor);

                            if(request.type == queue :: read)
                            {
                                this->_queue.remove <queue :: read> (timeout->descriptor);
                                request.promise.reject(sockets :: receive_timeout());
                            }
                            else
                            {
                                this->_queue.remove <queue :: write> (timeout->descriptor);
                                request.promise.reject(sockets :: send_timeout());
                            }
                        }
                    }, [&](request :: dispatcher & request)
                    {
                        if(request.version == timeout->version)
                        {
                            this->_pending.remove(timeout->descriptor);

                            if(request.type == queue :: read)
                            {
                                this->_queue.remove <queue :: read> (timeout->descriptor);
                                request.reject(std :: make_exception_ptr(sockets :: receive_timeout()));
                            }
                            else
                            {
                                this->_queue.remove <queue :: write> (timeout->descriptor);
                                request.reject(std :: make_exception_ptr(sockets :: send_timeout()));
                            }
                        }
                    });
                }
            }

            while(data :: optional <data :: variant <request :: connection, request :: dispatcher>> request = this->_new.pop())
            {
                request->visit([&](request :: connection & request)
                {
                    if(request.type == queue :: read)
                        this->_queue.add <queue :: read> (request.connection._arc->_connection->descriptor());
                    else
                        this->_queue.add <queue :: write> (request.connection._arc->_connection->descriptor());

                    request.version = version++;
                    this->_pending.add(request.connection._arc->_connection->descriptor(), data :: variant <request :: connection, request :: dispatcher> :: construct <request :: connection> (request));
                    this->_timeouts.push({.descriptor = request.connection._arc->_connection->descriptor(), .version = request.version}, microtime() + settings :: timeout);
                }, [&](request :: dispatcher & request)
                {
                    if(request.type == queue :: read)
                        this->_queue.add <queue :: read> (request.descriptor);
                    else
                        this->_queue.add <queue :: write> (request.descriptor);

                    request.version = version++;
                    this->_pending.add(request.descriptor, data :: variant <request :: connection, request :: dispatcher> :: construct <request :: dispatcher> (request));
                    this->_timeouts.push({.descriptor = request.descriptor, .version = request.version}, microtime() + settings :: timeout);
                });
            }
        }
    }

    void pool :: wake()
    {
        if(!(this->_awake))
        {
            char buffer[] = {'\0'};
            write(this->_wake.write, buffer, 1);
        }
    }

    // Static members

    size_t pool :: version = 0;
};
