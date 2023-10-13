#pragma once

#include "Types.h"

namespace ImageProc {

    namespace noise {

        int computeMedian(std::vector<unsigned char> values);

        imgVec adaptiveMedianFilter(Image& image, int minFilterSize, int maxFilterSize);

    } // namespace noise
} // namespace ImageProc