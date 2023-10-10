#include "ImageProc/ImgAnalysis.h"
#include "ImageProc/Types.h"
#include <gtest/gtest.h>

using namespace ImageProc;
using namespace analysis;

TEST(CalculateMSETest, ValidInput)
{
    imgVec inputVec(2, std::vector<unsigned char>(2));

    inputVec[0] = { 1, 5 };
    inputVec[1] = { 4, 4 };

    imgVec testVec(2, std::vector<unsigned char>(2));

    testVec[0] = { 0, 5 };
    testVec[1] = { 4, 4 };

    Image img1 = Image(inputVec, 1);

    Image img2 = Image(testVec, 1);
    ;

    float expected = 0.25;
    ASSERT_NO_THROW({
        float actual = calculateMSE(img1, img2);
        double tolerance = 1e-6;
        ASSERT_NEAR(expected, actual, tolerance);
    });
}

TEST(CalculatePSNRTest, ValidInput)
{
    imgVec inputVec(2, std::vector<unsigned char>(2));

    inputVec[0] = { 1, 5 };
    inputVec[1] = { 4, 4 };

    imgVec testVec(2, std::vector<unsigned char>(2));

    testVec[0] = { 0, 5 };
    testVec[1] = { 4, 4 };

    Image img1 = Image(inputVec, 1);

    Image img2 = Image(testVec, 1);

    float expected = 54.1514;

    ASSERT_NO_THROW({
        float actual = calculatePSNR(img1, img2);
        float tolerance = 1e-6;
        ASSERT_NEAR(actual, expected, tolerance);
    });
}

TEST(CalculatePMSTest, ValidInput)
{
    imgVec inputVec(2, std::vector<unsigned char>(2));

    inputVec[0] = { 1, 0 };
    inputVec[1] = { 4, 4 };

    imgVec testVec(2, std::vector<unsigned char>(2));

    testVec[0] = { 0, 5 };
    testVec[1] = { 4, 4 };

    Image img1 = Image(inputVec, 1);

    Image img2 = Image(testVec, 1);

    float expected = 25;

    ASSERT_NO_THROW({
        float actual = calculatePMS(img1, img2);
        float tolerance = 1e-6;
        ASSERT_NEAR(actual, expected, tolerance);
    });
}