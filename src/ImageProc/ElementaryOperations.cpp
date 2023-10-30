#include "ElementaryOperations.h"
#include "Types.h"
#include <algorithm>

namespace ImageProc::elementary {

void adjustBrightness(Image& image, int brightness)
{
    imgVec& imgMatrix = image.getImgVec();

    for (auto& column : imgMatrix) {
        for (auto& row : column) {
            for (auto& channelPixel : row) {
                int newChannelPixel = channelPixel + brightness;
                channelPixel = std::min(255, std::max(0, newChannelPixel));
            }
        }
    }
}

// https://www.dfstudios.co.uk/articles/programming/image-programming-algorithms/image-processing-algorithms-part-5-contrast-adjustment/
void adjustContrast(Image& image, int factor)
{
    auto& imgMatrix = image.getImgVec();

    float contrastFactor = (259.0 * (factor + 255.0)) / (255.0 * (259.0 - factor));

    for (auto& row : imgMatrix) {
        for (auto& column : row) {
            for (auto& channelPixel : column) { // color channel
                int oldChannelPixel = channelPixel;
                int newChannelPixel = static_cast<int>(contrastFactor * (oldChannelPixel - 128) + 128);
                newChannelPixel = std::max(0, std::min(255, newChannelPixel));
                channelPixel = static_cast<unsigned char>(newChannelPixel);
            }
        }
    }
}

void createNegative(Image& image)
{
    imgVec& imgMatrix = image.getImgVec();

    for (auto& column : imgMatrix) {
        for (auto& row : column) {
            for (auto& channelPixel : row) {
                channelPixel = 255 - channelPixel;
            }
        }
    }
}
} // namespace elementary
