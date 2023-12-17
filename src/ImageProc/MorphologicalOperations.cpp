#include <ImageProc/MorphologicalOperations.h>
#include <algorithm>
#include <stack>

namespace ImageProc::morph {

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
    std::vector<ImageProc::imgVec> regions;
    for (size_t i = 0; i < seedPointList.size(); ++i) {
        regions.push_back(ImageProc::imgVec(arrayImage.size(), std::vector<std::vector<unsigned char>>(arrayImage[0].size(), std::vector<unsigned char>(arrayImage[0][0].size(), 0))));
    }

    for (size_t i = 0; i < seedPointList.size(); ++i) {
        std::vector<std::vector<std::vector<bool>>> visited(arrayImage.size(), std::vector<std::vector<bool>>(arrayImage[0].size(), std::vector<bool>(arrayImage[0][0].size(), false)));
        std::stack<std::pair<int, int>> stack;
        stack.push(seedPointList[i]);

        while (!stack.empty()) {
            std::pair<int, int> currentPoint = stack.top();
            stack.pop();

            int currentRow = currentPoint.first;
            int currentCol = currentPoint.second;

            if (currentRow < 0 || currentRow >= arrayImage.size() || currentCol < 0 || currentCol >= arrayImage[0].size() || visited[currentRow][currentCol][0])
                continue;

            if (arrayImage[currentRow][currentCol][0] == arrayImage[seedPointList[i].first][seedPointList[i].second][0]) {
                regions[i][currentRow][currentCol][0] = 255;

                stack.push({ currentRow, currentCol + 1 });
                stack.push({ currentRow, currentCol - 1 });
                stack.push({ currentRow + 1, currentCol });
                stack.push({ currentRow - 1, currentCol });
            }

            visited[currentRow][currentCol][0] = true;
        }
    }

    // Remove duplicate regions
    regions.erase(std::unique(regions.begin(), regions.end()), regions.end());

    return regions;
}

}
