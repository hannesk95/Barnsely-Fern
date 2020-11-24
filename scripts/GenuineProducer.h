#ifndef HA1_GENUINEPRODUCER_H
#define HA1_GENUINEPRODUCER_H

#include <iostream>
#include <random>
#include "Producer.h"

/// Class which actually produces the data points of the Barnsely fern.
class GenuineProducer : public Producer<std::pair<float, float>>
{

private:
    float x, y;                 // Initial points
    int counter;                // Member variable which counts number of iterations
    bool terminate;             // Member variable which indicates whether work is done or not
    int max_iterations;         // Member variable which defines number of iterations
    std::random_device rd;      // Member variable for generating random numbers

public:
    /// Constructor of GenuineProducer class.
    /// \param buffer - Reference to Buffer object, in order to be able to invoke inherited constructor.
    /// \param iter - Reference which indicates maximum number of iterations.
    GenuineProducer(Buffer<std::pair<float, float>>& buffer, int iteration) : Producer<std::pair<float, float>>(buffer)
    {
        this->x = 0;
        this->y = 0;
        this->counter = 0;
        this->terminate = false;
        this->max_iterations = iteration;
    }

    /// Destructor of GenuineProducer class.
    ~GenuineProducer()
    {
        // Empty destructor.
    }

    /// Implementation of virtual method "produce" of parent Producer class.
    /// Method calculates actual fern x & y datapoints according to four different functions.
    /// Which of the functions is selected is due to "rolling a dice" (i.e. random number).
    /// \param coordinate - is the unit (i.e. pair) in which the two objects (x & y value) are stored in.
    /// \return True - if work is done (i.e. counter equals iterations), False - otherwise.
    bool produce(std::pair<float, float>& coordinate) override
    {
        int r = 0;
        float x_temp = 0;
        float y_temp = 0;

        // Create random integer number between 0 and 100
        std::uniform_int_distribution<int> d(0, 100);
        r = d(this->rd);

        // Case 1
        if (r < 1)
        {
            x_temp = 0;
            y_temp = 0.16 * this->y;
        }

        // Case 2
        else if (r < 86)
        {
            x_temp = 0.85 * this->x + 0.04 * this->y;
            y_temp = -0.04 * this->x + 0.85 * this->y + 1.6;
        }

        // Case 3
        else if (r < 93)
        {
            x_temp = 0.20 * this->x - 0.26 * this->y;
            y_temp = 0.23 * this->x + 0.22 * this->y + 1.6;
        }

        // Case 4
        else
        {
            x_temp = -0.15 * this->x + 0.28 * this->y;
            y_temp = 0.26 * this->x + 0.24 * this->y + 0.44;
        }

        // Save calculated data point
        coordinate.first = x_temp;
        coordinate.second = y_temp;

        // Save current calculated data point as starting point for next iteration
        this->x = x_temp;
        this->y = y_temp;

        // Increment counter and check whether job is done
        this->counter++;
        if( this->counter == this->max_iterations)
            this->terminate = true;

        return this->terminate;
    }
};

#endif //HA1_GENUINEPRODUCER_H



