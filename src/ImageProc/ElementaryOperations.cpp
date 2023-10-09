#include "ElementaryOperations.h"
#include "Types.h"
#include <algorithm>

namespace ImageProc {
namespace elementary {

    void adjustBrightness(Image& image, int brightness)
    {
        imgVec& imgMatrix = image.getImgVec();

        for (auto& column : imgMatrix) {
            for (auto& row : column) {
                for (auto& pixel : row) {
                    int newPixel = pixel + brightness;

                    pixel = (newPixel > 255) ? 255 : (newPixel < 0) ? 0
                                                                    : newPixel;
                }
            }
        }
    }

    void adjustContrast(Image& image, int factor)
    {
        auto& imgMatrix = image.getImgVec();

        int contrastFactor = (259 * (factor + 255)) / (255 * (259 - factor));
        for (auto& column : imgMatrix) {
            for (auto& row : column) {
                for (auto& pixel : row) {

                    int newPixel = contrastFactor * (static_cast<float>(pixel) - 128) + 128;
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
} // namespace ImageProc
