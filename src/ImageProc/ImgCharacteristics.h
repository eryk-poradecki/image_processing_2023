#pragma once
#include "ImageProc/Histogram.h"
#include "ImageProc/Types.h"

namespace ImageProc::characteristics {

using namespace histogram;

std::tuple<float, float, float> calculateMean(const Image& image);
}
