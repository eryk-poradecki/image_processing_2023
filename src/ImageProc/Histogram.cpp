#include "Histogram.h"
#include "ImageProc/Types.h"
#include <array>
#include <iostream>
#include <matplot/matplot.h>
#include <string_view>
#include <vector>

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
		matplot::ylim({0, +3000});
		// TODO 
		// Dont know how to set y lim automatically
		auto ax = matplot::gca();
        ax->x_axis().label_font_size(12);
    }
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
}
