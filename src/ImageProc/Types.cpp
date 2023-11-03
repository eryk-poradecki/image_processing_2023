#include "Types.h"

using namespace ImageProc;

Image::Image(imgVec& img)
    : mImgVec(img)
{
    mHeight = img.size();
    mWidth = img[0].size();
    mSpectrum = img[0][0].size();
}
imgVec& Image::getImgVec() const noexcept
{
    return mImgVec;
}

int Image::getHeight() const noexcept
{
    return mHeight;
}
int Image::getWidth() const noexcept
{
    return mWidth;
}
int Image::getSpectrum() const noexcept
{
    return mSpectrum;
}

bool Image::operator!=(const Image& other) const
{
    return this->getImgVec() != other.getImgVec();
}

bool Image::operator==(const Image& other) const
{
    return this->getImgVec() == other.getImgVec();
}
