#pragma once

#include "Types.h"

namespace ImageProc {

    namespace noise {

        std::array<unsigned char, 3> getFirstMedianLast(std::vector<unsigned char>& values);

        imgVec adaptiveMedianFilter(Image& image, int minFilterSize, int maxFilterSize);

    } // namespace noise
} // namespace ImageProc