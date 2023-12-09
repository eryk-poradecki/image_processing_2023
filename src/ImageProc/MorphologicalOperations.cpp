#include <ImageProc/MorphologicalOperations.h>
#include <queue>

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

imgVec regionGrowing(ImageProc::Image& image)
{
    imgVec& inputImgVec = image.getImgVec();
    int height = image.getHeight();
    int width = image.getWidth();
    int spectrum = image.getSpectrum();

    imgVec resultImg(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(spectrum, 0)));

    int seedX = 100;
    int seedY = 50;

    // region is linked to the seed region if the difference in intensity is less than a threshold
    int threshold = 10;

    std::queue<std::pair<int, int>> q;
    q.push({seedX, seedY});

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < height && ny >= 0 && ny < width) {
                    if (abs(inputImgVec[nx][ny][0] - inputImgVec[seedX][seedY][0]) < threshold) {
                        resultImg[nx][ny][0] = inputImgVec[seedX][seedY][0];
                        q.push({nx, ny});
                    }
                }
            }
        }
    }

    return resultImg;
}

}
