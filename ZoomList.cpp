#include <iostream>
#include "ZoomList.h"

namespace Fun
{
    ZoomList::ZoomList(int width, int height) : m_iWidth(width), m_iHeight(height) {}
    void ZoomList::Add(const Zoom& zoom)
    {
        m_vZooms.push_back(zoom);
        m_dxCenter += (zoom.iX - m_iWidth/2)*m_dScale;
        m_dyCenter += (zoom.iY - m_iHeight/2)*m_dScale;
        m_dScale *= zoom.dScale;
        std::cout << m_dxCenter << ", " << m_dyCenter << ", " << m_dScale << std::endl;
    }

    std::pair<double, double> ZoomList::DoZoom(int x, int y)
    {
        double xFractal = (x - m_iWidth/2)*m_dScale + m_dxCenter;
        double yFractal = (y - m_iHeight/2)*m_dScale + m_dyCenter;
        return std::pair<double, double> (xFractal, yFractal);
    }
} // namespace Fun
