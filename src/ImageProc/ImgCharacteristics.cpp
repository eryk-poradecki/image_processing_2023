#include "ImgCharacteristics.h"
#include "Histogram.h"
#include "Types.h"
#include <cmath>
#include <cstdlib>
#include <tuple>

using namespace ImageProc;
using namespace histogram;

std::tuple<float, float, float> characteristics::calculateMean(const Image& image)
{
    Histogram<NUM_BINS, 3> histogram;
    auto histData = histogram.createHistogramFromImg(image);

    float sumR = 0.0, sumG = 0.0, sumB = 0.0;
    float totalPixels = image.getWidth() * image.getHeight();

    for (size_t i = 0; i < NUM_BINS; ++i) {
        sumR += i * histData[0][i];
        sumG += i * histData[1][i];
        sumB += i * histData[2][i];
    }

    float meanR = sumR / totalPixels;
    float meanG = sumG / totalPixels;
    float meanB = sumB / totalPixels;

    return std::make_tuple(meanR, meanG, meanB);
}
