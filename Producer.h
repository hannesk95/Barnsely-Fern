#ifndef HA1_PRODUCER_H
#define HA1_PRODUCER_H

#include <iostream>
#include <condition_variable>

#include "Buffer.h"
#include "Worker.h"

template<typename T> class Producer : public Worker
{
private:
    Buffer<T>& m_buffer;

public:
    Producer(Buffer<T>& buffer) : Worker(), m_buffer(buffer)
    {
        std::cout << "Producer object created!" << std::endl;
        //this->m_buffer = buffer;
    };

    ~Producer()
    {
        std::cout << "Producer object deleted!" << std::endl;
    };

    bool step() override
    {
       T element;
       bool terminate = false;

        //for (int n=0; n<100000; n++)
        while(!terminate)
        {
            // 1. Create new datapoint
            terminate = produce(element);

            // 2. Push datapoint into buffer if free capacity is left
            // otherwise block current thread
            std::cout << "Push new element into buffer..." << std::endl;
            m_buffer.push(element);
            std::cout << "Current elements in buffer: " << m_buffer.size() << std::endl;
        }
        return terminate;
    }

protected:
    virtual bool produce(T& element)
    { return 0; };
};

#endif //HA1_PRODUCER_H