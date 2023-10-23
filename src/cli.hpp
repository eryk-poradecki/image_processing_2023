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
#include <filesystem>
#include <iostream>
#include <string>

const std::string OUTPUT_FILENAME("output.bmp");
const std::string HISTOGRAM_FILENAME("hist.jpg");

inline void cliMain(int argc, char** argv)
{

    cli::InputParser input(argc, argv);
    if (input.cmdOptionExists("--help")) {
        std::cout << config::programUsageInfo << std::endl;
    }
    const std::string& filename = input.getCmdOption("-f");
    if (filename.empty()) {
        std::cout << "Please provide filename\n";
    }
    if (!std::filesystem::exists(filename)) {
        std::cout << "Filename does not exist\n";
        return;
    }
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".bmp") {
        std::cout << "The file has a BMP extension." << std::endl;
        return;
    }

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
    if (input.cmdOptionExists("--hflip")) {
        geometric::horizontalFlip(img);
        convertToCimgAndCopyBack(image, img.getImgVec());
    }
    if (input.cmdOptionExists("--dflip")) {
        geometric::diagonalFlip(img);
        convertToCimgAndCopyBack(image, img.getImgVec());
    }
    if (input.cmdOptionExists("--shrink")) {
        int shrinkFactor = std::stoi(input.getCmdOption("--shrink"));
        imgVec shrunkImageVec = geometric::shrinkImage(img, shrinkFactor);

        CImg<unsigned char> cimgShrunkImage(shrunkImageVec.size(), shrunkImageVec[0].size(), 1, shrunkImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgShrunkImage, shrunkImageVec);

        cimgShrunkImage.save("shrunken_image.bmp");
    }
    if (input.cmdOptionExists("--enlarge")) {
        int enlargeFactor = std::stoi(input.getCmdOption("--enlarge"));
        imgVec enlargedImageVec = geometric::enlargeImage(img, enlargeFactor);

        CImg<unsigned char> cimgEnlargedImage(enlargedImageVec.size(), enlargedImageVec[0].size(), 1, enlargedImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgEnlargedImage, enlargedImageVec);

        cimgEnlargedImage.save("enlarged_image.bmp");
    }
    if (input.cmdOptionExists("--adaptive")) {
        int minFilterSize = std::stoi(input.getCmdOption("--min"));
        int maxFilterSize = std::stoi(input.getCmdOption("--max"));
        imgVec filteredImageVec = noise::adaptiveMedianFilter(img, minFilterSize, maxFilterSize);
        Image outImg = Image(filteredImageVec);
        if (input.cmdOptionExists("--mse")) {

            std::cout << "MSE:" << analysis::calculateMSE(img, outImg) << "\n";
        }

        if (input.cmdOptionExists("--pmse")) {

            std::cout << "PMSE:" << analysis::calculatePMSE(img, outImg) << "\n";
        }
        if (input.cmdOptionExists("--psnr")) {

            std::cout << "PSNR:" << analysis::calculatePSNR(img, outImg) << "\n";
        }
        if (input.cmdOptionExists("--md")) {

            std::cout << "MD:" << analysis::calculateMD(img, outImg) << "\n";
        }
        if (input.cmdOptionExists("--snr")) {

            std::cout << "SNR:" << analysis::calculatSNR(img, outImg) << "\n";
        }
        CImg<unsigned char> cimgFilteredImage(filteredImageVec.size(), filteredImageVec[0].size(), 1, filteredImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgFilteredImage, filteredImageVec);

        cimgFilteredImage.save("filtered_image.bmp");
    }
    if (input.cmdOptionExists("--histogram")) {
        histogram::createAndSaveHist(img, HISTOGRAM_FILENAME);
    }
    image.save(OUTPUT_FILENAME.c_str());
}
