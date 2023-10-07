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
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));

    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };

    imgVec expectedVec(3, std::vector<Pixel>(3 * 2));

    expectedVec[0] = { {255, 10, 10}, {255, 255, 10} };
    expectedVec[1] = { {11, 138, 138}, {74, 74, 15} };
    expectedVec[2] = { {14, 15, 16}, {11, 12, 13} };

    Image img3 = Image(inputVec, 3);

    elementary::adjustBrightness(img3, 10);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    // inputVec[0] = { {255}, {0}, {0}, {255}, {255}, {0} };
    // inputVec[1] = { {1}, {128}, {128}, {64}, {64}, {5} };
    // inputVec[2] = { {4}, {5}, {6}, {1}, {2}, {3} };

    // Image img1 = Image(inputVec, 1);
    // elementary::adjustBrightness(img1, 10);

    // EXPECT_TRUE(areImageVectorsEqual(expectedVec, img1.getImgVec()));
}

TEST(ElementaryOperations, AdjustNegativeBrightnessWithDiffSpectrumTest)
{
    //=================================================
    // spectrum 3
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));

    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };

    imgVec expectedVec(3, std::vector<Pixel>(3 * 2));

    expectedVec[0] = { {245, 0, 0}, {245, 245, 0} };
    expectedVec[1] = { {0, 118, 118}, {54, 54, 0} };
    expectedVec[2] = { {0, 0, 0}, {0, 0, 0} };

    Image img3 = Image(inputVec, 3);

    elementary::adjustBrightness(img3, -10);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img3.getImgVec()));

//     //=================================================
//     // spectrum 1

//     inputVec[0] = { 255, 0, 0, 255, 255, 0 };
//     inputVec[1] = { 1, 128, 128, 64, 64, 5 };
//     inputVec[2] = { 4, 5, 6, 1, 2, 3 };

//     Image img1 = Image(inputVec, 1);
//     elementary::adjustBrightness(img1, -10);

//     EXPECT_TRUE(areVectorsEqual(expectedVec, img1.getImgVec()));
}

TEST(ElementaryOperations, AdjustPositiveConstrastWithDiffSpectrumTest)
{
    //=================================================
    // spectrum 3
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));

    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };

    imgVec expectedVec(3, std::vector<Pixel>(3 * 2));

    expectedVec[0] = { {245, 0, 0}, {245, 245, 0} };
    expectedVec[1] = { {0, 118, 118}, {54, 54, 0} };
    expectedVec[2] = { {0, 0, 0}, {0, 0, 0} };

    Image img3 = Image(inputVec, 3);

    elementary::adjustBrightness(img3, -10);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    // imgVec inputVec1(3, std::vector<Pixel>(3 * 2));

    // inputVec1[0] = { {255}, {0}, {0}, {255}, {255}, {0} };
    // inputVec1[1] = { {1}, {128}, {128}, {64}, {64}, {5} };
    // inputVec1[2] = { {4}, {5}, {6}, {1}, {2}, {3} };

    // imgVec expectedVec1(3, std::vector<Pixel>(3 * 2));

    // expectedVec1[0] = { {245}, {0}, {0}, {245}, {245}, {0} };
    // expectedVec1[1] = { {0}, {118}, {118}, {54}, {54}, {0} };
    // expectedVec1[2] = { {0}, {0}, {0}, {0}, {0}, {0} };

    // Image img1 = Image(inputVec1, 1);
    // elementary::adjustBrightness(img1, -10);

    // EXPECT_TRUE(areImageVectorsEqual(expectedVec1, img1.getImgVec()));
}

TEST(ElementaryOperations, AdjustContrastTest)
{
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));
    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };
    Image img = Image(inputVec, 3);

    float contrastFactor = 1.5; 

    imgVec expectedVec(3, std::vector<Pixel>(inputVec[0].size()));
    for (auto& row : expectedVec) {
        for (auto& pixel : row) {
            Pixel inputPixel = inputVec[&row - &expectedVec[0]][&pixel - &row[0]];

            float expectedFactor = (259.0f * (contrastFactor + 255.0f)) / (255.0f * (259.0f - contrastFactor));

            int newRed = static_cast<int>(expectedFactor * (static_cast<float>(inputPixel.r) - 128.0f) + 128.0f);
            int newGreen = static_cast<int>(expectedFactor * (static_cast<float>(inputPixel.g) - 128.0f) + 128.0f);
            int newBlue = static_cast<int>(expectedFactor * (static_cast<float>(inputPixel.b) - 128.0f) + 128.0f);

            newRed = std::max(0, std::min(255, newRed));
            newGreen = std::max(0, std::min(255, newGreen));
            newBlue = std::max(0, std::min(255, newBlue));

            pixel = { static_cast<unsigned char>(newRed), static_cast<unsigned char>(newGreen), static_cast<unsigned char>(newBlue) };
        }
    }

    elementary::adjustContrast(img, contrastFactor);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img.getImgVec()));
}

TEST(ElementaryOperations, CreateNegativeTest)
{
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));

    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };

    Image img = Image(inputVec, 3);

    imgVec expectedVec(3, std::vector<Pixel>(3 * 2));

    expectedVec[0] = { {0, 255, 255}, {0, 0, 255} };
    expectedVec[1] = { {254, 127, 127}, {191, 191, 250} };
    expectedVec[2] = { {251, 250, 249}, {254, 253, 252} };

    elementary::createNegative(img);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img.getImgVec()));
}

