#include <ImageProc/MorphologicalOperations.h>

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

}
