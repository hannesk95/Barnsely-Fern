#ifndef HA1_CONSUMER_H
#define HA1_CONSUMER_H

#include <iostream>
#include "Worker.h"
#include "Buffer.h"

template<typename T> class Consumer : public Worker
{
private:
    Buffer<T>& m_buffer;

public:

    Consumer(Buffer<T>& buffer) : Worker(), m_buffer(buffer)
    {
        std::cout << "Consumer object created!" << std::endl;

        //this->m_buffer = buffer;
    };

    bool step() override
    {
        T element;
        bool terminate;

        while(!terminate)
        {
            try
            {
                //std::cout << "Pop element from buffer..." << std::endl;
                element = m_buffer.pop();
                terminate = consume(element);
                //std::cout << "Current elements in buffer: " << m_buffer.size() << std::endl;
            }
            catch (const std::runtime_error& error)
            {
                terminate = true;
            }
        }

        return terminate;
    }

protected:
    virtual bool consume(T& element)
    { return 0; };
};

#endif //HA1_CONSUMER_H