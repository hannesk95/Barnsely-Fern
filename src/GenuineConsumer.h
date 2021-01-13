#ifndef HA1_GENUINECONSUMER_H
#define HA1_GENUINECONSUMER_H

#include <iostream>
#include <string>
#include <cmath>
#include <mutex>
#include <vector>
#include "Consumer.h"

#define cimg_display 0
#include "CImg.h"

#define X_DIM 10000
#define Y_DIM 20000
#define X_MIN (-2.2)
#define X_MAX (2.7)
#define Y_MIN (0)
#define Y_MAX (10)

/// Class which converts data points into pixel values and draws the image.
class GenuineConsumer : public Consumer<std::pair<float, float>>
{
private:

    static cimg_library::CImg<unsigned char> fractal;   // Member variable which serves as image database.
    static int numConsumers;                            // Member variable which stores the active Consumer objects.
    static std::vector<std::mutex> vecMutex;            // Vector which includes mutexes for image access management.


public:
    /// Constructor of GenuineConsumer class.
    /// \param buffer - Reference to Buffer object, in order to be able to invoke inherited constructor.
    /// \param numConsumers - Reference which gives number of initial consumer objects.
    GenuineConsumer(Buffer<std::pair<float, float>>& buffer, int numConsumers) : Consumer<std::pair<float, float>>(buffer)
    {
        this->numConsumers = numConsumers;
    }

    /// Destructor of GenuineProducer class.
    /// Destructor checks number of active consumer objects. Last consumer object saves image.
    ~GenuineConsumer()
    {
        if(this->numConsumers == 1)
            fractal.save_png("fern_image.png");
        else
            this->numConsumers--;
    }

    /// Method converts x value of data point into x pixel value.
    /// \param xValue indicating the first value of float pair.
    /// \return x pixel value.
    void xPixel(float& xValue)
    {
        xValue = (xValue - X_MIN) * X_DIM / (X_MAX - X_MIN);
    }

    /// Method converts y value of data point into y pixel value.
    /// \param yValue xValue indicating the second value of float pair.
    /// \return y pixel value.
    void yPixel(float& yValue)
    {
        yValue = (yValue - Y_MIN) * Y_DIM / (Y_MAX - Y_MIN);
    }

    /// Implementation of virtual method "consume" of parent Consumer class.
    /// Method further processes data point pulled from buffer and assign corresponding pixel value of image.
    /// \param cooordinate - is the unit (i.e. pair) in which the two objects (x & y value) are stored in.
    /// \return False, as consumer can not decide whether thread has finished or not.
    bool consume(std::pair<float, float>& coordinate)
    {
        xPixel(coordinate.first);
        yPixel(coordinate.second);

        int xValue = ceil(coordinate.first);
        int yValue = ceil(coordinate.second);

        std::lock_guard<std::mutex> lock(this->vecMutex[xValue]);

        unsigned char *pixel_value = fractal.data((xValue), yValue, 0, 0);

        if ((*pixel_value) < 255)
            fractal(xValue, yValue, 0, 0) = (*pixel_value) + 1;

        return false;
    }

};

// Initialize static member variables
cimg_library::CImg<unsigned char> GenuineConsumer::fractal = cimg_library::CImg<unsigned char>(X_DIM, Y_DIM, 1, 1);
int GenuineConsumer::numConsumers = 0;
std::vector<std::mutex> GenuineConsumer::vecMutex(10000);

#endif //HA1_GENUINECONSUMER_H
