#include "ImageProc/Histogram.h"
#include "gtest/gtest.h"

using namespace ImageProc;

TEST(Histogram, CreateHistogramTest)
{

    constexpr int testBinSize = 256;
    constexpr int testChanSize = 3;
    histogram::Histogram<testBinSize, testChanSize> hist;
    ASSERT_EQ(testBinSize, hist.size());

    imgVec inputVec(3, std::vector<std::vector<unsigned char>>(2, std::vector<unsigned char>(3)));

    inputVec[0] = { { 255, 0, 0 }, { 255, 255, 0 } };
    inputVec[1] = { { 1, 128, 128 }, { 64, 64, 5 } };
    inputVec[2] = { { 4, 5, 6 }, { 1, 2, 3 } };

    Image img(inputVec);

    histogram::splitRGBImgToSaperateLayerRGB(img);
    std::array<histogram::Histogram<testBinSize, testChanSize>, testChanSize> histograms = hist.createHistogramFromImg(img);

    ASSERT_EQ(histograms.size(), testChanSize);

    ASSERT_EQ(2, histograms[0][255]);
    ASSERT_EQ(0, histograms[0][0]);
    ASSERT_EQ(1, histograms[0][4]);

    ASSERT_EQ(1, histograms[1][0]);
    ASSERT_EQ(0, histograms[1][1]);
}
