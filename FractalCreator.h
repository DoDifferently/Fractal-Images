#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <string>
#include <memory>
#include <vector>
#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"

namespace Fun
{
    class FractalCreator
    {
        private:
            int m_iWidth;
            int m_iHeight;
            int m_iTotal = 0;
            bool m_bGotFirstRange{false};
            std::unique_ptr<int[]> m_upHistogram{nullptr};
            std::unique_ptr<int[]> m_upFractal{nullptr};
            Bitmap m_bitmap;
            ZoomList m_zoomList;
            std::vector<int> m_vRanges;
            std::vector<RGB> m_vColors;
            std::vector<int> m_vRangeTotals;

        public:
            FractalCreator(int width, int height);
            virtual ~FractalCreator();
            void Run(std::string name);
            void AddZoom(const Zoom& zoom);
            void AddRange(double rangeEnd, const RGB& rgb);

        private:
            void m_CalculateRangeTotals();
            void m_CalculateIteration();
            void m_CalculateTotalIterations();
            void m_DrawFractal();
            void m_WriteBitmap(std::string name);
    };
} // namespace FUn


#endif /* FRACTALCREATOR_H_ */
