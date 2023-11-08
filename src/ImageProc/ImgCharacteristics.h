#pragma once
#include "ImageProc/Types.h"
#include "ImageProc/Histogram.h"

namespace ImageProc::characteristics {

    using namespace histogram;

    std::tuple<float, float, float> calculateMean(const Image& image);
}
