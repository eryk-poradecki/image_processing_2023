#pragma once
#include "ImageProc/Types.h"
#include "matplot/matplot.h"
#include <array>
#include <iostream>
#include <matplot/freestanding/axes_functions.h>
#include <string>
#include <string_view>
#include <vector>

// cpp17 magic namespace
namespace ImageProc::histogram {

constexpr size_t NUM_BINS = 256;

std::vector<std::vector<unsigned char>> splitRGBImgToSaperateLayerRGB(const ImageProc::Image& img);

/**
 * @class Histogram
 * @brief class for creating hisgrams from Image
 *
 */
template <int nBins, int chan>
class Histogram {
    static_assert(nBins <= NUM_BINS);

public:
    Histogram()
        : bins {} {};

    [[nodiscard]] std::array<Histogram<nBins, chan>, chan> createHistogramFromImg(const ImageProc::Image& img)
    {

        double factor = static_cast<double>(nBins) / NUM_BINS;
        auto splitVec = splitRGBImgToSaperateLayerRGB(img);
        std::array<Histogram<nBins, chan>, chan> histograms;
        for (int numOfChan = 0; numOfChan < splitVec.size(); ++numOfChan) {
            /* auto& bins = histograms[numOfChan].getArr(); */
            for (auto& pixel : splitVec[numOfChan]) {
                int bin = static_cast<int>(pixel * factor);
                std::cout << "bin  : " << bin << "\n";
                ++histograms[numOfChan][bin];
            }
        }
        return histograms;
    }

    [[nodiscard]] size_t size() const noexcept
    {
        return bins.size();
    }

    int operator[](int index) const
    {
        return bins[index];
    }

    int& operator[](int index)
    {
        return bins[index];
    }

    std::array<int, nBins> getArr() const noexcept
    {
        return bins;
    }

private:
    std::array<int, nBins> bins;
};

void createAndSaveHist(const ImageProc::Image& img, const std::string_view filename, size_t nBins = NUM_BINS);

}
