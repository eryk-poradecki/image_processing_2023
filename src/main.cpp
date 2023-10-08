#define cimg_display 0
#include "CImg.h"
#include "CLI/InputParser.hpp"
#include "ImageProc/ElementaryOperations.h"
#include "ImageProc/GeometricOperations.h"
#include "CImg.h"
#include "ImageProc/Types.h"
#include "config.hpp"
#include <iostream>
using namespace cimg_library;
using namespace ImageProc;

imgVec convertCimgtoImageVector(const CImg<unsigned char>& image);

void convertToCimgAndCopyBack(CImg<unsigned char>& cimgImage, const imgVec& imageArray);

int main(int argc, char** argv)
{
    cli::InputParser input(argc, argv);
    if (input.cmdOptionExists("--help")) {
        std::cout << config::programUsageInfo << std::endl;
    }
    const std::string& filename = input.getCmdOption("-f");
    if (!filename.empty()) {
        CImg<unsigned char> image(filename.c_str());
        int width = image.width();
        int height = image.height();
        int spectrum = image.spectrum();
        imgVec imageArray = convertCimgtoImageVector(image);

        Image img = Image(imageArray);
        if (input.cmdOptionExists("--brightness")) {
            int factor = std::stof(input.getCmdOption("--brightness"));
            elementary::adjustBrightness(img, factor);
            convertToCimgAndCopyBack(image, img.getImgVec());
        }
        if (input.cmdOptionExists("--contrast")) {
            float factor = std::stof(input.getCmdOption("--contrast"));
            elementary::adjustContrast(img, factor);
            convertToCimgAndCopyBack(image, img.getImgVec());
        }
        if (input.cmdOptionExists("--negative")) {
            elementary::createNegative(img);
            convertToCimgAndCopyBack(image, img.getImgVec());
        }
        if (input.cmdOptionExists("--vflip")) {
            geometric::verticalFlip(img);
            convertToCimgAndCopyBack(image, img.getImgVec());
        }
        if (input.cmdOptionExists("--hflip")) {
            geometric::horizontalFlip(img);
            convertToCimgAndCopyBack(image, img.getImgVec());
        }
        image.save("test.bmp");
    }
    return 0;
}

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
