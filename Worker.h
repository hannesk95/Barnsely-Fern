#ifndef HA1_WORKER_H
#define HA1_WORKER_H

#include <iostream>
#include <thread>

/// Class which acts as the base class of all other classes except for Buffer class.
class Worker
{
private:
    std::thread m_thread;   // Member variable which stores the thread
    bool m_terminate;       // Member variable which holds information about termination of thread
    bool m_running;         // Member variable which indicates whether thread is running or not

    /// Method which starts the actual task of the thread and keeps working as long as m_terminate is false.
    void work()
    {
        while(true)
        {
            if(stop(step()))
                break;
        }
    }

public:
    /// Constructor of Worker class. Initialize member variables.
    Worker()
    {
        this->m_terminate = false;
        this->m_running = false;
    }

    /// Destructor of Worker class.
    ~Worker()
    {
        // Empty destructor.
    }

    /// Method which invokes "work" method in corresponding thread and toggle variable for thread status.
    void start_work()
    {
        if(this->m_running)
            std::cout << "Thread can't be started twice!" << std::endl;
        else
        {
            this->m_thread = std::thread([this] { this->work(); });
        }
    }

    /// Method which joins thread with the main thread.
    void join_thread()
    {
        this->m_running = true;
        this->m_thread.join();
    }

    /// Method which checks whether thread has to be terminated.
    /// \param terminate - parameter which is the return variable of the step method.
    /// \return True - if thread has to be terminated, False - otherwise.
    bool stop(bool terminate)
    {
        if(terminate)
            this->m_terminate = true;
        else
            this->m_terminate = false;

        return this->m_terminate;
    }

protected:
    /// Virtual method which has to be implemented by child classes Producer and Consumer.
    /// \return Gives information about whether to terminate the thread if task is done.
    virtual bool step()
    {  return 0; } // Without return 0 compiler gives warning.
};

#endif //HA1_WORKER_H

