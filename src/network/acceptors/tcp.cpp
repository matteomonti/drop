// Includes

#include "tcp.hpp"

namespace network :: acceptors
{
    // sync

    // Constructors

    tcp :: sync :: sync(const uint16_t & port)
    {
        this->_socket.bind(port);
        this->_socket.listen();
    }

    // Methods

    connection tcp :: sync :: accept()
    {
        return connection(this->_socket.accept());
    }

    // async

    // Constructors

    tcp :: async :: async(const uint16_t & port) : _acceptor(port), _port(port), _alive(true)
    {
        this->_thread = std :: thread(&async :: run, this);
    }

    // Destructor

    tcp :: async :: ~async()
    {
        this->_alive = false;
        this->wake();
        this->_thread.join();

        this->clear();
    }

    // Methods

    void tcp :: async :: clear()
    {
        this->_mutex.lock();

        for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
            this->_callbacks[i].reset();

        this->_mutex.unlock();
    }

    // Private methods

    void tcp :: async :: run()
    {
        while(true)
        {
            connection connection = this->_acceptor.accept();

            if(!(this->_alive))
                break;

            for(size_t i = 0; i < settings :: callbacks && this->_callbacks[i]; i++)
                this->_callbacks[i](connection);
        }
    }

    void tcp :: async :: wake()
    {
        try
        {
            connectors :: tcp :: sync :: connect({"127.0.0.1", this->_port});
        }
        catch(...)
        {
        }
    }
};
