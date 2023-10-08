#include "Helpers.h"

using namespace ImageProc;
using namespace helpers;

bool cmpImgSpectrum(const Image& img1, const Image& img2)
{
    if (img1.getSpectrum() == img2.getSpectrum()) {
        return true;
    }
    return false;
}

bool cmpImgDim(const Image& img1, const Image& img2)
{
    if (img1.getHeight() == img2.getHeight() && img1.getWidth() == img2.getWidth()) {
        return true;
    }
    return false;
}
