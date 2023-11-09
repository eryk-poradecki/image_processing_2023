#pragma once
#include "ImageProc/Histogram.h"
#include "ImageProc/Types.h"

namespace ImageProc::characteristics {

using namespace histogram;

std::tuple<float, float, float> calculateMean(const Image& image);
std::tuple<float, float, float> calculateVariance(const Image& image);
std::tuple<float, float, float> calculateStandardDeviation(const Image& image);
std::tuple<float, float, float> calculateVariationCoefficientI(const Image& image);
std::tuple<float, float, float> calculateInformationSourceEntropy(const Image& image);
}
