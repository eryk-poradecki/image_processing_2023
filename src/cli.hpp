#pragma once

#include "CLI/InputParser.hpp"
#include "ImageProc/ElementaryOperations.h"
#include "ImageProc/ExtractionDetails.h"
#include "ImageProc/GeometricOperations.h"
#include "ImageProc/Histogram.h"
#include "ImageProc/ImgAnalysis.h"
#include "ImageProc/ImgCharacteristics.h"
#include "ImageProc/NoiseRemoval.h"
#include "ImageProc/NonLinearFilter.h"
#include "ImageProc/Types.h"
#include "config.hpp"
#include "files.hpp"
#include <CImg.h>
#include <ImageProc/MorphologicalOperations.h>
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
    if (input.cmdOptionExists("--dflip")) {
        geometric::diagonalFlip(img);
        convertToCimgAndCopyBack(image, img.getImgVec());
    }
    if (input.cmdOptionExists("--shrink")) {
        int shrinkFactor {};
        try {
            shrinkFactor = std::stoi(input.getCmdOption("--shrink"));
        } catch (...) {
            std::cout << "incorrent shrink factor\n";
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
            std::cout << "incorrent enlarge factor\n";
            return 1;
        }
        imgVec enlargedImageVec = geometric::enlargeImage(img, enlargeFactor);

        CImg<unsigned char> cimgEnlargedImage(enlargedImageVec.size(), enlargedImageVec[0].size(), 1, enlargedImageVec[0][0].size(), 0);

        convertToCimgAndCopyBack(cimgEnlargedImage, enlargedImageVec);

        cimgEnlargedImage.save("enlarged_image.bmp");
    }
    bool adaptiveFilter = input.cmdOptionExists("--adaptive");
    bool minFilter = input.cmdOptionExists("--min");
    bool maxFilter = input.cmdOptionExists("--max");
    imgVec filteredImageVec;
    Image outImg;
    if (adaptiveFilter) {
        int wmax, hmax, wmin, hmin;
        try {
            wmin = std::stoi(input.getCmdOption("--wmin"));
            wmax = std::stoi(input.getCmdOption("--wmax"));
            hmin = std::stoi(input.getCmdOption("--hmin"));
            hmax = std::stoi(input.getCmdOption("--hmax"));

        } catch (...) {
            std::cout << "incorrent hmin, hmax, wmin, mwax values\n";
            return -1;
        }
        if (hmin >= hmax || wmin >= wmax) {
            std::cout << "incorrent hmin, hmax, wmin, mwax values\n";
            return -1;
        }
        filteredImageVec = noise::adaptiveMedianFilter(img, wmin, wmax, hmin, hmax);
        Image filtered(filteredImageVec);
        outImg = std::move(Image(filteredImageVec));
    }
    if (maxFilter || minFilter) {
        int h, w;
        try {
            w = std::stoi(input.getCmdOption("--w"));
            h = std::stoi(input.getCmdOption("--h"));

        } catch (...) {
            std::cout << "incorrent h, w values\n";
            return -1;
        }
        filteredImageVec = noise::minMaxFilter(img, w, h, minFilter);
        outImg = std::move(Image(filteredImageVec));
    }
    if (adaptiveFilter || maxFilter || minFilter) {
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
    if (input.cmdOptionExists("--histogram")) {
        if (input.cmdOptionExists("--channel")) {
            int channel = std::stoi(input.getCmdOption("--channel"));
            histogram::createAndSaveHistForColorChannel(img, HISTOGRAM_FILENAME, channel);
        } else {
            histogram::createAndSaveHist(img, HISTOGRAM_FILENAME);
        }
        if (input.cmdOptionExists("--cmean")) {
            displayTuple(characteristics::calculateMean(img), spectrum);
        }
        if (input.cmdOptionExists("--cvariance")) {
            displayTuple(characteristics::calculateVariance(img), spectrum);
        }
        if (input.cmdOptionExists("--cstdev")) {
            displayTuple(characteristics::calculateStandardDeviation(img), spectrum);
        }
        if (input.cmdOptionExists("--cvarcoi")) {
            displayTuple(characteristics::calculateVariationCoefficientI(img), spectrum);
        }
        if (input.cmdOptionExists("--casyco")) {
            displayTuple(characteristics::calculateAsymmetryCoefficient(img), spectrum);
        }
        if (input.cmdOptionExists("--cflaco")) {
            displayTuple(characteristics::calculateFlatteningCoefficient(img), spectrum);
        }
        if (input.cmdOptionExists("--cvarcoii")) {
            displayTuple(characteristics::calculateVariationCoefficientII(img), spectrum);
        }
        if (input.cmdOptionExists("--centropy")) {
            displayTuple(characteristics::calculateInformationSourceEntropy(img), spectrum);
        }
    }
    if (input.cmdOptionExists("--dilation")) {
        std::vector<std::vector<unsigned char>> kernel = {
            { 0, 1, 0 },
            { 1, 1, 1 },
            { 0, 1, 0 }
        };
        imgVec dilationVec = morph::morph(img, kernel, "dilation");
        CImg<unsigned char> dilationImage(dilationVec.size(), dilationVec[0].size(), 1, 1, 0);
        convertToCimgAndCopyBack1Bit(dilationImage, dilationVec);
        dilationImage.save("dilation_image.bmp");
    }
    if (input.cmdOptionExists("--erosion")) {
        std::vector<std::vector<unsigned char>> kernel = {
            { 0, 1, 0 },
            { 1, 1, 1 },
            { 0, 1, 0 }
        };
        imgVec erosionVec = morph::morph(img, kernel, "erosion");
        CImg<unsigned char> erosionImage(erosionVec.size(), erosionVec[0].size(), 1, 1, 0);
        convertToCimgAndCopyBack1Bit(erosionImage, erosionVec);
        erosionImage.save("erosion_image.bmp");
    }
    // if (input.cmdOptionExists("--opening")) {
    //     imgVec openingVec = morph::opening(img);
    //     CImg<unsigned char> openingImage(openingVec.size(), openingVec[0].size(), 1, openingVec[0][0].size(), 0);
    //     convertToCimgAndCopyBack(openingImage, openingVec);
    //     openingImage.save("opening_image.bmp");
    // }
    // if (input.cmdOptionExists("--closing")) {
    //     imgVec closingVec = morph::closing(img);
    //     CImg<unsigned char> closingImage(closingVec.size(), closingVec[0].size(), 1, closingVec[0][0].size(), 0);
    //     convertToCimgAndCopyBack(closingImage, closingVec);
    //     closingImage.save("closing_image.bmp");
    // }
    if (input.cmdOptionExists("--hmt")) {
        imgVec hmtVec = morph::hitOrMissTransformation(img);
        CImg<unsigned char> hmtImage(hmtVec.size(), hmtVec[0].size(), 1, hmtVec[0][0].size(), 0);
        convertToCimgAndCopyBack(hmtImage, hmtVec);
        hmtImage.save("hmt_image.bmp");
    }
    // if (input.cmdOptionExists("--operationM1")) {
    //     imgVec operationVec = morph::operationM1(img);
    //     CImg<unsigned char> operationImage(operationVec.size(), operationVec[0].size(), 1, operationVec[0][0].size(), 0);
    //     convertToCimgAndCopyBack(operationImage, operationVec);
    //     operationImage.save("operationM1_image.bmp");
    // }
    if (input.cmdOptionExists("--slaplace")) {
        imgVec slaplace;
        if (input.cmdOptionExists("--opt")) {
            slaplace = extractdetails::extractionDetailsIIIopt(img);

        } else {
            int kernelNum = std::stoi(input.getCmdOption("--kernel"));
            slaplace = extractdetails::extractionDetailsIII(img, kernelNum);
        }
        CImg<unsigned char> cimgslaplaceImage(slaplace.size(), slaplace[0].size(), 1, slaplace[0][0].size(), 0);
        convertToCimgAndCopyBack(cimgslaplaceImage, slaplace);
        cimgslaplaceImage.save("slaplace_image.bmp");
    }
    if (input.cmdOptionExists("--orobertsii")) {
        imgVec robertsIIImageVec = filter::robertsOperatorII(img);
        Image robertsIIImage(robertsIIImageVec);
        CImg<unsigned char> cimgRobertsIIImage(robertsIIImageVec.size(), robertsIIImageVec[0].size(), 1, robertsIIImageVec[0][0].size(), 0);
        convertToCimgAndCopyBack(cimgRobertsIIImage, robertsIIImageVec);
        cimgRobertsIIImage.save("roberts_ii_image.bmp");
    }
    if (input.cmdOptionExists("--hexponent")) {

        int gmin = std::stof(input.getCmdOption("--gmin"));
        int gmax = std::stof(input.getCmdOption("--gmax"));

        if (gmin < 0 || gmin > gmax) {
            std::cout << "not correct values for gmin\n";
            return -1;
        }

        if (gmax > 255 || gmax < gmin) {
            std::cout << "not correct values for gmax\n";
            return -1;
        }
        std::cout << gmax << " " << gmin << std::endl;

        imgVec hexponentImageVec = histogram::finalProbabilityDensityFunction(img, gmin, gmax);
        CImg<unsigned char> cimgRobertsIIImage(hexponentImageVec.size(), hexponentImageVec[0].size(), 1, hexponentImageVec[0][0].size(), 0);
        convertToCimgAndCopyBack(cimgRobertsIIImage, hexponentImageVec);
        cimgRobertsIIImage.save("hexponent_image.bmp");
    }
    if (input.cmdOptionExists("--regionGrow")) {
        if (!input.cmdOptionExists("--seedPoints")) {
            std::cout << "Please provide seed points using --seedPoints option.\n";
            return -1;
        }

        std::string seedPointsStr = input.getCmdOption("--seedPoints");
        std::vector<std::pair<int, int>> seedPoints;

        size_t pos = 0;
        while ((pos = seedPointsStr.find(';')) != std::string::npos) {
            std::string pointStr = seedPointsStr.substr(0, pos);
            size_t commaPos = pointStr.find(',');
            if (commaPos == std::string::npos) {
                std::cout << "Invalid seed point format.\n";
                return -1;
            }
            int x = std::stoi(pointStr.substr(0, commaPos));
            int y = std::stoi(pointStr.substr(commaPos + 1));
            seedPoints.push_back({ x, y });
            seedPointsStr.erase(0, pos + 1);
        }

        if (!seedPointsStr.empty()) {
            size_t commaPos = seedPointsStr.find(',');
            if (commaPos == std::string::npos) {
                std::cout << "Invalid seed point format.\n";
                return -1;
            }
            int x = std::stoi(seedPointsStr.substr(0, commaPos));
            int y = std::stoi(seedPointsStr.substr(commaPos + 1));
            seedPoints.push_back({ x, y });
        }

        std::vector<ImageProc::imgVec> regions = morph::regionGrowing(seedPoints, img);

        for (size_t i = 0; i < regions.size(); ++i) {
            CImg<unsigned char> cimgRegion(regions[i].size(), regions[i][0].size(), 1, regions[i][0][0].size(), 0);
            convertToCimgAndCopyBack(cimgRegion, regions[i]);
            cimgRegion.save(("region_" + std::to_string(i) + ".bmp").c_str());
        }
    }
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
