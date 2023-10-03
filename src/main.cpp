#define cimg_display 0
#include <iostream>

#include "CImg.h"

#include "CLI/InputParser.hpp"
#include "ImageProc/Image.h"
#include "config.hpp"

using namespace cimg_library;

int main(int argc, char** argv)
{
    cli::InputParser input(argc, argv);
    if (input.cmdOptionExists("--help")) {
        std::cout << config::programUsageInfo << std::endl;
    }
    const std::string& filename = input.getCmdOption("-f");
    if (!filename.empty()) { }
    return 0;
}
