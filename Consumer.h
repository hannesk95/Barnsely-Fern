#ifndef HA1_CONSUMER_H
#define HA1_CONSUMER_H

#include <iostream>
#include "Worker.h"
#include "Buffer.h"

/// Class which takes care of emptying the buffer elementwise.
/// \tparam T - template class
template<typename T> class Consumer : public Worker
{
private:
    Buffer<T>& m_buffer;    // Member variable which is used by Consumer objects to pull data points from

public:
    /// Constructor of Consumer class.
    /// \param buffer - Reference to Buffer object, which will be used to pull data points from.
    Consumer(Buffer<T>& buffer) : Worker(), m_buffer(buffer)
    {
        // Empty constructor.
    }

    /// Destructor of Consumer class.
    ~Consumer()
    {
        // Empty destructor.
    }

    /// Implementation of virtual method "step" of parent Worker class.
    /// Method pulls data point from buffer and invokes "consume" for further processing.
    /// \return False, as consumer can not decide whether thread has finished or not.
    bool step() override
    {
        T element;
        bool terminate;

        while(!terminate)
        {
            try
            {
                // 1. Pull datapoint from buffer
                m_buffer.pop(element);

                // 2. Process popped datapoint
                terminate = consume(element);
            }
            catch (const std::runtime_error& error)
            {
                terminate = true;
            }
        }

        return terminate;
    }

protected:
    /// Virtual method which has to be implemented in child class GenuineConsumer
    /// \param element - takes reference to element of datatype T (template) as input.
    /// \return False, as consumer can not decide whether thread has finished or not.
    virtual bool consume(T& element)
    { return 0; }  // Without return 0 compiler gives warning.
};

#endif //HA1_CONSUMER_H