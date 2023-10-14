#include "ImageProc/Types.h"
#include <iostream>

#include "helpers.hpp"
#include "gtest/gtest.h"
#include <ImageProc/GeometricOperations.h>
#include <vector>

using namespace ImageProc;

TEST(GeometricOperations, HorizontalFlipTest)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    Image img(inputVec);

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));
    expectedVec[0] = { { 4, 5, 6 }, { 1, 2, 3 } };
    expectedVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    expectedVec[2] = { { 255, 0, 0 }, { 255, 255, 0 } };

    geometric::horizontalFlip(img);

    EXPECT_TRUE(expectedVec == img.getImgVec());
}

TEST(GeometricOperations, VerticalFlipTest)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    Image img(inputVec);

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));
    expectedVec[0] = { { 255, 255, 0 }, { 255, 0, 0 } };
    expectedVec[1] = { { 64, 64, 5 }, { 1, 128, 128 } };
    expectedVec[2] = { { 1, 2, 3 }, { 4, 5, 6 } };

    geometric::verticalFlip(img);

    EXPECT_TRUE(expectedVec == img.getImgVec());
}

TEST(GeometricOperations, DiagonalFlipTest)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    Image img(inputVec);

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));
    expectedVec[0] = { { 1, 2, 3 }, { 4, 5, 6 } };
    expectedVec[1] = { { 64, 64, 5 }, { 1, 128, 128 } };
    expectedVec[2] = { { 255, 255, 0 }, { 255, 0, 0 } };

    geometric::diagonalFlip(img);

    EXPECT_TRUE(expectedVec == img.getImgVec());
}

TEST(GeometricOperations, ShrinkTest)
{
    imgVec inputVec(4, std::vector<std::vector<unsigned char>>(4, std::vector<unsigned char>(1, 128)));
    Image inputImage(inputVec);

    int shrinkFactor = 2;
    imgVec shrunkImageVec = geometric::shrinkImage(inputImage, shrinkFactor);

    EXPECT_EQ(shrunkImageVec.size(), 2);
    EXPECT_EQ(shrunkImageVec[0].size(), 2);

    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < 2; ++x) {
            unsigned char expectedValue = 128;

            EXPECT_EQ(shrunkImageVec[y][x][0], expectedValue);
        }
    }
}

TEST(GeometricOperations, EnlargeTest)
{
    imgVec inputVec(2, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(1, 255)));
    Image inputImage(inputVec);

    int enlargeFactor = 2;
    imgVec enlargedImageVec = geometric::enlargeImage(inputImage, enlargeFactor);

    EXPECT_EQ(enlargedImageVec.size(), 4);
    EXPECT_EQ(enlargedImageVec[0].size(), 4);

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            unsigned char expectedValue = 255;

            EXPECT_EQ(enlargedImageVec[y][x][0], expectedValue);
        }
    }
}

