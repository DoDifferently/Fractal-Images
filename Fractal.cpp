#include <iostream>
#include <cstdint>
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
    
    for(int y = 0; y < IMG_HEIGHT; ++y)
    {
        for(int x = 0; x < IMG_WIDTH; ++x)
        {
            double xFractal = (x - IMG_WIDTH/2)*(2.0/IMG_WIDTH);
            double yFractal = (y - IMG_HEIGHT/2)*(2.0/IMG_HEIGHT);
            int iterations = Mandelbrot::s_GetIterations(xFractal, yFractal);
            uint8_t red = (uint8_t)(256*(double)iterations/Mandelbrot::MAX_ITERATIONS);
            bitmap.SetPixel(x, y, red, 0, 0);
            if(red < min)
            {
                min = xFractal;
            }
            if(red > max)
            {
                max = xFractal;
            }
        }
    }
    cout << min << ", " << max << endl;
    bitmap.Write("test.bmp");
    cout << "Finished" << endl;
    return 0;
}