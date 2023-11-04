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

Image::Image()
    : mWidth(0)
    , mHeight(0)
    , mSpectrum(0)
{
    mImgVec = imgVec {};
}
Image& Image::operator=(Image&& other) noexcept
{
    if (this != &other) {
        // Release current resources
        mImgVec.clear(); // Assuming the ownership is within mImgVec

        // Move the data and control variables
        mImgVec = std::move(other.mImgVec);
        mWidth = other.mWidth;
        mHeight = other.mHeight;
        mSpectrum = other.mSpectrum;

        // Reset the source object
        other.mWidth = 0;
        other.mHeight = 0;
        other.mSpectrum = 0;
        other.mImgVec.clear();
    }
    return *this;
}
