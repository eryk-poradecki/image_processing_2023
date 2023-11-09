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

std::tuple<float, float, float> characteristics::calculateVariance(const Image& image)
{
    auto [meanR, meanG, meanB] = calculateMean(image);
    Histogram<NUM_BINS, 3> histogram;
    auto histData = histogram.createHistogramFromImg(image);

    float sumR = 0.0, sumG = 0.0, sumB = 0.0;
    float totalPixels = image.getWidth() * image.getHeight();

    for (size_t i = 0; i < NUM_BINS; ++i) {
        sumR += (i - meanR) * (i - meanR) * histData[0][i];
        sumG += (i - meanG) * (i - meanG) * histData[1][i];
        sumB += (i - meanB) * (i - meanB) * histData[2][i];
    }

    float varR = sumR / totalPixels;
    float varG = sumG / totalPixels;
    float varB = sumB / totalPixels;

    return std::make_tuple(varR, varG, varB);
}

std::tuple<float, float, float> characteristics::calculateStandardDeviation(const Image& image)
{
    auto [varR, varG, varB] = calculateVariance(image);

    float stdDevR = std::sqrt(varR);
    float stdDevG = std::sqrt(varG);
    float stdDevB = std::sqrt(varB);

    return std::make_tuple(stdDevR, stdDevG, stdDevB);
}

std::tuple<float, float, float> characteristics::calculateVariationCoefficientI(const Image& image)
{
    auto [stdDevR, stdDevG, stdDevB] = calculateStandardDeviation(image);
    auto [meanR, meanG, meanB] = calculateMean(image);

    float variationCoeffR = stdDevR / meanR;
    float variationCoeffG = stdDevG / meanG;
    float variationCoeffB = stdDevB / meanB;

    return std::make_tuple(variationCoeffR, variationCoeffG, variationCoeffB);
}
std::tuple<float, float, float> characteristics::calculateInformationSourceEntropy(const Image& image)
{

    Histogram<NUM_BINS, 3> histogram;
    auto histData = histogram.createHistogramFromImg(image);

    float sumR = 0.0, sumG = 0.0, sumB = 0.0;
    float totalPixels = image.getWidth() * image.getHeight();

    for (size_t i = 0; i < NUM_BINS; ++i) {
        if (histData[0][i] != 0)
            sumR += histData[0][i] * std::log2(histData[0][i] / totalPixels);
        if (histData[1][i] != 0)
            sumG += histData[1][i] * std::log2(histData[1][i] / totalPixels);
        if (histData[2][i] != 0)
            sumB += histData[2][i] * std::log2(histData[2][i] / totalPixels);
    }

    float factor = -1 / totalPixels;
    float informationSourceEntropyR = sumR * factor;
    float informationSourceEntropyG = sumG * factor;
    float informationSourceEntropyB = sumB * factor;

    return std::make_tuple(informationSourceEntropyR, informationSourceEntropyG, informationSourceEntropyB);
}
