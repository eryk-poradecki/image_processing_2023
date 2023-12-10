#include <ImageProc/MorphologicalOperations.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <stack>

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

std::array<unsigned char, 3> generateRandomColor();

std::vector<ImageProc::imgVec> regionGrowing(const std::vector<std::pair<int, int>>& seedPointList, const ImageProc::imgVec& arrayImage)
{
    std::vector<ImageProc::imgVec> regions;

    auto seedPointListCopy(seedPointList);

    while (seedPointListCopy.size()) {

        std::vector<std::vector<std::vector<bool>>> visited(arrayImage.size(), std::vector<std::vector<bool>>(arrayImage[0].size(), std::vector<bool>(arrayImage[0][0].size(), false)));
        std::stack<std::pair<int, int>> stack;
        auto seedPoint = seedPointListCopy.back();
        seedPointListCopy.pop_back();
        stack.push(seedPoint);
        ImageProc::imgVec region(arrayImage.size(), std::vector<std::vector<unsigned char>>(arrayImage[0].size(), std::vector<unsigned char>(arrayImage[0][0].size(), 0)));
        auto [r, g, b] = generateRandomColor();
        while (!stack.empty()) {
            std::pair<int, int> currentPoint = stack.top();
            stack.pop();

            int currentRow = currentPoint.first;
            int currentCol = currentPoint.second;

            auto it = std::find(seedPointListCopy.begin(), seedPointListCopy.end(), currentPoint);
            // we dont want to process the same seed points twice, thats why if we find one, we delete it from list
            if (it != seedPointListCopy.end()) {
                seedPointListCopy.erase(it);
            }
            if (currentRow < 0 || currentRow >= arrayImage.size() || currentCol < 0 || currentCol >= arrayImage[0].size() || visited[currentRow][currentCol][0])
                continue;

            if (arrayImage[currentRow][currentCol][0] == arrayImage[seedPoint.first][seedPoint.second][0]) {
                region[currentRow][currentCol][0] = r;
                region[currentRow][currentCol][1] = g;
                region[currentRow][currentCol][2] = r;

                stack.push({ currentRow, currentCol + 1 });
                stack.push({ currentRow, currentCol - 1 });
                stack.push({ currentRow + 1, currentCol });
                stack.push({ currentRow - 1, currentCol });
            }

            visited[currentRow][currentCol][0] = true;
        }
        regions.push_back(region);
    }
    imgVec result;

    // sum all regions, they dont overlap so we won't get values bigger than 255
    for (const auto& img : regions) {
        if (result.empty()) {
            result = img;
        } else {
            for (std::size_t i = 0; i < img.size(); ++i) {
                for (std::size_t j = 0; j < img[i].size(); ++j) {
                    for (std::size_t k = 0; k < img[i][j].size(); ++k) {
                        result[i][j][k] += img[i][j][k];
                    }
                }
            }
        }
    }
    regions.push_back(result);
    return regions;
}
std::array<unsigned char, 3> generateRandomColor()
{
    std::array<unsigned char, 3> color;

    // Random number generator for each color component
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> distribution(0, 255);

    // Generating random values for red, green, and blue components
    color[0] = static_cast<unsigned char>(distribution(gen));
    color[1] = static_cast<unsigned char>(distribution(gen));
    color[2] = static_cast<unsigned char>(distribution(gen));

    return color;
}
}
