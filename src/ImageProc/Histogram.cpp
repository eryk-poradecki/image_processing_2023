#include "Histogram.h"

using namespace ImageProc;
void histogram::createAndSaveHist(ImageProc::Image& img, std::string filename, size_t nBins)
{
    auto imgVec = img.getImgVec();
    int numOfHist = img.getSpectrum();
    int col = img.getWidth();
    int row = img.getHeight();
    std::cout << numOfHist << std::endl;
    std::vector<std::vector<unsigned char>> splitRGBVec(numOfHist, std::vector<unsigned char>(row * col, 150));
    for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < row; j++) {
            for (size_t k = 0; k < numOfHist; k++) {
                splitRGBVec[k][i * col + j] = imgVec[i][j][k];
            }
        }
    }

    for (int i = 0; i < numOfHist; i++) {
        matplot::subplot(1, numOfHist, i);
        matplot::hist(splitRGBVec[i], nBins);
        auto x = matplot::linspace(0, 255);
        matplot::xticks({ 0, 128, 255 });
        auto ax = matplot::gca();
        ax->x_axis().label_font_size(12);
    }
    matplot::save(filename);
}
