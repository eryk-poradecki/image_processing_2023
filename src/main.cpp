#define cimg_display 0
#include "CImg.h"
#include "CLI/InputParser.hpp"
#include "ImageProc/ElementaryOperations.h"
#include "ImageProc/GeometricOperations.h"
#include "ImageProc/Types.h"
#include "config.hpp"
#include "CImg.h"
#include <iostream>
using namespace cimg_library;
using namespace ImageProc;

// declaration
imgVec convertCimgtoImageVector(const CImg<unsigned char>& image);

void convertToCimgAndCopyBack(CImg<unsigned char>& cimgImage, const imgVec& imageArray) {
    // convert ImageVector (std::vector<std::vector<Pixel>>) to CImg image and save

    // copy data from imageVector to CImg
    for (int i = 0; i < imageArray.size(); i++) {
        for (int j = 0; j < imageArray[0].size(); j++) {
            cimgImage(i, j, 0, 0) = imageArray[i][j].r;
            cimgImage(i, j, 0, 1) = imageArray[i][j].g;
            cimgImage(i, j, 0, 2) = imageArray[i][j].b;
        }
    }
}

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

        Image img = Image(imageArray, spectrum);

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
        image.save("output.bmp");


    }
    return 0;
}

imgVec convertCimgtoImageVector(const CImg<unsigned char>& image)
{
    int width = image.width();
    int height = image.height();
    int spectrum = image.spectrum();
    int pixel_count = width * height;

    imgVec imageArray;
    std::vector<Pixel> row;

    for (int i = 0; i < height; i++) {
        row.clear();
        for (int j = 0; j < width; j++) {
            Pixel pix;
            // https://stackoverflow.com/questions/3291923/how-to-get-rgb-value-by-cimg
            pix.r = image(i, j, 0, 0);
            pix.g = image(i, j, 0, 1);
            pix.b = image(i, j, 0, 2);
            row.push_back(pix);
        }
        imageArray.push_back(row);
    }

    return imageArray;
}