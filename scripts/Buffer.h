#ifndef HA1_BUFFER_H
#define HA1_BUFFER_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "GenuineConsumer.h"

/// Class which acts as the central data storage for Consumer and Producer objects.
/// \tparam T - template class
template<typename T> class Buffer
{
private:
    std::mutex mutex;               // Member variable mutex to manage buffer access
    std::unique_ptr<T[]> buffer;    // Member variable which is a pointer for elements in buffer
    size_t head = 0;                // Member variable which indicates the head of the buffer
    size_t tail = 0;                // Member variable which indicates the tail of the buffer
    const size_t max_size;          // Member variable which indicates the max size of the buffer object
    bool full = false;              // Member variable which indicates whether the buffer is full or not
    std::condition_variable hasCapacity, hasData;  // Member variables to handle race condition

public:
    /// Constructor of Buffer class.
    /// \param size - Element indicates the maximum size of the Buffer object.
    Buffer(size_t size) : buffer(std::unique_ptr<T[]>(new T[size])), max_size(size)
    {
        // Empty constructor.
    };

    /// Destructor of Buffer class.
    ~Buffer()
    {
        // Empty destructor.
    };

    /// Method which actually "pushes" one element of datatype T into the buffer.
    /// \param element - Reference to element of datatype T.
    void push_item(T& element)
    {
        buffer[head] = element;

        if(full)
        {
            tail = (tail + 1) % max_size;
        }

        head = (head + 1) % max_size;

        full = head == tail;
    }


    /// Method which starts push process.
    /// Method checks whether buffer is full or not. If full, current thread have to wait.
    /// \param element - Reference to element of datatype T, which is pushed into the buffer.
    void push(T& element)
    {
        // Unique lock is necessary as condition variable is used.
        std::unique_lock<std::mutex> lock(mutex);

        // Lambda function which checks whether buffer is full.
        hasCapacity.wait(lock, [this]
        {
            if(this->is_full())
            {
                return false;
            }
            else
            {
                return true;
            }
        });

        // Actual push element into buffer pipeline
        push_item(element);

        // Send notification update
        hasData.notify_one();
    };

    /// Method which actually "pop's" one element of datatype T from the buffer.
    /// \param element - Reference to element of datatype T.
    void pop_item(T& element)
    {
        element = buffer[tail];
        full = false;
        tail = (tail + 1) % max_size;
    };

    /// Method which starts pop process.
    /// Method checks for timeout. In case buffer is empty, throw runtime_error which will be catched in
    /// step method of class Consumer.
    /// \param element - Reference to element of datatype T, which is popped from the buffer.
    void pop(T& element)
    {
        // Unique lock is necessary as condition variable is used
        std::unique_lock<std::mutex> lock(mutex);

        if(!hasData.wait_for(lock, std::chrono::seconds(1), [this] { if(this->is_empty()) return false; else return true;}))
        {
            throw std::runtime_error("No more items in the buffer!");
        }

        // Actual pop element from buffer pipeline
        pop_item(element);

        // Send notification update
        hasCapacity.notify_one();
    };

    /// Method which gives information about the status of the Buffer.
    /// \return - True, if buffer is empty. False, otherwise.
    bool is_empty() const
    {
        //If head and tail are equal, the buffer is empty.
        return (!full && (head == tail));
    };

    /// Method which gives information about the status of the Buffer.
    /// \return True, if buffer is full. False, otherwise.
    bool is_full() const
    {
        //If tail is ahead the head by 1, the buffer is full.
        return full;
    };
};

#endif //HA1_BUFFER_H