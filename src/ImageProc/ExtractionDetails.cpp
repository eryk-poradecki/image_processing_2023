#include "ExtractionDetails.h"

namespace ImageProc::extractdetails {
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
    { -2, 8, -2 },
    { 1, -2, 1 }
};
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
                outputImgVec[i][j][chan] = static_cast<unsigned char>(tmp);
            }
        }
    }
    return outputImgVec;
}

}
