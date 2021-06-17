#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_

#include <vector>
#include <utility>
#include "Zoom.h"

namespace Fun
{
    class ZoomList
    {
        private:
            double m_dxCenter{0};
            double m_dyCenter{0};
            double m_dScale{1.0};

            int m_iWidth{0};
            int m_iHeight{0};
            /*
            * It's better to do this rather than writing using namespace standard.
            * And the reason for that is that the standard namespace imports a lot
            * of different classes and functions. So if you're going to use other C++
            * libraries the classes and function names in that could conflict with 
            * the standard ones.
            */
            std::vector<Zoom> m_vZooms;
        public:
            ZoomList(int width, int height);
            void Add(const Zoom& zoom);
            std::pair<double, double> DoZoom(int x, int y);
    };
} // namespace Fun


#endif /* ZOOMLIST_H_ */
