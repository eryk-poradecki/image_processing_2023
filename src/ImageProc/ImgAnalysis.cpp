#include "ImgAnalysis.h"
#include "Exceptions.h"
#include "Helpers.h"
#include "Types.h"
#include <cmath>
#include <cstdlib>

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
    int numerator = R * R;
    return 10 * std::log10(numerator / mse);
}

int analysis::calculatePMSE(const Image& img1, const Image& img2)
{

    // TODO(@rostekus)
    // linker error

    // if (!helpers::cmpImgSpectrum(img1, img2)) {
    //     throw ImgSpectrumValueException();
    // }

    // if (!helpers::cmpImgDim(img1, img2)) {
    //     throw DimImgValueException();
    // }

    float mse = analysis::calculateMSE(img1, img2);

    return (mse / (255 * 255));
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

float calculatSNR(const Image&  img1,const Image&  img2){
	
    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();
	
	if(img1 != img2){
		throw  DimImgValueException();
	}

    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();
    int numPixels = imgMatrix2[0][0].size();
	
	
	int dominator = 1;
	int numerator = 0; 

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            for (int k = 0; k < numPixels; ++k) {
                int diff = imgMatrix1[i][j][k] - imgMatrix2[i][j][k];
				dominator += diff *diff;
				numerator += imgMatrix1[i][j][k] *imgMatrix1[i][j][k];
             }
        }
    }
	 

	return 10 * std::log10(numerator/dominator);

}

