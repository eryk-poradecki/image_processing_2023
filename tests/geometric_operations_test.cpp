#include "ImageProc/Types.h"
#include <iostream>

#include "helpers.hpp"
#include "gtest/gtest.h"
#include <ImageProc/GeometricOperations.h>
#include <vector>

using namespace ImageProc;


TEST(GeometricOperations, HorizontalFlipTest) {
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));

    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };

    Image img(inputVec, 3);

    imgVec expectedVec(3, std::vector<Pixel>(3 * 2));
    expectedVec[0] = { {4, 5, 6}, {1, 2, 3} };
    expectedVec[1] = { {1, 128, 128}, {64, 64, 5} };
    expectedVec[2] = { {255, 0, 0}, {255, 255, 0} };

    geometric::horizontalFlip(img);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img.getImgVec()));
}

TEST(GeometricOperations, VerticalFlipTest) {
    imgVec inputVec(3, std::vector<Pixel>(3 * 2));

    inputVec[0] = { {255, 0, 0}, {255, 255, 0} };
    inputVec[1] = { {1, 128, 128}, {64, 64, 5} };
    inputVec[2] = { {4, 5, 6}, {1, 2, 3} };

    Image img(inputVec, 3);

    imgVec expectedVec(3, std::vector<Pixel>(3 * 2));
    expectedVec[0] = { {255, 255, 0}, {255, 0, 0} };
    expectedVec[1] = { {64, 64, 5}, {1, 128, 128} };
    expectedVec[2] = { {1, 2, 3}, {4, 5, 6} };

    geometric::verticalFlip(img);

    EXPECT_TRUE(areImageVectorsEqual(expectedVec, img.getImgVec()));
}
