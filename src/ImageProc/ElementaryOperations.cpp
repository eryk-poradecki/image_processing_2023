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

    void adjustContrast(Image& image, float factor)
    {
        auto& imgMatrix = image.getImgVec();

        float contrastFactor = (259.0f * (factor + 255.0f)) / (255.0f * (259.0f - factor));
        for (auto& column : imgMatrix) {
            for (auto& row : column) {
                for (auto& pixel : row) {

                    int newPixel = static_cast<int>(contrastFactor * (static_cast<float>(pixel) - 128.0f) + 128.0f);

                    pixel = static_cast<unsigned char>(std::min(255, std::max(0, newPixel)));
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
