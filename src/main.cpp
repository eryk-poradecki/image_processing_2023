#include <iostream>
#include "CLI/InputParser.hpp"
#include "ImageProc/Types.h"
#include "config.hpp"
#include "ImageProc/ElementaryOperations.h"

using namespace cimg_library;
using namespace ImageProc;

void copyImageDataBack(CImg<unsigned char>& cimgImage, const Image& imageArray);

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

        Image imageArray(height, std::vector<unsigned char>(width * spectrum));

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width * spectrum; ++j) {
                imageArray[i][j] = image.data()[i * width * spectrum + j];
            }
        }

        if (input.cmdOptionExists("--brightness")) {
            float factor = std::stof(input.getCmdOption("--brightness"));
            elementary::adjustBrightness(imageArray, width, height, spectrum, factor);

            copyImageDataBack(image, imageArray);
            image.save("output.bmp");
        }
        else if (input.cmdOptionExists("--contrast")) {
            float factor = std::stof(input.getCmdOption("--contrast"));
            elementary::adjustContrast(imageArray, width, height, spectrum, factor);

            copyImageDataBack(image, imageArray);
            image.save("output.bmp");
        }
        else if (input.cmdOptionExists("--negative")) {
            elementary::createNegative(imageArray, width, height, spectrum);

            copyImageDataBack(image, imageArray);
            image.save("output.bmp");
        }
    }
    return 0;
}

void copyImageDataBack(CImg<unsigned char>& cimgImage, const Image& imageArray) {
    int width = cimgImage.width();
    int height = cimgImage.height();
    int spectrum = cimgImage.spectrum();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * spectrum; ++j) {
            cimgImage.data()[i * width * spectrum + j] = imageArray[i][j];
        }
    }
}
