#pragma once
#include "Types.h"

namespace ImageProc::extractdetails {
ImageProc::imgVec extractionDetailsIII(ImageProc::Image& img, int kernelNum);
ImageProc::imgVec extractionDetailsIIIopt(ImageProc::Image& img);
ImageProc::imgVec convolution(ImageProc::Image& img, const std::vector<std::vector<int>>& kernel);
ImageProc::imgVec convolveHorizontal(ImageProc::Image& img, const std::vector<float>& kernel);
ImageProc::imgVec convolveVertical(ImageProc::Image& img, const std::vector<float>& kernel);
}
