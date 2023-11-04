#pragma once
#include "Types.h"
#include <array>

namespace ImageProc {

namespace noise {

    std::tuple<unsigned char, unsigned char, unsigned char> getFirstMedianLast(std::vector<unsigned char>& values, int size);

    imgVec adaptiveMedianFilter(Image& image, int minW, int minH, int maxW, int maxH);
    imgVec minMaxFilter(Image& image, int w, int h, bool minFilter);

} // namespace noise
} // namespace ImageProc
