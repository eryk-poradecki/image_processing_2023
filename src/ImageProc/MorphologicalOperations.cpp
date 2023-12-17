#include "ImageProc/Types.h"
#include <ImageProc/Histogram.h>
#include <ImageProc/MorphologicalOperations.h>
#include <algorithm>
#include <array>
#include <random>
#include <stack>

namespace ImageProc::morph {
imgVec mergeRegion(imgVec img, std::array<unsigned char, 3> rgb, std::pair<int, int> point);

int clipPixel(int value, int minValue, int maxValue)
{
    return std::max(minValue, std::min(value, maxValue));
}

// this fucn works only for 1 bit image
imgVec morph(Image& inImage, const std::vector<std::vector<unsigned char>>& kernel, const std::string& type)
{
    int sz = (kernel.size() - 1) / 2;

    auto img = inImage.getImgVec();
    // we can use copy for output cuz we go through all pixels

    auto outImage(img);
    for (int x = 0; x < img.size(); ++x) {
        for (int y = 0; y < img[0].size(); ++y) {
            unsigned char val;

            if (x - sz < 0 || x + sz >= img.size() || y - sz < 0 || y + sz >= img[0].size()) {
                val = img[x][y][0];
            } else {
                std::vector<unsigned char> list;

                for (int i = 0; i < kernel.size(); ++i) {
                    for (int j = 0; j < kernel[i].size(); ++j) {
                        if (kernel[i][j] == 1) {
                            list.push_back(img[x + i - sz][y + j - sz][0]);
                        }
                    }
                }

                if (type == "dilation") {
                    // this max function works as OR operator, if there is 1 in the list it will return 1
                    val = *std::max_element(list.begin(), list.end());
                } else if (type == "erosion") {
                    // this min function works as AND operator, all values in the list must be 1, otherwise 0
                    val = *std::min_element(list.begin(), list.end());
                }
            }

            outImage[x][y][0] = val;
        }
    }
    return outImage;
}

imgVec opening(Image& img, const std::vector<std::vector<unsigned char>>& kernel)
{
    imgVec erodedImg = morph(img, kernel, "erosion");
    Image erodedImage(erodedImg);
    imgVec openedImg = morph(erodedImage, kernel, "dilation");
    return openedImg;
}

imgVec closing(Image& img, const std::vector<std::vector<unsigned char>>& kernel)
{
    imgVec dilatedImg = morph(img, kernel, "dilation");
    Image dilatedImage(dilatedImg);
    imgVec closedImg = morph(dilatedImage, kernel, "erosion");

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

// ImageProc::imgVec operationM1(ImageProc::Image& img)
//{
//     // (A dilation B) / A
//     imgVec dilatedImg = dilation(img);
//     imgVec resultImg1 = elementwiseDivision(dilatedImg, img.getImgVec());
//     Image resultImage1(resultImg1);
//
//     // A / (A erosion B)
//     imgVec erodedImg = erosion(resultImage1);
//     imgVec resultImg2 = elementwiseDivision(resultImg1, erodedImg);
//     Image resultImage2(resultImg2);
//
//     // (A dilation B) / (A erosion B)
//     dilatedImg = dilation(resultImage2);
//     erodedImg = erosion(resultImage2);
//     imgVec resultImg3 = elementwiseDivision(dilatedImg, erodedImg);
//
//     return resultImg3;
// }

std::array<unsigned char, 3> generateRandomColor();

imgVec hitOrMissTransformation(Image& img)
{
    int height = img.getHeight();
    int width = img.getWidth();
    int spectrum = img.getSpectrum();

    imgVec& inputImgVec = img.getImgVec();
    imgVec resultImg(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum, 0)));

    std::vector<std::vector<int>> hitKernel = {
        { 0, 1, 0 },
        { 1, 0, 1 },
        { 0, 1, 0 }
    };

    std::vector<std::vector<int>> missKernel = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    int kernelSize = hitKernel.size();

    int padding = kernelSize / 2;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < spectrum; ++k) {
                bool hit = true;

                // hit condition
                for (int m = -padding; m <= padding; ++m) {
                    for (int n = -padding; n <= padding; ++n) {
                        int row = i + m;
                        int col = j + n;

                        // padding value if not within bounds
                        if (row >= 0 && row < height && col >= 0 && col < width) {
                            if (hitKernel[m + padding][n + padding] == 1) {
                                hit = hit && (inputImgVec[row][col][k] == 255);
                            }
                        }
                    }
                }

                // miss condition
                for (int m = -padding; m <= padding; ++m) {
                    for (int n = -padding; n <= padding; ++n) {
                        int row = i + m;
                        int col = j + n;

                        // padding value if not within bounds
                        if (row >= 0 && row < height && col >= 0 && col < width) {
                            if (missKernel[m + padding][n + padding] == 1) {
                                hit = hit && (inputImgVec[row][col][k] == 0);
                            }
                        }
                    }
                }

                resultImg[i][j][k] = (hit) ? 255 : 0;
            }
        }
    }

    return resultImg;
}

// add joining regions at the end, count neighbours, if more than visited, join 2 larger regions
std::vector<ImageProc::imgVec> regionGrowing(const std::vector<std::pair<int, int>>& seedPointList, const ImageProc::imgVec& arrayImage)
{
    auto arrayImage = img.getImgVec();
    std::vector<ImageProc::imgVec> regions;
    histogram::Histogram<histogram::NUM_BINS, 3> histogram;
    auto histograms = histogram.createHistogramFromImg(img);

    int intensityThreshold = std::numeric_limits<int>::max();

    for (int channel = 0; channel < img.getSpectrum(); ++channel) {
        auto intensityRange = histogram.computeIntensityRange(histograms[channel].getArr());
        int channelThreshold = std::min(intensityRange.first, intensityRange.second);
        intensityThreshold = std::min(intensityThreshold, channelThreshold);
    }

    auto seedPointListCopy(seedPointList);

    while (seedPointListCopy.size()) {

        std::vector<std::vector<std::vector<bool>>> visited(arrayImage.size(), std::vector<std::vector<bool>>(arrayImage[0].size(), std::vector<bool>(1, false)));

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

            if (currentRow < 0 || currentRow >= arrayImage.size() || currentCol < 0 || currentCol >= arrayImage[0].size() || visited[currentRow][currentCol][0])
                continue;
            if (img.getSpectrum() == 1) {
                if (std::abs(arrayImage[currentRow][currentCol][0] - arrayImage[seedPoint.first][seedPoint.second][0]) <= intensityThreshold) {
                    region[currentRow][currentCol][0] = r;

                    stack.push({ currentRow, currentCol + 1 });
                    stack.push({ currentRow, currentCol - 1 });
                    stack.push({ currentRow + 1, currentCol });
                    stack.push({ currentRow - 1, currentCol });
            }
            } else if (std::abs(arrayImage[currentRow][currentCol][0] - arrayImage[seedPoint.first][seedPoint.second][0]) <= intensityThreshold &&
            std::abs(arrayImage[currentRow][currentCol][1] - arrayImage[seedPoint.first][seedPoint.second][1]) <= intensityThreshold &&
            std::abs(arrayImage[currentRow][currentCol][2] - arrayImage[seedPoint.first][seedPoint.second][2]) <= intensityThreshold) {
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

    for (const auto& img : regions) {
        if (result.empty()) {
            result = img;
            continue;
        } else {
            for (std::size_t i = 0; i < img.size(); ++i) {
                for (std::size_t j = 0; j < img[i].size(); ++j) {
                    unsigned char r = img[i][j][0];
                    unsigned char g = img[i][j][1];
                    unsigned char b = img[i][j][2];
                    if (r + g + b) {
                        if (result[i][j][0] != r && result[i][j][1] != g && result[i][j][2] != b) {
                            if (result[i][j][0] + result[i][j][1] + result[i][j][2]) {
                                std::array<unsigned char, 3> rgb { r, g, b };
                                result = mergeRegion(result, rgb, std::make_pair(i, j));

                            } else {
                                result[i][j][0] = r;
                                result[i][j][1] = g;
                                result[i][j][2] = b;
                            }
                        }
                    }
                }
            }
        }
    }
    regions.push_back(result);
    return regions;
}

/* imgVec mergeRegion(imgVec img, const std::array<unsigned char, 3> rgb, const std::pair<int, int> point) */
/* { */
/*     // Get the color at the specified point */
/*     unsigned char targetR = img[point.first][point.second][0]; */
/*     unsigned char targetG = img[point.first][point.second][1]; */
/*     unsigned char targetB = img[point.first][point.second][2]; */
/*     std::cout << targetR << " " << targetG << "  " << targetB; */
/*     // Iterate through the image and change pixels that match the target color */
/*     for (size_t i = 0; i < img.size(); ++i) { */
/*         for (size_t j = 0; j < img[i].size(); ++j) { */
/*             if (img[i][j][0] == targetR && img[i][j][1] == targetG && img[i][j][2] == targetB) { */
/*                 // Change the pixel color to the specified RGB value */
/*                 img[i][j][0] = rgb[0]; */
/*                 img[i][j][1] = rgb[1]; */
/*                 img[i][j][2] = rgb[2]; */
/*             } */
/*         } */
/*     } */
/*     return img; */
/* } */
/**/
imgVec mergeRegion(imgVec img, std::array<unsigned char, 3> rgb, std::pair<int, int> point)
{
    std::stack<std::pair<int, int>> stack;
    stack.push(point);

    unsigned char toChangeColorR = img[point.first][point.second][0];
    unsigned char toChangeColorG = img[point.first][point.second][1];
    unsigned char toChangeColorB = img[point.first][point.second][2];

    unsigned char targetColorR = rgb[0];
    unsigned char targetColorG = rgb[1];
    unsigned char targetColorB = rgb[2];

    std::vector<std::vector<std::vector<bool>>> visited(img.size(), std::vector<std::vector<bool>>(img[0].size(), std::vector<bool>(1, false)));
    while (!stack.empty()) {
        std::pair<int, int> currentPoint = stack.top();
        stack.pop();

        int currentRow = currentPoint.first;
        int currentCol = currentPoint.second;

        if (currentRow < 0 || currentRow >= img.size() || currentCol < 0 || currentCol >= img[0].size() || visited[currentRow][currentCol][0])
            continue;

        if (img[currentRow][currentCol][0] == toChangeColorR && img[currentRow][currentCol][1] == toChangeColorG && img[currentRow][currentCol][2] == toChangeColorB) {
            img[currentRow][currentCol][0] = targetColorR;
            img[currentRow][currentCol][1] = targetColorG;
            img[currentRow][currentCol][2] = targetColorB;

            stack.push({ currentRow, currentCol + 1 });
            stack.push({ currentRow, currentCol - 1 });
            stack.push({ currentRow + 1, currentCol });
            stack.push({ currentRow - 1, currentCol });
        }

        visited[currentRow][currentCol][0] = true;
    }
    return img;
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
