#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>

namespace Fun
{
    #pragma pack(push, 2)

    struct BitmapFileHeader
    {
        char header[2]{'B', 'M'};
        int32_t file_size;
        int32_t reserved{0};
        int32_t dataOffset;
    };

    #pragma(pop)
}

#endif /* BITMAPFILEHEADER_H_ */
