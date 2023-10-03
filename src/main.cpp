#define cimg_display 0
#include <iostream>

#include "CImg.h"

#include "CLI/InputParser.hpp"
#include "ImageProc/Image.h"
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
        if (input.cmdOptionExists("--brightness")) {
            float factor = std::stof(input.getCmdOption("--brightness"));
            elementary::adjustBrightness(image, factor);
            image.save("output.bmp");
        }
    }
    return 0;
}
