#include <fstream>
#include <iostream>
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
using namespace Fun;

namespace Fun
{
    Bitmap::Bitmap(int width, int height) : m_iWidth(width), m_iHeight(height), m_pPixels(new uint8_t[width*height*3]{0})
    {
    }

    bool Bitmap::Write(std::string filename)
    {
        BitmapFileHeader st_fileHeader;
        BitmapInfoHeader st_infoHeader;
        st_fileHeader.file_size = sizeof(BitmapFileHeader)*sizeof(BitmapInfoHeader) + m_iWidth*m_iHeight*3;
        st_fileHeader.dataOffset = sizeof(BitmapFileHeader)*sizeof(BitmapInfoHeader);
        st_infoHeader.width = m_iWidth;
        st_infoHeader.height = m_iHeight;

        std::ofstream binFile;
        binFile.open(filename, std::ios::out|std::ios::binary);
        if (!binFile.is_open())
        {
            std::cout << "Could not create " << filename << std::endl;
            return false;
        }
        binFile.write((char *)&st_fileHeader, sizeof(st_fileHeader));
        binFile.write((char *)&st_infoHeader, sizeof(st_infoHeader));
        // error: invalid cast from type 'std::unique_ptr<unsigned char []>' to type 'char*' so need raw pointer here using get()
        binFile.write((char *)m_pPixels.get(), m_iWidth*m_iHeight*3);
        if (!binFile)
        {
            std::cout << "Could not write data to file " << filename << std::endl;
        }
        binFile.close();
        return true;
    }

    void Bitmap::SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
    {        
    }

    Bitmap::~Bitmap()
    {        
    }
}