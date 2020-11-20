#ifndef HA1_GENUINECONSUMER_H
#define HA1_GENUINECONSUMER_H

#include <iostream>
#include <string>
#include "Consumer.h"
#include <cmath>
#include <mutex>
#include <vector>

#define cimg_display 0
#include "CImg.h"

#define X_DIM 10000
#define Y_DIM 20000
#define X_MIN (-2.2)
#define X_MAX (2.7)
#define Y_MIN (0)
#define Y_MAX (10)

class GenuineConsumer : public Consumer<std::pair<float, float>>
{
private:

    static cimg_library::CImg<unsigned char> fractal;
    static int numConsumers;
    static bool saveImage;
    static std::vector<std::mutex> vecMutex;


public:
    GenuineConsumer(Buffer<std::pair<float, float>>& buffer, int numConsumers) : Consumer<std::pair<float, float>>(buffer)
    {
        //std::cout << "Genuine Consumer Object created!" << std::endl;
        this->numConsumers = numConsumers;
    }

    ~GenuineConsumer()
    {
        if(this->numConsumers == 1)
            fractal.save_png("fern_image.png");
        else
            this->numConsumers--;
    }

    float xPixel(float xValue)
    {
        return float(xValue - X_MIN) * X_DIM / (X_MAX - X_MIN);
    }

    float yPixel(float& yValue)
    {
        return float(yValue - Y_MIN) * Y_DIM / (Y_MAX - Y_MIN);
    }

    /**
     *
     * @param cooordinate
     * @return
     */
    bool consume(std::pair<float, float>& cooordinate)
    {
        int xValue = ceil(xPixel(cooordinate.first));
        int yValue = ceil(yPixel(cooordinate.second));

        std::cout << "x-Pixel value: " << xValue << std::endl;
        std::cout << "y-Pixel value: " << yValue << std::endl;

        std::lock_guard<std::mutex> guard(vecMutex[xValue]);
        {
            unsigned char *pixel_value = fractal.data((xValue), yValue, 0, 0);

            if ((*pixel_value) < 255)
                fractal(xValue, yValue, 0, 0) = (*pixel_value) + 255;

        }
        return false;
    }

};

cimg_library::CImg<unsigned char> GenuineConsumer::fractal = cimg_library::CImg<unsigned char>(X_DIM, Y_DIM, 1, 1);
int GenuineConsumer::numConsumers = 0;
bool GenuineConsumer::saveImage = false;
std::vector<std::mutex> GenuineConsumer::vecMutex(10000);

#endif //HA1_GENUINECONSUMER_H
