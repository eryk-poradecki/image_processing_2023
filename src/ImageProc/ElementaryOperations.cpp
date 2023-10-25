#include "ElementaryOperations.h"
#include "Types.h"
#include <algorithm>

namespace ImageProc::elementary {

void adjustBrightness(Image& image, int brightness)
{
    imgVec& imgMatrix = image.getImgVec();

    for (auto& column : imgMatrix) {
        for (auto& row : column) {
            for (auto& pixel : row) {
                int newPixel = pixel + brightness;
                pixel = std::min(255, std::max(0, newPixel));
            }
        }
    }
}

void adjustContrast(Image& image, int factor)
{
    auto& imgMatrix = image.getImgVec();
    // Todo @eryk  check formula
    float contrastFactor = (255 * (factor + 255.0)) / (255 * (255 - factor));
    for (auto& column : imgMatrix) {
        for (auto& row : column) {
            for (auto& pixel : row) {
                int newPixel = static_cast<int>(contrastFactor * (pixel - 128) + 128);
                pixel = std::min(255, std::max(0, newPixel));
            }
        }
    }
}

void createNegative(Image& image)
{
    imgVec& imgMatrix = image.getImgVec();

    for (auto& column : imgMatrix) {
        for (auto& row : column) {
            for (auto& pixel : row) {
                pixel = 255 - pixel;
            }
        }
    }
}
} // namespace elementary
