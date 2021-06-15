#ifndef BITMAP_H_
#define BITMAP_H_

#include <string>
#include <cstdint>
#include <memory>

namespace Fun
{
    class Bitmap
    {
        private:
            int m_iWidth{0};
            int m_iHeight{0};
            std::unique_ptr<uint8_t[]> m_pPixels{nullptr};

        public:
            Bitmap(int width, int height);
            void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
            bool Write(std::string filename);
            virtual ~Bitmap();
    };
} // namespace Fun


#endif /* BITMAP_H_ */
