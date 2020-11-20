#ifndef HA1_BUFFER_H
#define HA1_BUFFER_H

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "GenuineConsumer.h"

template<typename T> class Buffer
{
private:
    std::mutex a_mutex;
    std::unique_ptr<T[]> buffer;
    size_t head = 0;
    size_t tail = 0;
    const size_t max_size;
    bool full = false;
    std::condition_variable hasCapacity, hasData;

public:

    Buffer(size_t size) : buffer(std::unique_ptr<T[]>(new T[size])), max_size(size)
    {
        std::cout << "Buffer object with size " << size << " created!" << std::endl;
    };

    ~Buffer()
    {
        std::cout << "Buffer object deleted!" << std::endl;
    };


    void push_item(T& element)
    {
        // std::lock_guard<std::mutex> lock(a_mutex);

        buffer[head] = element;

        if(full)
        {
            tail = (tail + 1) % max_size;
        }

        head = (head + 1) % max_size;

        full = head == tail;
    }

    /*
     *
     */
    void push(T& element)
    {
        std::unique_lock<std::mutex> lock(a_mutex);

        // Lambda function which checks whether buffer is full
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

        // Notify all other threads
        hasData.notify_one();
    };

    /*
     *
     */
    T pop_item()
    {
        //std::lock_guard<std::mutex> lock(a_mutex);

        if(is_empty())
        {
            return T();
        }

        //Read data and advance the tail (we now have a free space)
        auto val = buffer[tail];
        full = false;
        tail = (tail + 1) % max_size;

        return val;
    };

    T pop()
    {
        T element;
        std::unique_lock<std::mutex> lock(a_mutex);

        // Lambda function which checks whether buffer still has elements
        if(!hasData.wait_for(lock, std::chrono::seconds(1), [this] { if(this->is_empty()) return false; else return true;}))
        {
            throw std::runtime_error("No more items in the buffer!");
        }

        // Actual pop element from buffer pipeline
        element = pop_item();

        // Notify all other threads
        hasCapacity.notify_one();

        return element;

        // Error handling
//        try
//        {
//            if (badThingHappened)
//            {
//                throw std::runtime_error("Something Bad happened here");
//            }
//        }
//        catch(std::exception const& e)
//        {
//            std::cout << "Exception: " << e.what() << "\n";
//        }
    };

    void reset()
    {
        std::lock_guard<std::mutex> lock(a_mutex);
        head = tail;
        full = false;
    };

    bool is_empty() const
    {
        //if head and tail are equal, the buffer is empty
        return (!full && (head == tail));
    };

    bool is_full() const
    {
        //If tail is ahead the head by 1, we are full
        return full;
    };
    size_t capacity() const
    {
        return max_size;
    };

    size_t size() const
    {
        size_t size = max_size;

        if(!full)
        {
            if(head >= tail)
            {
                size = head - tail;
            }
            else
            {
                size = max_size + head - tail;
            }
        }
        return size;
    };

};

#endif //HA1_BUFFER_H