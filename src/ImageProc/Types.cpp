#include "Types.h"

using namespace ImageProc;

Image::Image(imgVec& img)
    : mImgVec(img)
{
    mHeight = img.size();
    mWidth = img[0].size();
    mSpectrum = img[0][0].size();
}
imgVec& Image::getImgVec() const
{
    return mImgVec;
}

int Image::getHeight() const
{
    return mHeight;
}
int Image::getWidth() const
{
    return mWidth;
}
int Image::getSpectrum() const
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
