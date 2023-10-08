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
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    expectedVec[0] = { { 255, 10, 10 }, { 255, 255, 10 } };
    expectedVec[1] = { { 11, 138, 138 }, { 74, 74, 15 } };
    expectedVec[2] = { { 14, 15, 16 }, { 11, 12, 13 } };

    Image img3(inputVec);

    elementary::adjustBrightness(img3, 10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    inputVec[0] = { {255}, {0}, {0}, {255}, {255}, {0} };
    inputVec[1] = { {1}, {128}, {128}, {64}, {64}, {5} };
    inputVec[2] = { {4}, {5}, {6}, {1}, {2}, {3} };

    Image img1(inputVec);

    expectedVec[0] = { { 255 }, { 10 }, { 10 }, { 255 }, { 255 }, { 10 } };
    expectedVec[1] = { { 11 }, { 138 }, { 138 }, { 74 }, { 74 }, { 15 } };
    expectedVec[2] = { { 14 }, { 15 }, { 16 }, { 11 }, { 12 }, { 13 } };

    elementary::adjustBrightness(img1, 10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img1.getImgVec()));
}


TEST(ElementaryOperations, AdjustNegativeBrightnessWithDiffSpectrumTest)
{
    //=================================================
    // spectrum 3
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    expectedVec[0] = { { 245, 0, 0 }, { 245, 245, 0 } };
    expectedVec[1] = { { 0, 118, 118 }, { 54, 54, 0 } };
    expectedVec[2] = { { 0, 0, 0 }, { 0, 0, 0 } };

    Image img3(inputVec);

    elementary::adjustBrightness(img3, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    inputVec[0] = { {255}, {0}, {0}, {255}, {255}, {0} };
    inputVec[1] = { {1}, {128}, {128}, {64}, {64}, {5} };
    inputVec[2] = { {4}, {5}, {6}, {1}, {2}, {3} };

    Image img1(inputVec);

    expectedVec[0] = { { 245 }, { 0 }, { 0 }, { 245 }, { 245 }, { 0 } };
    expectedVec[1] = { { 0 }, { 118 }, { 118 }, { 54 }, { 54 }, { 0 } };
    expectedVec[2] = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };


    elementary::adjustBrightness(img1, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img1.getImgVec()));
}

TEST(ElementaryOperations, AdjustConstrastWithDiffSpectrumTest)
{
    //=================================================
    // spectrum 3
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    expectedVec[0] = { { 255, 10, 10 }, { 255, 255, 10 } };
    expectedVec[1] = { { 11, 138, 138 }, { 74, 74, 15 } };
    expectedVec[2] = { { 14, 15, 16 }, { 11, 12, 13 } };

    Image img3(inputVec);

    elementary::adjustBrightness(img3, 10);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img3.getImgVec()));

    //=================================================
    // spectrum 1

    imgVec inputVec1(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec1[0] = { {255}, {0}, {0}, {255}, {255}, {0} };
    inputVec1[1] = { {1}, {128}, {128}, {64}, {64}, {5} };
    inputVec1[2] = { {4}, {5}, {6}, {1}, {2}, {3} };

    imgVec expectedVec1(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    expectedVec1[0] = { {245}, {0}, {0}, {245}, {245}, {0} };
    expectedVec1[1] = { {0}, {118}, {118}, {54}, {54}, {0} };
    expectedVec1[2] = { {0}, {0}, {0}, {0}, {0}, {0} };

    Image img1(inputVec1);
    elementary::adjustBrightness(img1, -10);

    EXPECT_TRUE(areVectorsEqual(expectedVec1, img1.getImgVec()));
}

TEST(ElementaryOperations, CreateNegativeTest)
{
    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    Image img(inputVec);

    imgVec expectedVec(3, std::vector<std::vector<unsigned char>>(3 * 2, std::vector<unsigned char>(3)));

    expectedVec[0] = { { 0, 255, 255 }, { 0, 0, 255 } };
    expectedVec[1] = { { 254, 127, 127 }, { 191, 191, 250 } };
    expectedVec[2] = { { 251, 250, 249 }, { 254, 253, 252 } };

    elementary::createNegative(img);

    EXPECT_TRUE(areVectorsEqual(expectedVec, img.getImgVec()));
}
