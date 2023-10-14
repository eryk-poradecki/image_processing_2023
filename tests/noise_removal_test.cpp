#include "ImageProc/NoiseRemoval.h"
#include "ImageProc/Types.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace ImageProc;

TEST(NoiseRemoval, AdaptiveMedianFilterTest) {
    int minFilterSize = 3;
    int maxFilterSize = 7;
    
    imgVec testImage = { 
        { {100, 120, 150}, {110, 130, 140}, {90, 115, 155} },
        { {115, 125, 145}, {105, 135, 130}, {95, 120, 160} },
        { {105, 140, 135}, {100, 130, 125}, {85, 110, 150} }
    };
    
    Image testImg(testImage);

    imgVec filteredImage = noise::adaptiveMedianFilter(testImg, minFilterSize, maxFilterSize);

    ASSERT_EQ(filteredImage.size(), testImage.size());
    ASSERT_EQ(filteredImage[0].size(), testImage[0].size());
    ASSERT_EQ(filteredImage[0][0].size(), testImage[0][0].size());

    ASSERT_EQ(filteredImage[1][1][0], 105); 
    ASSERT_EQ(filteredImage[1][1][1], 135); 
    ASSERT_EQ(filteredImage[1][1][2], 130); 
}