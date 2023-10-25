#pragma once
#include "Types.h"
#include <array>
#include <tuple>

namespace ImageProc::noise {

std::tuple<unsigned char, unsigned char, unsigned char> getFirstMedianLast(std::vector<unsigned char>& values);

imgVec adaptiveMedianFilter(Image& image, int minFilterSize, int maxFilterSize);

} // namespace noise
