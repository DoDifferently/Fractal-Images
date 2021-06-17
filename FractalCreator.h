#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>
#include <memory>
#include "Bitmap.h"
#include "ZoomList.h"

namespace Fun
{
    class FractalCreator
    {
        private:
            int m_iWidth;
            int m_iHeight;
            int m_iTotal = 0;
            std::unique_ptr<int[]> m_upHistogram{nullptr};
            std::unique_ptr<int[]> m_upFractal{nullptr};
            Bitmap m_bitmap;
            ZoomList m_zoomList;
        public:
            FractalCreator(int width, int height);
            virtual ~FractalCreator();

            void CalculateIteration();
            void CalculateTotalIterations();
            void DrawFractal();
            void AddZoom(const Zoom& zoom);
            void WriteBitmap(std::string name);
    };
} // namespace FUn


#endif /* FRACTALCREATOR_H_ */