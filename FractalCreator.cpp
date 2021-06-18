#include <cmath>
#include <assert.h>
#include "FractalCreator.h"
#include "Mandelbrot.h"

namespace Fun
{
    void FractalCreator::Run(std::string name)
    {
        m_CalculateIteration();
        m_CalculateTotalIterations();
        m_CalculateRangeTotals();
        m_DrawFractal();
        m_WriteBitmap(name); 
    }

    FractalCreator::FractalCreator(int width, int height) : m_iWidth(width), m_iHeight(height),
    m_upHistogram(new int[Mandelbrot::MAX_ITERATIONS]{0}), m_upFractal(new int[m_iWidth*m_iHeight]{0}),
    m_bitmap(m_iWidth, m_iHeight), m_zoomList(m_iWidth, m_iHeight)
    {
    }
    
    void FractalCreator::AddRange(double rangeEnd, const RGB& rgb)
    {
        m_vRanges.push_back(rangeEnd*Mandelbrot::MAX_ITERATIONS);
        m_vColors.push_back(rgb);
        if(m_bGotFirstRange)
        {
            m_vRangeTotals.push_back(0);
        }
        m_bGotFirstRange = true;
    }

    void FractalCreator::m_CalculateRangeTotals()
    {
        int rangeIndex = 0;
        for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
        {
            int pixels = m_upHistogram[i];
            if(i >= m_vRanges[rangeIndex+1])
            {
                rangeIndex++;
            }
            m_vRangeTotals[rangeIndex] += pixels;
        }
    }

    int FractalCreator::m_getRange(int iterations) const
    {
        int range = 0;
        for(int i = 1; i < m_vRanges.size(); ++i)
        {
            if(m_vRanges[i] > iterations)
            {
                break;
            }
            range = i;
        }
        assert(range > -1);
        assert(range < m_vRanges.size());
        return range;
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
        for(int y = 0; y < m_iHeight; ++y)
        {
            for(int x = 0; x < m_iWidth; ++x)
            {
                int iterations = m_upFractal[y*m_iWidth + x];

                int range = m_getRange(iterations);
                int rangeTotal = m_vRangeTotals[range];
                int rangeStart = m_vRanges[range];

                RGB& start_color = m_vColors[range];
                RGB& end_color = m_vColors[range+1];
                RGB color_diff = end_color - start_color;

                uint8_t red = 0;
                uint8_t green = 0;
                uint8_t blue = 0;
                if(iterations != Mandelbrot::MAX_ITERATIONS)
                {
                    int total_pixels = 0;
                    for(int i = rangeStart; i <= iterations; ++i)
                    {
                        total_pixels += m_upHistogram[i];
                    }
                    red = start_color.r + color_diff.r*((double)total_pixels/rangeTotal);
                    green = start_color.g + color_diff.g*((double)total_pixels/rangeTotal);
                    blue = start_color.b + color_diff.b*((double)total_pixels/rangeTotal);
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
