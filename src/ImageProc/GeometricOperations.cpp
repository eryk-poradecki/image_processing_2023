#include "GeometricOperations.h"
#include "Types.h"
#include <algorithm>

namespace ImageProc {

namespace geometric {

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

        for (auto& column : imgMatrix) {
            std::reverse(column.begin(), column.end());
        }

        std::reverse(imgMatrix.begin(), imgMatrix.end());
    }

    imgVec shrinkImage(const Image& image, int shrinkFactor)
    {
        // Get the original image dimensions
        int originalWidth = image.getWidth();
        int originalHeight = image.getHeight();
        int originalSpectrum = image.getSpectrum();

        // Calculate the new dimensions
        int newWidth = originalWidth / shrinkFactor;
        int newHeight = originalHeight / shrinkFactor;

        // Create a new image with the reduced dimensions
        imgVec newImgMatrix(newHeight, std::vector<std::vector<unsigned char>>(newWidth, std::vector<unsigned char>(originalSpectrum, 0)));

        // Iterate over the new image pixels
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                // Calculate the corresponding region in the original image
                int startX = x * shrinkFactor;
                int startY = y * shrinkFactor;

                // Accumulate pixel values in the region
                std::vector<unsigned int> sumPixel(originalSpectrum, 0);
                for (int i = 0; i < shrinkFactor; ++i) {
                    for (int j = 0; j < shrinkFactor; ++j) {
                        for (int c = 0; c < originalSpectrum; ++c) {
                            sumPixel[c] += image.getImgVec()[startY + i][startX + j][c];
                        }
                    }
                }

                // Compute the average value for the new pixel
                for (int c = 0; c < originalSpectrum; ++c) {
                    newImgMatrix[y][x][c] = static_cast<unsigned char>(sumPixel[c] / (shrinkFactor * shrinkFactor));
                }
            }
        }

        // Create and return the new Image object
        return newImgMatrix;
    }

    imgVec enlargeImage(const Image& image, int enlargeFactor)
    {
        // Get the original image dimensions
        int originalWidth = image.getWidth();
        int originalHeight = image.getHeight();
        int originalSpectrum = image.getSpectrum();

        // Calculate the new dimensions
        int newWidth = originalWidth * enlargeFactor;
        int newHeight = originalHeight * enlargeFactor;

        // Create a new image with the enlarged dimensions
        imgVec newImgMatrix(newHeight, std::vector<std::vector<unsigned char>>(newWidth, std::vector<unsigned char>(originalSpectrum, 0)));

        // Iterate over the new image pixels
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                // Calculate the corresponding region in the original image
                int originalX = x / enlargeFactor;
                int originalY = y / enlargeFactor;

                // Copy the pixel values from the original image to the enlarged image
                for (int c = 0; c < originalSpectrum; ++c) {
                    newImgMatrix[y][x][c] = image.getImgVec()[originalY][originalX][c];
                }
            }
        }

        // Return the new image data
        return newImgMatrix;
    }



} // namespace geometric
} // namespace ImageProc
