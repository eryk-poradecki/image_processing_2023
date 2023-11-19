#pragma once
#include "Types.h"

namespace ImageProc::extractdetails {
ImageProc::imgVec extractionDetailsIII(ImageProc::Image& img, int kernelNum);
ImageProc::imgVec convolution(ImageProc::Image& img, const std::vector<std::vector<int>>& kernel);
}
