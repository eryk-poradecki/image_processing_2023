#include <iostream>
#include "CLI/InputParser.hpp"
#include "ImageProc/Types.h" // Include the Image header
#include "config.hpp"
#include "ImageProc/ElementaryOperations.h"

using namespace cimg_library;

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

        // Create the Image object
        Image imageArray(height, std::vector<unsigned char>(width * spectrum));

        // Copy data into the Image object
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width * spectrum; ++j) {
                imageArray[i][j] = image.data()[i * width * spectrum + j];
            }
        }

        if (input.cmdOptionExists("--brightness")) {
            float factor = std::stof(input.getCmdOption("--brightness"));
            elementary::adjustBrightness(imageArray, width, height, spectrum, factor);

            // Copy data back to the CImg object
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width * spectrum; ++j) {
                    image.data()[i * width * spectrum + j] = imageArray[i][j];
                }
            }

            image.save("output.bmp");
        }
        else if (input.cmdOptionExists("--contrast")) {
            float factor = std::stof(input.getCmdOption("--contrast"));
            elementary::adjustContrast(imageArray, width, height, spectrum, factor);

            // Copy data back to the CImg object
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width * spectrum; ++j) {
                    image.data()[i * width * spectrum + j] = imageArray[i][j];
                }
            }

            image.save("output.bmp");
        }
        else if (input.cmdOptionExists("--negative")) {
            elementary::createNegative(imageArray, width, height, spectrum);

            // Copy data back to the CImg object
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width * spectrum; ++j) {
                    image.data()[i * width * spectrum + j] = imageArray[i][j];
                }
            }

            image.save("output.bmp");
        }
    }
    return 0;
}
