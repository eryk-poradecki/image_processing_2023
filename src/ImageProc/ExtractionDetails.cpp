#include "ExtractionDetails.h"
#include <array>
namespace ImageProc::extractdetails {

int clipInt(int value, int minValue, int maxValue)
{
    return std::max(minValue, std::min(value, maxValue));
}
std::vector<std::vector<int>> laplacianMask1 = {
    { 0, -1, 0 },
    { -1, 4, -1 },
    { 0, -1, 0 }
};

std::vector<std::vector<int>> laplacianMask2 = {
    { -1, -1, -1 },
    { -1, 8, -1 },
    { -1, -1, -1 }
};

std::vector<std::vector<int>> laplacianMask3 = {
    { 1, -2, 1 },
    { -2, 4, -2 },
    { 1, -2, 1 }
};

std::vector<std::vector<float>> laplacianMask2opt = {
    { 8.1961 * 0.7004, 8.1961 * 0.13736, 8.1961 * 0.7004 },
    { -0.7004, 0.09714, -0.7071 }
};

std::vector<std::vector<float>> laplacianMask1opt = {
    { 4.445 * 0.6738, 4.445 * 0.3029, 4.445 * 0.6738 },
    { -0.6738, 0.21418, -0.7071 }
};

std::vector<std::vector<float>> laplacianMask3opt = {
    { 6 * 0.4082, -6 * 0.8164, 6 * 0.4082 },
    { 0.40824, 0.89442, -0.1825 }
};
ImageProc::imgVec extractionDetailsIIIopt(ImageProc::Image& img)
{
    auto imgVecH = convolveHorizontal(img, laplacianMask3opt[0]);
    img.setImgVec(imgVecH);
    auto imgVecV = convolveVertical(img, laplacianMask3opt[1]);
    return imgVecH;
}
ImageProc::imgVec extractionDetailsIII(ImageProc::Image& img, int kernelNum)
{
    std::vector<std::vector<int>> kernel;
    if (kernelNum == 1) {
        kernel = laplacianMask1;
    } else if (kernelNum == 2) {
        kernel = laplacianMask2;
    } else if (kernelNum == 3) {
        kernel = laplacianMask3;
    }
    return convolution(img, kernel);
}
ImageProc::imgVec convolution(ImageProc::Image& img, const std::vector<std::vector<int>>& kernel)
{
    int height = img.getHeight();
    int width = img.getWidth();
    int numChan = img.getSpectrum();
    auto image = img.getImgVec();

    const int kernelX = kernel.size();
    const int kernelY = kernel[0].size();

    const int dx = kernelX / 2;
    const int dy = kernelY / 2;

    ImageProc::imgVec outputImgVec(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(numChan)));

    for (int chan = 0; chan < numChan; ++chan) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int tmp = 0;
                for (int k = 0; k < kernelX; ++k) {
                    for (int l = 0; l < kernelY; ++l) {
                        int x = j - dx + l;
                        int y = i - dy + k;
                        if (x >= 0 && x < width && y >= 0 && y < height)
                            tmp += image[y][x][chan] * kernel[k][l];
                    }
                }
                outputImgVec[i][j][chan] = static_cast<unsigned char>(clipInt(tmp, 0, 255));
            }
        }
    }
    return outputImgVec;
}

ImageProc::imgVec convolveHorizontal(ImageProc::Image& img, const std::vector<float>& kernel)
{
    int height = img.getHeight();
    int width = img.getWidth();
    int numChan = img.getSpectrum();
    auto image = img.getImgVec();

    const int kernelSize = kernel.size();
    const int halfKernel = kernelSize / 2;

    ImageProc::imgVec outputImgVec(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(numChan)));

    for (int chan = 0; chan < numChan; ++chan) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int tmp = 0;
                for (int k = 0; k < kernelSize; ++k) {
                    int x = j - halfKernel + k;
                    if (x >= 0 && x < width)
                        tmp += image[i][x][chan] * kernel[k];
                }
                outputImgVec[i][j][chan] = static_cast<unsigned char>(clipInt(tmp, 0, 255));
            }
        }
    }
    return outputImgVec;
}

ImageProc::imgVec convolveVertical(ImageProc::Image& img, const std::vector<float>& kernel)
{
    int height = img.getHeight();
    int width = img.getWidth();
    int numChan = img.getSpectrum();
    auto image = img.getImgVec();

    const int kernelSize = kernel.size();
    const int halfKernel = kernelSize / 2;

    ImageProc::imgVec outputImgVec(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(numChan)));

    for (int chan = 0; chan < numChan; ++chan) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int tmp = 0;
                for (int k = 0; k < kernelSize; ++k) {
                    int y = i - halfKernel + k;
                    if (y >= 0 && y < height)
                        tmp += image[y][j][chan] * kernel[k];
                }
                outputImgVec[i][j][chan] = static_cast<unsigned char>(clipInt(tmp, 0, 255));
            }
        }
    }
    return outputImgVec;
}
}
