#include "ImageProc/Histogram.h"
#include "ImageProc/ImgCharacteristics.h"
#include "ImageProc/Types.h"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

using namespace ImageProc;
using namespace characteristics;

TEST(CalculateMeanTest, ValidInput)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
    inputVec[1] = { { 100, 50, 200 }, { 200, 150, 100 }, { 50, 100, 150 } };
    inputVec[2] = { { 150, 150, 150 }, { 150, 150, 150 }, { 150, 150, 150 } };

    Image testImage = Image(inputVec);

    auto [meanR, meanG, meanB] = calculateMean(testImage);
    float expectedMeanR = (255 + 100 + 150 + 200 + 150 + 50 + 150) / 9.0f;
    float expectedMeanG = (50 + 150 + 255 + 150 + 150 + 100 + 150) / 9.0f;
    float expectedMeanB = (200 + 150 + 100 + 150 + 255 + 150 + 150) / 9.0f;
    ASSERT_FLOAT_EQ(meanR, expectedMeanR);
    ASSERT_FLOAT_EQ(meanG, expectedMeanG);
    ASSERT_FLOAT_EQ(meanB, expectedMeanB);
}
