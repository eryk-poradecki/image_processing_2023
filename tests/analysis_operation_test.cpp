#include "ImageProc/ImgAnalysis.h"
#include "ImageProc/Types.h"
#include <cmath>
#include <gtest/gtest.h>

using namespace ImageProc;
using namespace analysis;

TEST(CalculateMSETest, ValidInput)
{
    // spectrum 3
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 3, 0, 4 }, { 5, 2, 0 } };
    inputVec[1] = { { 0, 0, 0 }, { 254, 9, 0 } };
    inputVec[2] = { { 0, 0, 0 }, { 0, 0, 1 } };

    int maxr = calculate_3DVecMax(inputVec, 0);
    int maxg = calculate_3DVecMax(inputVec, 1);
    int maxb = calculate_3DVecMax(inputVec, 2);
    ASSERT_EQ(maxr, 254);
    ASSERT_EQ(maxg, 9);
    ASSERT_EQ(maxb, 4);
}

// TEST(CalculatePSNRTest, ValidInput)
//{
//     imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));
//
//     inputVec[0] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     inputVec[1] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     inputVec[2] = { { 0, 0, 0 }, { 0, 0, 1 } };
//
//     imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));
//
//     expectedVec[0] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     expectedVec[1] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     expectedVec[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
//
//     Image img1 = Image(inputVec);
//
//     Image img2 = Image(expectedVec);
//
//     float expected = 10 * std::log10(1);
//     ASSERT_NO_THROW({
//         float actual = calculatePSNR(img1, img2);
//         float tolerance = 1e-6;
//         ASSERT_NEAR(actual, expected, tolerance);
//     });
// }
//
// TEST(CalculatePMSTest, ValidInput)
//{
//     imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));
//
//     inputVec[0] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     inputVec[1] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     inputVec[2] = { { 0, 0, 0 }, { 0, 0, 1 } };
//
//     imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));
//
//     expectedVec[0] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     expectedVec[1] = { { 0, 0, 0 }, { 0, 0, 0 } };
//     expectedVec[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
//
//     Image img1 = Image(inputVec);
//
//     Image img2 = Image(expectedVec);
//
//     float expected = (1.0 / 18) / (255 * 255);
//
//     ASSERT_NO_THROW({
//         float actual = calculatePMSE(img1, img2);
//         float tolerance = 1e-6;
//         ASSERT_NEAR(actual, expected, tolerance);
//     });
// }

TEST(CalculateMDTest, ValidInput)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 10, 0, 0 }, { 0, 0, 0 } };
    inputVec[1] = { { 0, 0, 0 }, { 0, 4, 0 } };
    inputVec[2] = { { 0, 0, 0 }, { 0, 0, 1 } };

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    expectedVec[0] = { { 4, 0, 0 }, { 0, 0, 0 } };
    expectedVec[1] = { { 0, 0, 0 }, { 0, 4, 0 } };
    expectedVec[2] = { { 0, 0, 0 }, { 0, 0, 0 } };

    Image img1 = Image(inputVec);

    Image img2 = Image(expectedVec);

    int expected = 6;

    auto [r, g, b] = calculateMD(img1, img2);

    ASSERT_EQ(r, 6);
    ASSERT_EQ(g, 0);
    ASSERT_EQ(b, 1);
}
