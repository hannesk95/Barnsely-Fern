#ifndef HA1_WORKER_H
#define HA1_WORKER_H

#include <iostream>
#include <thread>
#include <vector>
#include <pthread.h>
#include <atomic>

class Worker
{
private:
    std::thread m_thread;
    bool m_terminate;
    bool m_running;


    int work()
    {
        while(true)
        {
            //this->m_terminate = step();
            if(stop(step()))
                break;
        }
        return 0;
    };


public:

    Worker()
    {
        //this->m_thread = std::thread([this] { this->work(); });
        this->m_terminate =false;
        this->m_running = false;
    };

//    ~Worker()
//    {
//        std::cout << "Worker object deleted!" << std::endl;
//    };

    void start_work()
    {
        if(this->m_running)
            std::cout << "Thread can't be started twice!" << std::endl;
        else
        {
            std::cout << "Start thread..." << std::endl;
            //this->m_running = true;
            this->m_thread = std::thread([this] { this->work(); });
            //this->m_thread = std::thread(&Worker::work, Worker());
            //this->m_thread.join();

        }
    };

    void join_thread()
    {
        this->m_running = true;
        this->m_thread.join();
    }

    bool stop(bool terminate)
    {
        if(terminate)
        {
            return true;
        }

        else
        {
            std::cout << "Waiting for the thread to be finished..." << std::endl;
            return false;
        }

    };

protected:
    virtual bool step()
    {  return 0; };

};

#endif //HA1_WORKER_H

