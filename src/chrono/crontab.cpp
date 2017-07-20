// Includes

#include "crontab.h"

namespace chrono
{
    // Constructors

    crontab :: crontab() : _alive(true)
    {
        this->_thread = std :: thread(&crontab :: run, this);
    }

    // Destructor

    crontab :: ~crontab()
    {
        this->_alive = false;
        this->_semaphore.post();
        this->_thread.join();
    }

    // Methods

    promise <void> crontab :: wait(const microtimestamp & timeout)
    {
        microtimestamp time = microtime() + timeout;
        promise <void> promise;

        this->_mutex.lock();

        data :: optional <microtimestamp> next = this->_timelock.next();
        this->_timelock.push(promise, time);

        bool wake = (!next || time < *next);

        this->_mutex.unlock();

        if(wake)
            this->_semaphore.post();

        return promise;
    }

    // Private methods

    void crontab :: run()
    {
        while(true)
        {
            microtimestamp now = microtime();

            this->_mutex.lock();
            data :: optional <microtimestamp> next = this->_timelock.next();
            this->_mutex.unlock();

            if(next)
            {
                if(*next > now)
                    this->_semaphore.wait(next - now);
            }
            else
                this->_semaphore.wait();

            if(!(this->_alive))
                return;

            this->_mutex.lock();

            while(data :: optional <promise <void>> promise = this->_timelock.pop())
                promise->resolve();

            this->_mutex.unlock();
        }
    }
};
