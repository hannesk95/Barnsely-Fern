#ifndef HA1_PRODUCER_H
#define HA1_PRODUCER_H

#include <iostream>
#include <condition_variable>
#include "Buffer.h"
#include "Worker.h"

/// Class which takes care of filling the buffer with elements.
/// \tparam T - template class
template<typename T> class Producer : public Worker
{
private:
    Buffer<T>& m_buffer;    // Member variable which is used to store data points by Producer objects

public:
    /// Constructor of Producer class.
    /// \param buffer - Reference to Buffer object, which will be used to push data points into and store.
    Producer(Buffer<T>& buffer) : Worker(), m_buffer(buffer)
    {
        // Empty constructor.
    };

    /// Destructor of Producer class.
    ~Producer()
    {
        // Empty destructor.
    };

    /// Implementation of virtual method "step" of parent Worker class.
    /// Method invokes "produce" in order to create data point and store produced data point in buffer object.
    /// \return True - if job is done, False - otherwise.
    bool step() override
    {
        T element;
        bool terminate = false;

        while(!terminate)
        {
            // 1. Create new datapoint
            terminate = produce(element);

            // 2. Push datapoint into buffer
            m_buffer.push(element);
        }
        return terminate;
    }

protected:
    /// Virtual method which has to be implemented in child class GenuineProducer
    /// \param element - takes reference to element of datatype T (template) as input.
    /// \return True - if job is done, False - otherwise.
    virtual bool produce(T& element)
    { return 0; }  // Without return 0 compiler gives warning.
};

#endif //HA1_PRODUCER_H