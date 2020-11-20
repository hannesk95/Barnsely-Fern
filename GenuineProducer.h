#ifndef HA1_GENUINEPRODUCER_H
#define HA1_GENUINEPRODUCER_H

#endif //HA1_GENUINEPRODUCER_H

#include <iostream>
#include <random>
#include "Producer.h"


//class GenuineProducer : public Producer<std::pair<float,float>>
class GenuineProducer : public Producer<std::pair<float, float>>
{

private:
    float x, y; // Initial points
    float a, b, c, d, e, f;
    int counter;
    bool terminate;
    int max_iterations;

public:
    //GenuineProducer(Buffer<std::pair<float, float>>& buffer) : Producer<std::pair<float, float>>(buffer)
    //Producer(Buffer<T>& buffer) : Worker(), m_buffer(buffer);
    GenuineProducer(Buffer<std::pair<float, float>>& buffer) : Producer<std::pair<float, float>>(buffer)
    {
        //std::cout << "Genuine Producer Object created!" << std::endl;

        this->x = 0;
        this->y = 0;
        this->counter = 0;
        this->terminate = false;
        this->max_iterations = 100000000;
    }

    ~GenuineProducer()
    {
        std::cout << "Genuine Producer Object deleted!" << std::endl;
    };

    bool produce(std::pair<float, float>& coordinate) override
    {
        int r = 0;
        float x_temp = 0;
        float y_temp = 0;
        std::uniform_int_distribution<int> d(0, 100);
        std::random_device rd;
        r = d(rd);

        if (r < 1)
        {
            x_temp = 0;
            y_temp = 0.16 * this->y;
        }

        else if (r < 86)
        {
            x_temp = 0.85 * this->x + 0.04 * this->y;
            y_temp = -0.04 * this->x + 0.85 * this->y + 1.6;
        }

        else if (r < 93)
        {
            x_temp = 0.20 * this->x - 0.26 * this->y;
            y_temp = 0.23 * this->x + 0.22 * this->y + 1.6;
        }

        else
        {
            x_temp = -0.15 * this->x + 0.28 * this->y;
            y_temp = 0.26 * this->x + 0.24 * this->y + 0.44;
        }

        coordinate.first = x_temp;
        coordinate.second = y_temp;

        this->x = x_temp;
        this->y = y_temp;

        this->counter++;
        if( this->counter == this->max_iterations)
            this->terminate = true;

        return this->terminate;
    }


};



