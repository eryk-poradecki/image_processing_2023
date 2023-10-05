#include "Exceptions.h"

using namespace ImageProc;

const char* ImgSpectrumValueException::what() const noexcept
{
    return "This is my custom exception";
}

const char* DimImgValueException::what() const noexcept
{
    return "Dimentions of images are not the same";
}