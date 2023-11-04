#pragma once

#include "Types.h"
#include <tuple>

namespace ImageProc {
namespace analysis {

    std::tuple<float, float, float> calculatePSNR(const Image& img1, const Image& img2);
    std::tuple<float, float, float> calculateMSE(const Image& img1, const Image& img2);
    std::tuple<float, float, float> calculateSNR(const Image& img1, const Image& img2);
    std::tuple<float, float, float> calculatePMSE(const Image& img1, const Image& img2);
    std::tuple<int, int, int> calculateMD(const Image& img1, const Image& img2);
    int calculate_3DVecMax(imgVec& threeDVector, int chan);
} // namespace elementary
} // namespace ImageProc
