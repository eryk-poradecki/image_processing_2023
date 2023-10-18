#include "NoiseRemoval.h"
#include "Types.h"
#include "iostream"
#include <algorithm>
#include <array>
#include <vector>

namespace ImageProc {

namespace noise {

    std::array<unsigned char, 3> getFirstMedianLast(std::vector<unsigned char>& values)
    {
        size_t n = values.size();
        std::sort(values.begin(), values.end());
        unsigned char first = values.front();
        unsigned char last = values.back();
        unsigned char median;
        if (n % 2 == 0) {
            median = (values[n / 2 - 1] + values[n / 2]) / 2;
        } else {
            median = values[n / 2];
        }
        return { first, median, last };
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

                    std::vector<unsigned char> windowValuesR(currentWindow + 1);
                    std::vector<unsigned char> windowValuesG(currentWindow + 1);
                    std::vector<unsigned char> windowValuesB(currentWindow + 1);

                    for (int i = startX; i <= endX; ++i) {
                        for (int j = startY; j <= endY; ++j) {
                            windowValuesR.push_back(originalVec[j][i][0]);
                            windowValuesG.push_back(originalVec[j][i][1]);
                            windowValuesB.push_back(originalVec[j][i][2]);
                        }
                    }

                    auto resultR = getFirstMedianLast(windowValuesR);
                    unsigned char zminR = resultR[0];
                    int zmedR = resultR[1];
                    unsigned char zmaxR = resultR[2];

                    auto resultG = getFirstMedianLast(windowValuesG);
                    unsigned char zminG = resultG[0];
                    int zmedG = resultG[1];
                    unsigned char zmaxG = resultG[2];

                    auto resultB = getFirstMedianLast(windowValuesB);
                    unsigned char zminB = resultB[0];
                    int zmedB = resultB[1];
                    unsigned char zmaxB = resultB[2];

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
