#include "GeometricOperations.h"
#include "Types.h"
#include <algorithm>

namespace ImageProc::geometric {

void horizontalFlip(Image& image)
{
    imgVec& imgMatrix = image.getImgVec();

    std::reverse(imgMatrix.begin(), imgMatrix.end());
}

void verticalFlip(Image& image)
{
    imgVec& imgMatrix = image.getImgVec();
    for (auto& row : imgMatrix) {
        std::reverse(row.begin(), row.end());
    }
}

void diagonalFlip(Image& image)
{
    imgVec& imgMatrix = image.getImgVec();
    for (auto& row : imgMatrix) {
        std::reverse(row.begin(), row.end());
    }

    std::reverse(imgMatrix.begin(), imgMatrix.end());
}

imgVec shrinkImage(const Image& image, int shrinkFactor)
{
    int originalWidth = image.getWidth();
    int originalHeight = image.getHeight();
    int originalSpectrum = image.getSpectrum();

    int newWidth = originalWidth / shrinkFactor;
    int newHeight = originalHeight / shrinkFactor;

    imgVec newImgMatrix(newHeight, std::vector<std::vector<unsigned char>>(newWidth, std::vector<unsigned char>(originalSpectrum, 0)));
    auto inputImgVec = image.getImgVec();
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int startX = x * shrinkFactor;
            int startY = y * shrinkFactor;

            std::vector<unsigned int> sumPixel(originalSpectrum, 0);
            for (int i = 0; i < shrinkFactor; ++i) {
                for (int j = 0; j < shrinkFactor; ++j) {
                    for (int c = 0; c < originalSpectrum; ++c) {
                        sumPixel[c] += inputImgVec[startY + i][startX + j][c];
                    }
                }
            }

            for (int c = 0; c < originalSpectrum; ++c) {
                newImgMatrix[y][x][c] = static_cast<unsigned char>(sumPixel[c] / (shrinkFactor * shrinkFactor));
            }
        }
    }

    return newImgMatrix;
}

imgVec enlargeImage(const Image& image, int enlargeFactor)
{
    int originalWidth = image.getWidth();
    int originalHeight = image.getHeight();
    int originalSpectrum = image.getSpectrum();

    int newWidth = originalWidth * enlargeFactor;
    int newHeight = originalHeight * enlargeFactor;

    imgVec newImgMatrix(newHeight, std::vector<std::vector<unsigned char>>(newWidth, std::vector<unsigned char>(originalSpectrum, 0)));
    auto inputImgVec = image.getImgVec();
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int originalX = x / enlargeFactor;
            int originalY = y / enlargeFactor;

            for (int c = 0; c < originalSpectrum; ++c) {
                newImgMatrix[y][x][c] = inputImgVec[originalY][originalX][c];
            }
        }
    }

    return newImgMatrix;
}

} // namespace geometric
