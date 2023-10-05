#include "ImgAnalysis.h"
#include "Exceptions.h"
#include "Helpers.h"
#include "Types.h"

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
