#pragma once

#include "Types.h"

namespace ImageProc {
namespace analysis {

    float calculatePSNR(const Image& img1, const Image& img2);
    float calculateMSE(const Image& img1, const Image& img2);
    float calculatSNR(const Image& img1, const Image& img2);
    int calculatePMSE(const Image& img1, const Image& img2);
    int calculatePMSE(const Image& img1, const Image& img2);
    int calculateMD(const Image& img1, const Image& img2);
} // namespace elementary
} // namespace ImageProc
