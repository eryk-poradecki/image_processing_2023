#include "ImageProc/Types.h"
#include <iostream>

#include "helpers.hpp"
#include "gtest/gtest.h"
#include <ImageProc/ElementaryOperations.h>
#include <vector>

using namespace ImageProc;

TEST(ElementaryOperations, AdjustPositiveBrightnessWithDiffSpectrumTest)
{
    // spectrum 3
    imgVec inputVec(3, std::vector<unsigned char>(3 * 2));

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    imgVec expectedVec(3, std::vector<unsigned char>(3 * 2));

    expectedVec[0] = { 255, 10, 10, 255, 255, 10 };
    expectedVec[1] = { 11, 138, 138, 74, 74, 15 };
    expectedVec[2] = { 14, 15, 16, 11, 12, 13 };

    Image img3 = Image(inputVec, 3);

    elementary::adjustBrightness(img3, 10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    Image img1 = Image(inputVec, 1);
    elementary::adjustBrightness(img1, 10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img1.getImgVec()));
}

TEST(ElementaryOperations, AdjustNegativeBrightnessWithDiffSpectrumTest)
{
    //=================================================
    // spectrum 3
    imgVec inputVec(3, std::vector<unsigned char>(3 * 2));

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    imgVec expectedVec(3, std::vector<unsigned char>(3 * 2));

    expectedVec[0] = { 245, 0, 0, 245, 245, 0 };
    expectedVec[1] = { 0, 118, 118, 54, 54, 0 };
    expectedVec[2] = { 0, 0, 0, 0, 0, 0 };

    Image img3 = Image(inputVec, 3);

    elementary::adjustBrightness(img3, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    Image img1 = Image(inputVec, 1);
    elementary::adjustBrightness(img1, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img1.getImgVec()));
}


TEST(ElementaryOperations, AdjustPositiveConstrastWithDiffSpectrumTest)
{
    //=================================================
    // spectrum 3
    imgVec inputVec(3, std::vector<unsigned char>(3 * 2));

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    imgVec expectedVec(3, std::vector<unsigned char>(3 * 2));

    expectedVec[0] = { 245, 0, 0, 245, 245, 0 };
    expectedVec[1] = { 0, 118, 118, 54, 54, 0 };
    expectedVec[2] = { 0, 0, 0, 0, 0, 0 };

    Image img3 = Image(inputVec, 3);

    elementary::adjustBrightness(img3, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    Image img1 = Image(inputVec, 1);
    elementary::adjustBrightness(img1, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img1.getImgVec()));
}

TEST(ElementaryOperations, AdjustContrastTest)
{
    imgVec inputVec(3, std::vector<unsigned char>(3 * 2));

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    Image img = Image(inputVec, 3);

    imgVec expectedVec(3, std::vector<unsigned char>(3 * 2));

    expectedVec[0] = { 255, 0, 0, 255, 255, 0 };
    expectedVec[1] = { 0, 192, 192, 128, 128, 16 };
    expectedVec[2] = { 32, 64, 96, 0, 32, 64 };

	elementary::adjustContrast(img, 2.0);

    //EXPECT_TRUE(areVectorsEqual(expectedVec, img.getImgVec()));
}


TEST(ElementaryOperations, CreateNegativeTest)
{
    // Create an input image with a spectrum of 3
    imgVec inputVec(3, std::vector<unsigned char>(3 * 2));

    inputVec[0] = { 255, 0, 0, 255, 255, 0 };
    inputVec[1] = { 1, 128, 128, 64, 64, 5 };
    inputVec[2] = { 4, 5, 6, 1, 2, 3 };

    Image img = Image(inputVec, 3);

    // Define the expected result after creating the negative image
    imgVec expectedVec(3, std::vector<unsigned char>(3 * 2));

    expectedVec[0] = { 0, 255, 255, 0, 0, 255 };
    expectedVec[1] = { 254, 127, 127, 191, 191, 250 };
    expectedVec[2] = { 251, 250, 249, 254, 253, 252 };

    // Create the negative image
    elementary::createNegative(img);

    // Check if the resulting image matches the expected result
    EXPECT_TRUE(areVectorsEqual(expectedVec, img.getImgVec()));
}
