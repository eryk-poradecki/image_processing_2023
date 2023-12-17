#pragma once
#include "CImg.h"
#include "ImageProc/Types.h"

using namespace cimg_library;
using namespace ImageProc;

imgVec convertCimgtoImageVector(const CImg<unsigned char>& image)
{
    int width = image.width();
    int height = image.height();
    int spectrum = image.spectrum();

    imgVec imageArray(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum)));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // https://stackoverflow.com/questions/3291923/how-to-get-rgb-value-by-cimg
            for (int k = 0; k < spectrum; k++) {
                imageArray[i][j][k] = image(i, j, 0, k);
            }
        }
    }

    return imageArray;
}

void convertToCimgAndCopyBack(CImg<unsigned char>& cimgImage, const imgVec& imageArray)
{
    for (int i = 0; i < imageArray.size(); i++) {
        for (int j = 0; j < imageArray[0].size(); j++) {
            for (int k = 0; k < imageArray[0][0].size(); k++)
                cimgImage(i, j, 0, k) = imageArray[i][j][k];
        }
    }
}
void convertToCimgAndCopyBack1Bit(CImg<unsigned char>& cimgImage, const imgVec& imageArray)
{
    for (int i = 0; i < imageArray.size(); i++) {
        for (int j = 0; j < imageArray[0].size(); j++) {
            cimgImage(i, j, 0, 0) = imageArray[i][j][0];
        }
    }
}
