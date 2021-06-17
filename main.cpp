#include <iostream>
#include "FractalCreator.h"
#include "Zoom.h"
using namespace Fun;

#define IMG_WIDTH 800
#define IMG_HEIGHT 600

int main(void)
{
    std::cout << "Enter" << std::endl;

    FractalCreator fractalCreator(IMG_WIDTH, IMG_HEIGHT);
    fractalCreator.AddZoom(Zoom(IMG_WIDTH/2, IMG_HEIGHT/2, 4.0/IMG_WIDTH));
    fractalCreator.AddZoom(Zoom(295, IMG_HEIGHT - 202, 0.1));
    fractalCreator.AddZoom(Zoom(312, IMG_HEIGHT - 304, 0.1));
    fractalCreator.Run("test.bmp");

    std::cout << "Exit" << std::endl;
    return 0;
}