#include "Histogram.h"
#include "ImageProc/Types.h"
#include <array>
#include <cmath>
#include <iostream>
#include <matplot/matplot.h>
#include <numeric>
#include <string_view>
#include <vector>

int clipInt(int value, int minValue, int maxValue)
{
    return std::max(minValue, std::min(value, maxValue));
}
template <int nBins, int chan>
size_t firstNonZeroIndex(ImageProc::histogram::Histogram<nBins, chan>& hist);

template <int nBins, int chan>
size_t sumFirstNHist(ImageProc::histogram::Histogram<nBins, chan>& hist, size_t n);

template <int nBins, int chan>
size_t lastNonZeroIndex(ImageProc::histogram::Histogram<nBins, chan>& hist);

namespace ImageProc::histogram {

void createAndSaveHist(const ImageProc::Image& img, const std::string_view filename, size_t nBins)
{
    int numOfHist = img.getSpectrum();
    int col = img.getWidth();
    int row = img.getHeight();
    auto splitRGBVec = histogram::splitRGBImgToSaperateLayerRGB(img);
    for (int i = 0; i < numOfHist; ++i) {
        matplot::subplot(1, numOfHist, i);
        matplot::hist(splitRGBVec[i], nBins);
        auto x = matplot::linspace(0, 256);
        matplot::xticks({ 0, 128, 255 });
        auto ax = matplot::gca();
        ax->x_axis().label_font_size(12);
    }
    matplot::save(filename.data());
}

void createAndSaveHistForColorChannel(const ImageProc::Image& img, const std::string_view filename, int channel, size_t nBins)
{
    int col = img.getWidth();
    int row = img.getHeight();
    auto splitRGBVec = histogram::splitRGBImgToSaperateLayerRGB(img);

    if (channel < 0 || channel >= splitRGBVec.size()) {
        std::cout << "Invalid channel number" << std::endl;
        return;
    }

    matplot::hist(splitRGBVec[channel], nBins);
    auto x = matplot::linspace(0, 256);
    matplot::xticks({ 0, 128, 255 });
    auto ax = matplot::gca();
    ax->x_axis().label_font_size(12);
    matplot::save(filename.data());
}

std::vector<std::vector<unsigned char>> splitRGBImgToSaperateLayerRGB(const ImageProc::Image& img)
{
    int numOfHist = img.getSpectrum();
    int col = img.getWidth();
    int row = img.getHeight();
    std::vector<std::vector<unsigned char>> splitRGBVec(numOfHist, std::vector<unsigned char>(row * col, 0));
    auto imgMatrix = img.getImgVec();
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            for (size_t k = 0; k < numOfHist; ++k) {
                splitRGBVec[k][i * col + j] = imgMatrix[i][j][k];
            }
        }
    }
    return splitRGBVec;
}

ImageProc::imgVec finalProbabilityDensityFunction(const ImageProc::Image& image, const int gmin, const int gmax)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int spectrum = image.getSpectrum();

    auto inputImgVec = image.getImgVec();
    size_t numberOfPixels = width * height;

    imgVec outputImgVec(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum)));

    Histogram<NUM_BINS, 3> histogram;
    auto histData = histogram.createHistogramFromImg(image);

    float alpha = 1.0 / (gmax - gmin);
    for (int i = 0; i < spectrum; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < width; ++k) {
                float sumHist = sumFirstNHist(histData[i], inputImgVec[j][k][i]);
                float factor = std::log(1 - (1.0 / numberOfPixels) * sumHist);
                int newPixelValue = gmin - (1.0 / alpha) * factor;
                outputImgVec[j][k][i] = clipInt(newPixelValue, 0, 255);
            }
        }
    }
    return outputImgVec;
}

} // namespace ImageProc::histogram
template <int nBins, int chan>
size_t sumFirstNHist(ImageProc::histogram::Histogram<nBins, chan>& hist, size_t n)
{
    size_t sum = 0;
    for (size_t i = 0; i < n; ++i) {
        sum += hist[i];
    }
    return sum;
}

template <int nBins, int chan>
size_t firstNonZeroIndex(ImageProc::histogram::Histogram<nBins, chan>& hist)
{
    size_t i = 0;
    for (; i < hist.size(); ++i) {
        if (hist[i] != 0) {
            break;
        }
    }
    return i;
}

template <int nBins, int chan>
size_t lastNonZeroIndex(ImageProc::histogram::Histogram<nBins, chan>& hist)
{
    size_t i = 255;
    for (; i > hist.size(); --i) {
        if (hist[i] != 0) {
            break;
        }
    }
    return i;
}
