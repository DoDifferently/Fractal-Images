#include <cmath>
#include "FractalCreator.h"
#include "Mandelbrot.h"
#include "RGB.h"

namespace Fun
{
    void FractalCreator::Run(std::string name)
    {
        m_CalculateIteration();
        m_CalculateTotalIterations();
        m_DrawFractal();
        m_WriteBitmap(name); 
    }

    FractalCreator::FractalCreator(int width, int height) : m_iWidth(width), m_iHeight(height),
    m_upHistogram(new int[Mandelbrot::MAX_ITERATIONS]{0}), m_upFractal(new int[m_iWidth*m_iHeight]{0}),
    m_bitmap(m_iWidth, m_iHeight), m_zoomList(m_iWidth, m_iHeight)
    {
    }
    
    void FractalCreator::m_CalculateIteration()
    {        
        for(int y = 0; y < m_iHeight; ++y)
        {
            for(int x = 0; x < m_iWidth; ++x)
            {
                std::pair<double, double> coords = m_zoomList.DoZoom(x, y);
                int iterations = Mandelbrot::s_GetIterations(coords.first, coords.second);
                m_upFractal[y*m_iWidth + x] = iterations;
                if(iterations < Mandelbrot::MAX_ITERATIONS)
                {
                    m_upHistogram[iterations]++;
                }
            }
        }
    }
    
    void FractalCreator::m_CalculateTotalIterations()
    {
        for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
        {
            m_iTotal += m_upHistogram[i];
        }
    }

    void FractalCreator::m_DrawFractal()
    {
        RGB start_color(0, 0, 0);
        RGB end_color(0, 255, 0);
        RGB color_diff = start_color - end_color;
        for(int y = 0; y < m_iHeight; ++y)
        {
            for(int x = 0; x < m_iWidth; ++x)
            {
                uint8_t red = 0;
                uint8_t green = 0;
                uint8_t blue = 0;
                int iterations = m_upFractal[y*m_iWidth + x];
                if(iterations != Mandelbrot::MAX_ITERATIONS)
                {
                    double hue = 0.0;
                    for(int i = 0; i <= iterations; ++i)
                    {
                        hue += ((double)m_upHistogram[i])/m_iTotal;
                    }
                    red = pow(start_color.r - color_diff.r, hue);
                    green = pow(start_color.g - color_diff.g, hue);
                    blue = pow(start_color.b - color_diff.b, hue);
                }            
                m_bitmap.SetPixel(x, y, red, green, blue);
            }
        }
    }

    void FractalCreator::AddZoom(const Zoom& zoom)
    {
        m_zoomList.Add(zoom);
    }

    void FractalCreator::m_WriteBitmap(std::string name)
    {
        m_bitmap.Write(name);
    }

    FractalCreator::~FractalCreator() {}
} // namespace Fun
