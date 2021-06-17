#include <cmath>
#include "FractalCreator.h"
#include "Mandelbrot.h"

namespace Fun
{
    FractalCreator::FractalCreator(int width, int height) : m_iWidth(width), m_iHeight(height),
    m_upHistogram(new int[Mandelbrot::MAX_ITERATIONS]{0}), m_upFractal(new int[m_iWidth*m_iHeight]{0}),
    m_bitmap(m_iWidth, m_iHeight), m_zoomList(m_iWidth, m_iHeight)
    {
    }
    
    void FractalCreator::CalculateIteration()
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
    void FractalCreator::CalculateTotalIterations()
    {
        for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
        {
            m_iTotal += m_upHistogram[i];
        }
    }
    void FractalCreator::DrawFractal()
    {
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
                    green = pow(255, hue);
                }            
                m_bitmap.SetPixel(x, y, red, green, blue);
            }
        }
    }
    void FractalCreator::AddZoom(const Zoom& zoom)
    {
        m_zoomList.Add(zoom);
    }
    void FractalCreator::WriteBitmap(std::string name)
    {
        m_bitmap.Write(name);
    }

    FractalCreator::~FractalCreator() {}
} // namespace Fun
