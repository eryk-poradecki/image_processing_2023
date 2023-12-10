#include <ImageProc/MorphologicalOperations.h>
#include <queue>
#include <unordered_set>

namespace ImageProc::morph {

int clipPixel(int value, int minValue, int maxValue)
{
    return std::max(minValue, std::min(value, maxValue));
}

imgVec dilation(Image& img)
{
    int height = img.getHeight();
    int width = img.getWidth();
    int spectrum = img.getSpectrum();

    imgVec& inputImgVec = img.getImgVec();
    imgVec resultImg(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum, 0)));

    // Hardcoded kernel for dilation
    std::vector<std::vector<int>> kernel = {
        { 1, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    };

    int kernelSize = kernel.size();

    // Padding size to handle corners
    int padding = kernelSize / 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < spectrum; ++k) {
                unsigned char maxVal = 0;
                for (int m = -padding; m <= padding; ++m) {
                    for (int n = -padding; n <= padding; ++n) {
                        int row = i + m;
                        int col = j + n;

                        // Check if within bounds, otherwise consider it as a padding value
                        if (row >= 0 && row < height && col >= 0 && col < width) {
                            if (kernel[m + padding][n + padding] == 1) {
                                maxVal = std::max(maxVal, static_cast<unsigned char>(inputImgVec[row][col][k] * kernel[m + padding][n + padding]));
                            }
                        }
                    }
                }
                resultImg[i][j][k] = maxVal;
            }
        }
    }

    return resultImg;
}

imgVec erosion(Image& img)
{
    int height = img.getHeight();
    int width = img.getWidth();
    int spectrum = img.getSpectrum();

    imgVec& inputImgVec = img.getImgVec();
    imgVec resultImg(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum, 255))); // Initializing with maximum value

    // Hardcoded kernel for erosion
    std::vector<std::vector<int>> kernel = {
        { 1, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    };

    int kernelSize = kernel.size();

    // Padding size to handle corners
    int padding = kernelSize / 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < spectrum; ++k) {
                unsigned char minVal = 255; // Initializing with maximum value
                bool performErosion = true;
                for (int m = -padding; m <= padding; ++m) {
                    for (int n = -padding; n <= padding; ++n) {
                        int row = i + m;
                        int col = j + n;

                        // Check if within bounds, otherwise consider it as a padding value
                        if (row >= 0 && row < height && col >= 0 && col < width) {
                            if (kernel[m + padding][n + padding] == 1) {
                                minVal = std::min(minVal, static_cast<unsigned char>(inputImgVec[row][col][k] * kernel[m + padding][n + padding]));
                            }
                        } else {
                            // If any part of the kernel extends outside the image, erosion cannot be performed at this point
                            performErosion = false;
                        }
                    }
                }
                if (performErosion) {
                    resultImg[i][j][k] = minVal;
                }
            }
        }
    }

    return resultImg;
}

imgVec opening(Image& img)
{
    imgVec erodedImg = erosion(img);
    Image erodedImage(erodedImg);
    imgVec openedImg = dilation(erodedImage);

    return openedImg;
}

imgVec closing(Image& img)
{
    imgVec dilatedImg = dilation(img);
    Image dilatedImage(dilatedImg);
    imgVec closedImg = erosion(dilatedImage);

    return closedImg;
}

ImageProc::imgVec elementwiseDivision(const imgVec& img1, const imgVec& img2)
{
    int height = img1.size();
    int width = img1[0].size();
    int spectrum = img1[0][0].size();

    imgVec resultImg(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum, 0)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < spectrum; ++k) {

                if (img2[i][j][k] != 0) {
                    resultImg[i][j][k] = static_cast<unsigned char>(img1[i][j][k] / img2[i][j][k]);
                } else {
                    resultImg[i][j][k] = 255;
                }
            }
        }
    }
    return resultImg;
}

ImageProc::imgVec operationM1(ImageProc::Image& img)
{
    // (A dilation B) / A
    imgVec dilatedImg = dilation(img);
    imgVec resultImg1 = elementwiseDivision(dilatedImg, img.getImgVec());
    Image resultImage1(resultImg1);

    // A / (A erosion B)
    imgVec erodedImg = erosion(resultImage1);
    imgVec resultImg2 = elementwiseDivision(resultImg1, erodedImg);
    Image resultImage2(resultImg2);

    // (A dilation B) / (A erosion B)
    dilatedImg = dilation(resultImage2);
    erodedImg = erosion(resultImage2);
    imgVec resultImg3 = elementwiseDivision(dilatedImg, erodedImg);

    return resultImg3;
}

std::vector<ImageProc::imgVec> regionGrowing(const std::vector<std::pair<int, int>>& seedPointList, const ImageProc::imgVec& arrayImage)
{
    std::vector<ImageProc::imgVec> regions;
    for (size_t i = 0; i < seedPointList.size(); ++i) {
        regions.push_back(ImageProc::imgVec(arrayImage.size(), std::vector<std::vector<unsigned char>>(arrayImage[0].size(), std::vector<unsigned char>(arrayImage[0][0].size(), 0))));
    }

    for (size_t i = 0; i < seedPointList.size(); ++i) {
        std::vector<std::vector<std::vector<bool>>> visited(arrayImage.size(), std::vector<std::vector<bool>>(arrayImage[0].size(), std::vector<bool>(arrayImage[0][0].size(), false)));
        std::vector<std::pair<int, int>> stack = {seedPointList[i]};

        while (!stack.empty()) {
            std::pair<int, int> currentPoint = stack.back();
            stack.pop_back();

            if (!visited[currentPoint.first][currentPoint.second][0]) {
                if (arrayImage[currentPoint.first][currentPoint.second][0] == arrayImage[seedPointList[i].first][seedPointList[i].second][0]) {
                    regions[i][currentPoint.first][currentPoint.second][0] = 255;

                    if (currentPoint.second + 1 < arrayImage[0].size()) {
                        stack.push_back({currentPoint.first, currentPoint.second + 1});
                    }
                    if (currentPoint.second > 0) {
                        stack.push_back({currentPoint.first, currentPoint.second - 1});
                    }
                    if (currentPoint.first + 1 < arrayImage.size()) {
                        stack.push_back({currentPoint.first + 1, currentPoint.second});
                    }
                    if (currentPoint.first > 0) {
                        stack.push_back({currentPoint.first - 1, currentPoint.second});
                    }
                }

                visited[currentPoint.first][currentPoint.second][0] = true;
            }
        }
    }

    // remove duplicate regions
    regions.erase(std::unique(regions.begin(), regions.end()), regions.end());

    return regions;
}
}
