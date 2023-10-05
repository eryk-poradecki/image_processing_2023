#include "ImgAnalysis.h"
#include "Exceptions.h"
#include "Helpers.h"
#include "Types.h"
#include <cmath>

using namespace ImageProc;

float analysis::calculateMSE(const Image& img1, const Image& img2)
{
    // TODO(@rostekus)
    // linker error

    // if (!helpers::cmpImgSpectrum(img1, img2)) {
    //     throw ImgSpectrumValueException();
    // }

    // if (!helpers::cmpImgDim(img1, img2)) {
    //     throw DimImgValueException();
    // }

    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();

    double mse = 0.0;
    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            double diff = static_cast<double>(imgMatrix1[i][j]) - static_cast<double>(imgMatrix2[i][j]);
            mse += diff * diff;
        }
    }

    mse /= static_cast<double>(numRows * numCols);
    return mse;
}

float analysis::calculatePSNR(const Image& img1, const Image& img2)
{
    // In the equation, R is the maximum fluctuation in the input image data type. For example, if the input image has a double-precision floating-point data type, then R is 1. If it has an 8-bit unsigned integer data type, R is 255
    int R = 255;

    float mse = analysis::calculateMSE(img1, img2);
    int numerator = R * R;
    return 10 * std::log10(numerator / mse);
}
