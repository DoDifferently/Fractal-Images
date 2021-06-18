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
    fractalCreator.AddRange(0.0, RGB(0, 0, 0));
    fractalCreator.AddRange(0.3, RGB(255, 0, 0));
    fractalCreator.AddRange(0.5, RGB(255, 255, 0));
    fractalCreator.AddRange(1.0, RGB(255, 255, 255));
    fractalCreator.AddZoom(Zoom(IMG_WIDTH/2, IMG_HEIGHT/2, 4.0/IMG_WIDTH));
    fractalCreator.AddZoom(Zoom(295, IMG_HEIGHT - 202, 0.1));
    fractalCreator.AddZoom(Zoom(312, IMG_HEIGHT - 304, 0.1));
    fractalCreator.Run("test.bmp");

    std::cout << "Exit" << std::endl;
    return 0;
}