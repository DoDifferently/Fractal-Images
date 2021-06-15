#ifndef BITMAPFILEHEADER
#define BITMAPFILEHEADER

#include <cstdint>

struct BitMapFileHeader
{
    char header[2]{'B', 'M'};
    int32_t file_size;
    int32_t reserved{0};
    int32_t dataOffset;
};

#endif /* BITMAPFILEHEADER */