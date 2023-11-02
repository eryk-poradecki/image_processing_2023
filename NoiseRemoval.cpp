#include "NoiseRemoval.h"
#include "Types.h"
#include "iostream"
#include <algorithm>
#include <array>
#include <vector>

namespace ImageProc {

namespace noise {

    std::tuple<unsigned char, unsigned char, unsigned char> getFirstMedianLast(std::vector<unsigned char>& values, int size)
    {
        std::sort(values.begin(), values.begin() + size);
        unsigned char first = values[0];
        unsigned char last = values[size];
        unsigned char median;
        if (size % 2 == 0) {
            median = (values[size / 2 - 1] + values[size / 2]) / 2;
        } else {
            median = values[size / 2];
        }
        return std::make_tuple(first, median, last);
    }

    imgVec adaptiveMedianFilter(Image& image, int minFilterSize, int maxFilterSize)
    {
        int width = image.getWidth();
        int height = image.getHeight();
        int spectrum = image.getSpectrum();
        imgVec& originalVec = image.getImgVec();

        imgVec outputImgVec(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum)));

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                int currentWindow = minFilterSize;
                while (currentWindow <= maxFilterSize) {
                    int startX = std::max(0, x - currentWindow / 2);
                    int startY = std::max(0, y - currentWindow / 2);
                    int endX = std::min(width - 1, x + currentWindow / 2);
                    int endY = std::min(height - 1, y + currentWindow / 2);

                    std::vector<unsigned char> windowValuesR;
                    std::vector<unsigned char> windowValuesG;
                    std::vector<unsigned char> windowValuesB;

                    int counter = 0;
                    for (int i = startX; i <= endX; ++i) {
                        for (int j = startY; j <= endY; ++j) {
                            windowValuesR.push_back(originalVec[j][i][0]);
                            windowValuesG.push_back(originalVec[j][i][1]);
                            windowValuesB.push_back(originalVec[j][i][2]);
                            ++counter;
                        }
                    }
                    --counter;

                    auto [zminR, zmedR, zmaxR] = getFirstMedianLast(windowValuesR, counter);

                    auto [zminG, zmedG, zmaxG] = getFirstMedianLast(windowValuesG, counter);

                    auto [zminB, zmedB, zmaxB] = getFirstMedianLast(windowValuesG, counter);

                    int zxyR = originalVec[y][x][0];
                    int zxyG = originalVec[y][x][1];
                    int zxyB = originalVec[y][x][2];

                    int A1R = zmedR - zminR;
                    int A2R = zmedR - zmaxR;
                    int A1G = zmedG - zminG;
                    int A2G = zmedG - zmaxG;
                    int A1B = zmedB - zminB;
                    int A2B = zmedB - zmaxB;

                    if ((A1R > 0 && A2R < 0) && (A1G > 0 && A2G < 0) && (A1B > 0 && A2B < 0)) {
                        int B1R = zxyR - zminR;
                        int B2R = zxyR - zmaxR;
                        int B1G = zxyG - zminG;
                        int B2G = zxyG - zmaxG;
                        int B1B = zxyB - zminB;
                        int B2B = zxyB - zmaxB;

                        if ((B1R > 0 && B2R < 0) && (B1G > 0 && B2G < 0) && (B1B > 0 && B2B < 0)) {
                            outputImgVec[y][x][0] = zxyR;
                            outputImgVec[y][x][1] = zxyG;
                            outputImgVec[y][x][2] = zxyB;
                        } else {
                            outputImgVec[y][x][0] = zmedR;
                            outputImgVec[y][x][1] = zmedG;
                            outputImgVec[y][x][2] = zmedB;
                        }
                        break;
                    }
                    currentWindow++;

                    if (currentWindow > maxFilterSize) {
                        outputImgVec[y][x][0] = zxyR;
                        outputImgVec[y][x][1] = zxyG;
                        outputImgVec[y][x][2] = zxyB;
                        break;
                    }
                }
            }
        }

        return outputImgVec;
    }
}
}
