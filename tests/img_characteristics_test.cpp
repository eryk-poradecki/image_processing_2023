#include "ImageProc/Histogram.h"
#include "ImageProc/ImgCharacteristics.h"
#include "ImageProc/Types.h"
#include <cmath>
#include <cstddef>
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

TEST(CalculateVarianceTest, ValidInput)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
    inputVec[1] = { { 100, 50, 200 }, { 200, 150, 100 }, { 50, 100, 150 } };
    inputVec[2] = { { 150, 150, 150 }, { 150, 150, 150 }, { 150, 150, 150 } };

    Image testImage = Image(inputVec);

    auto [varR, varG, varB] = calculateVariance(testImage);

    float expectedMeanR = (255 + 100 + 150 + 200 + 150 + 50 + 150) / 9.0f, expectedVarR = 0.0f;
    float expectedMeanG = (50 + 150 + 255 + 150 + 150 + 100 + 150) / 9.0f, expectedVarG = 0.0f;
    float expectedMeanB = (200 + 150 + 100 + 150 + 255 + 150 + 150) / 9.0f, expectedVarB = 0.0f;

    for (size_t i = 0; i < inputVec[0].size(); ++i)
        for (size_t j = 0; j < inputVec[i].size(); ++j) {
            {
                expectedVarR += pow(inputVec[i][j][0] - expectedMeanR, 2);
                expectedVarG += pow(inputVec[i][j][1] - expectedMeanG, 2);
                expectedVarB += pow(inputVec[i][j][2] - expectedMeanB, 2);
            }
        }

    expectedVarR /= 9.0f;
    expectedVarG /= 9.0f;
    expectedVarB /= 9.0f;

    ASSERT_FLOAT_EQ(varR, expectedVarR);
    ASSERT_FLOAT_EQ(varG, expectedVarG);
    ASSERT_FLOAT_EQ(varB, expectedVarB);
}

TEST(CalculateStandardDeviationTest, ValidInput)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
    inputVec[1] = { { 100, 50, 200 }, { 200, 150, 100 }, { 50, 100, 150 } };
    inputVec[2] = { { 150, 150, 150 }, { 150, 150, 150 }, { 150, 150, 150 } };

    Image testImage = Image(inputVec);

    auto [stdDevR, stdDevG, stdDevB] = calculateStandardDeviation(testImage);

    float expectedMeanR = (255 + 100 + 150 + 200 + 150 + 50 + 150) / 9.0f, expectedVarR = 0.0f;
    float expectedMeanG = (50 + 150 + 255 + 150 + 150 + 100 + 150) / 9.0f, expectedVarG = 0.0f;
    float expectedMeanB = (200 + 150 + 100 + 150 + 255 + 150 + 150) / 9.0f, expectedVarB = 0.0f;

    for (size_t i = 0; i < inputVec[0].size(); ++i) {
        for (size_t j = 0; j < inputVec[i].size(); ++j) {
            expectedVarR += pow(inputVec[i][j][0] - expectedMeanR, 2);
            expectedVarG += pow(inputVec[i][j][1] - expectedMeanG, 2);
            expectedVarB += pow(inputVec[i][j][2] - expectedMeanB, 2);
        }
    }

    expectedVarR /= 9.0f;
    expectedVarG /= 9.0f;
    expectedVarB /= 9.0f;

    float expectedStdDevR = std::sqrt(expectedVarR);
    float expectedStdDevG = std::sqrt(expectedVarG);
    float expectedStdDevB = std::sqrt(expectedVarB);

    ASSERT_FLOAT_EQ(stdDevR, expectedStdDevR);
    ASSERT_FLOAT_EQ(stdDevG, expectedStdDevG);
    ASSERT_FLOAT_EQ(stdDevB, expectedStdDevB);
}

TEST(CalculateVariationCoefficientTest, ValidInput)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
    inputVec[1] = { { 100, 50, 200 }, { 200, 150, 100 }, { 50, 100, 150 } };
    inputVec[2] = { { 150, 150, 150 }, { 150, 150, 150 }, { 150, 150, 150 } };

    Image testImage = Image(inputVec);

    auto [varCoeffR, varCoeffG, varCoeffB] = calculateVariationCoefficientI(testImage);

    auto [meanR, meanG, meanB] = calculateMean(testImage);
    auto [stdDevR, stdDevG, stdDevB] = calculateStandardDeviation(testImage);

    float expectedVarCoeffR = stdDevR / meanR;
    float expectedVarCoeffG = stdDevG / meanG;
    float expectedVarCoeffB = stdDevB / meanB;

    ASSERT_FLOAT_EQ(varCoeffR, expectedVarCoeffR);
    ASSERT_FLOAT_EQ(varCoeffG, expectedVarCoeffG);
    ASSERT_FLOAT_EQ(varCoeffB, expectedVarCoeffB);
}

TEST(CalculateInformationSourceEntropyTest, ValidInput)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
    inputVec[1] = { { 100, 50, 200 }, { 200, 150, 100 }, { 50, 100, 150 } };
    inputVec[2] = { { 150, 150, 150 }, { 150, 150, 150 }, { 150, 150, 150 } };

    Image testImage = Image(inputVec);

    auto [infoSrcEntropyR, infoSrcEntropyG, infoSrcEntropyB] = calculateInformationSourceEntropy(testImage);

    float expectedInfoSrcEntropyR = 2.419382095;
    float expectedInfoSrcEntropyG = 2.058814048;
    float expectedInfoSrVarCoeffB = 2.058814048;

    float tolerance = 1e-6;
    ASSERT_NEAR(infoSrcEntropyR, expectedInfoSrcEntropyR, tolerance);
    ASSERT_NEAR(infoSrcEntropyG, expectedInfoSrcEntropyG, tolerance);
    ASSERT_NEAR(infoSrcEntropyB, expectedInfoSrVarCoeffB, tolerance);
}
