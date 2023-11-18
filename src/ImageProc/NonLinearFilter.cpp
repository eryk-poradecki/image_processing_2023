#include "NonLinearFilter.h"
#include "ImageProc/Types.h"
#include <cmath>

using namespace ImageProc;
using namespace filter;

imgVec filter::robertsOperatorII(const Image& image)
{
    imgVec& inputVec = image.getImgVec();
    int width = image.getWidth();
    int height = image.getHeight();
    int spectrum = image.getSpectrum();

    imgVec outputVec(width - 1, std::vector<std::vector<unsigned char>>(height - 1, std::vector<unsigned char>(spectrum, 0)));

    for (int c = 0; c < spectrum; ++c) {
        for (int y = 0; y < height - 1; ++y) {
            for (int x = 0; x < width - 1; ++x) {
                int pixelValue = 0;

                int p1 = static_cast<int>(inputVec[x][y][c]);
                int p2 = static_cast<int>(inputVec[x + 1][y][c]);
                int p3 = static_cast<int>(inputVec[x][y + 1][c]);
                int p4 = static_cast<int>(inputVec[x + 1][y + 1][c]);

                int diff1 = std::abs(p1 - p4);
                int diff2 = std::abs(p2 - p3);

                pixelValue = diff1 + diff2;

                outputVec[x][y][c] = static_cast<unsigned char>(pixelValue);
            }
        }
    }
    return outputVec;
}
