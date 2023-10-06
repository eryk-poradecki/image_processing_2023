#include "Types.h"

using namespace ImageProc;

Image::Image(imgVec& img, short spectrum)
    : mImgVec(img)
    , mSpectrum(spectrum)
{
    mHeight = img.size();
    mWidth = img[0].size();
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
