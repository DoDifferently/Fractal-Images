#include <iostream>
#include <cstdint>
#include <memory>
#include "Bitmap.h"
#include "Mandelbrot.h"
using namespace std;
using namespace Fun;

#define IMG_WIDTH 800
#define IMG_HEIGHT 600

int main(void)
{
    Bitmap bitmap(IMG_WIDTH, IMG_HEIGHT);
    
    double min = INT_MAX;
    double max = INT_MIN;
    
    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0});
    unique_ptr<int[]> fractal(new int[IMG_WIDTH*IMG_WIDTH]{0});
    
    for(int y = 0; y < IMG_HEIGHT; ++y)
    {
        for(int x = 0; x < IMG_WIDTH; ++x)
        {
            double xFractal = (x - IMG_WIDTH/2 - 200)*(2.0/IMG_WIDTH);
            double yFractal = (y - IMG_HEIGHT/2)*(2.0/IMG_HEIGHT);
            int iterations = Mandelbrot::s_GetIterations(xFractal, yFractal);
            fractal[y*IMG_WIDTH + x] = iterations;
            if(iterations < Mandelbrot::MAX_ITERATIONS)
            {
                histogram[iterations]++;
            }            
            uint8_t color = (uint8_t)(256*(double)iterations/Mandelbrot::MAX_ITERATIONS);
            color = color*color*color;
            bitmap.SetPixel(x, y, 0, color, 0);
            if(color < min)
            {
                min = color;
            }
            if(color > max)
            {
                max = color;
            }
        }
    }
    int total = 0;
    for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
    {
        total += histogram[i];
    }
    for(int y = 0; y < IMG_HEIGHT; ++y)
    {
        for(int x = 0; x < IMG_WIDTH; ++x)
        {
            int iterations = fractal[y*IMG_WIDTH + x];
            double hue = 0.0;
            for(int i = 0; i <= iterations; ++i)
            {
                hue += ((double)histogram[i])/total;
            }
            uint8_t red = 0;
            uint8_t green = hue*255;
            uint8_t blue = 0;
            bitmap.SetPixel(x, y, red, green, blue);
        }
    }
    bitmap.Write("test.bmp");
    cout << "Finished" << endl;
    return 0;
}