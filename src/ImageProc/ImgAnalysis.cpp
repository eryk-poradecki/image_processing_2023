#include "ImgAnalysis.h"
#include "Exceptions.h"
#include "Helpers.h"
#include "Types.h"
#include <cmath>
#include <cstdlib>

using namespace ImageProc;

int calculate_3DVecMax(imgVec& threeDVector);

float analysis::calculateMSE(const Image& img1, const Image& img2)
{

    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();

    double mse = 0.0;
    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();
    int numPixels = imgMatrix2[0][0].size();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            for (int k = 0; k < numPixels; ++k) {
                double diff = static_cast<double>(imgMatrix1[i][j][k]) - static_cast<double>(imgMatrix2[i][j][k]);
                mse += diff * diff;
            }
        }
    }

    mse /= static_cast<double>(numRows * numCols * numPixels);
    return mse;
}

float analysis::calculatePSNR(const Image& img1, const Image& img2)
{
    // In the equation, R is the maximum fluctuation in the input image data type. For example, if the input image has a double-precision floating-point data type, then R is 1. If it has an 8-bit unsigned integer data type, R is 255
    int R = 255;

    imgVec imgMatrix1 = img1.getImgVec();

    int numRows = imgMatrix1.size();
    int numCols = imgMatrix1[0].size();
    int numPixels = imgMatrix1[0][0].size();

    float mse = analysis::calculateMSE(img1, img2) * numPixels * numCols * numRows;

    int max = calculate_3DVecMax(imgMatrix1);

    int numerator = max * max;
    return 10 * std::log10(numerator / mse);
}

int analysis::calculatePMSE(const Image& img1, const Image& img2)
{

    float mse = analysis::calculateMSE(img1, img2);
    int max = calculate_3DVecMax(img1.getImgVec());
    return (mse / (max * max));
}

int analysis::calculateMD(const Image& img1, const Image& img2)
{

    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();

    int peak = 0;
    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();
    int numPixels = imgMatrix2[0][0].size();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            for (int k = 0; k < numPixels; ++k) {
                int diff = imgMatrix1[i][j][k] - imgMatrix2[i][j][k];
                peak = std::max(peak, std::abs(diff));
            }
        }
    }
    return peak;
}

float analysis::calculatSNR(const Image& img1, const Image& img2)
{

    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();

    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();
    int numPixels = imgMatrix2[0][0].size();

    int denominator = 1;
    int numerator = 0;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            for (int k = 0; k < numPixels; ++k) {
                int diff = imgMatrix1[i][j][k] - imgMatrix2[i][j][k];
                denominator += diff * diff;
                numerator += imgMatrix1[i][j][k] * imgMatrix1[i][j][k];
            }
        }
    }

    return 10 * std::log10(numerator / denominator);
}

int calculate_3DVecMax(imgVec& threeDVector)
{

    int max_value = threeDVector[0][0][0];
    for (const auto& layer : threeDVector) {
        for (const auto& row : layer) {
            for (const int& value : row) {
                if (value > max_value) {
                    max_value = value;
                }
            }
        }
    }
    return max_value;
}
