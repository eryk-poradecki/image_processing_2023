#pragma once

#include "CLI/InputParser.hpp"
#include "ImageProc/ElementaryOperations.h"
#include "ImageProc/GeometricOperations.h"
#include "ImageProc/Histogram.h"
#include "ImageProc/ImgAnalysis.h"
#include "ImageProc/NoiseRemoval.h"
#include "ImageProc/Types.h"
#include "config.hpp"
#include "files.hpp"
#include <CImg.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

const std::string OUTPUT_FILENAME("output.bmp");
const std::string HISTOGRAM_FILENAME("hist.jpg");

template <typename T>
void displayTuple(std::tuple<T, T, T> res, int chan);

inline int cliMain(int argc, char** argv)
{

    cli::InputParser input(argc, argv);
    if (input.cmdOptionExists("--help")) {
        std::cout << config::programUsageInfo << std::endl;
    }
    const std::string& filename = input.getCmdOption("-f");
    if (filename.empty()) {
        std::cout << "Please provide filename\n";
        return -1;
    }
    if (!std::filesystem::exists(filename)) {
        std::cout << "Filename does not exist\n";
        return -1;
    }
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".bmp") {
        std::cout << "The file has a BMP extension." << std::endl;
        return -1;
    }

    CImg<unsigned char> image(filename.c_str());
    int width = image.width();
    int height = image.height();
    int spectrum = image.spectrum();
    imgVec imageArray = convertCimgtoImageVector(image);

    Image img = Image(imageArray);
    if (input.cmdOptionExists("--brightness")) {
        int factor;
        try {
            factor = std::stof(input.getCmdOption("--brightness"));
        } catch (...) {
            std::cout << "uncorrent brightness factor\n";
            return 1;
        }
        elementary::adjustBrightness(img, factor);
        convertToCimgAndCopyBack(image, img.getImgVec());
    }
    if (input.cmdOptionExists("--contrast")) {
        int factor {};
        try {
            factor = std::stoi(input.getCmdOption("--contrast"));
        } catch (...) {
            std::cout << "uncorrent contrast factor\n";
            return 1;
        }
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
    if (input.cmdOptionExists("--hflip")) {
        geometric::horizontalFlip(img);
        convertToCimgAndCopyBack(image, img.getImgVec());
    }
    if (input.cmdOptionExists("--dflip")) {
        geometric::diagonalFlip(img);
        convertToCimgAndCopyBack(image, img.getImgVec());
    }
    if (input.cmdOptionExists("--shrink")) {
        int shrinkFactor {};
        try {
            shrinkFactor = std::stoi(input.getCmdOption("--shrink"));
        } catch (...) {
            std::cout << "uncorrent shrink factor\n";
            return 1;
        }
        imgVec shrunkImageVec = geometric::shrinkImage(img, shrinkFactor);

        CImg<unsigned char> cimgShrunkImage(shrunkImageVec.size(), shrunkImageVec[0].size(), 1, shrunkImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgShrunkImage, shrunkImageVec);

        cimgShrunkImage.save("shrunken_image.bmp");
    }
    if (input.cmdOptionExists("--enlarge")) {
        int enlargeFactor {};
        try {
            enlargeFactor = std::stoi(input.getCmdOption("--enlarge"));
        } catch (...) {
            std::cout << "uncorrent enlarge factor\n";
            return 1;
        }
        imgVec enlargedImageVec = geometric::enlargeImage(img, enlargeFactor);

        CImg<unsigned char> cimgEnlargedImage(enlargedImageVec.size(), enlargedImageVec[0].size(), 1, enlargedImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgEnlargedImage, enlargedImageVec);

        cimgEnlargedImage.save("enlarged_image.bmp");
    }
    if (input.cmdOptionExists("--adaptive")) {
        int wmax, hmax, wmin, hmin;
        try {
            wmin = std::stoi(input.getCmdOption("--wmin"));
            wmax = std::stoi(input.getCmdOption("--wmax"));
            hmin = std::stoi(input.getCmdOption("--hmin"));
            hmax = std::stoi(input.getCmdOption("--hmax"));

        } catch (...) {
            std::cout << "uncorrent hmin, hmax, wmin, mwax values\n";
            return -1;
        }
        if (hmin >= hmax || wmin >= wmax) {
            std::cout << "uncorrent hmin, hmax, wmin, mwax values\n";
            return -1;
        }
        imgVec filteredImageVec = noise::adaptiveMedianFilter(img, wmin, wmax, hmin, hmax);
        Image outImg = Image(filteredImageVec);
        if (input.cmdOptionExists("--mse")) {
            std::cout << "MSE:\n";
            displayTuple(analysis::calculateMSE(img, outImg), spectrum);
        }

        if (input.cmdOptionExists("--pmse")) {
            std::cout << "PMSE:\n";
            displayTuple(analysis::calculatePMSE(img, outImg), spectrum);
        }
        if (input.cmdOptionExists("--psnr")) {
            std::cout << "PSNR:\n";
            displayTuple(analysis::calculatePSNR(img, outImg), spectrum);
        }
        if (input.cmdOptionExists("--md")) {

            std::cout << "MD:\n";
            displayTuple(analysis::calculateMD(img, outImg), spectrum);
        }

        if (input.cmdOptionExists("--snr")) {
            std::cout << "SNR:\n";
            displayTuple(analysis::calculateSNR(img, outImg), spectrum);
        }
        CImg<unsigned char> cimgFilteredImage(filteredImageVec.size(), filteredImageVec[0].size(), 1, filteredImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgFilteredImage, filteredImageVec);

        cimgFilteredImage.save("filtered_image.bmp");
    }
    // if (input.cmdOptionExists("--histogram")) {
    //     histogram::createAndSaveHist(img, HISTOGRAM_FILENAME);
    // }
    image.save(OUTPUT_FILENAME.c_str());
    return 0;
}

template <typename T>
void displayTuple(std::tuple<T, T, T> res, int chan)
{
    auto [r, g, b] = res;
    if (chan == 1) {
        std::cout << r << "\n";
        return;
    }

    std::cout << r << "\n";
    std::cout << g << "\n";
    std::cout << b << "\n";
}
