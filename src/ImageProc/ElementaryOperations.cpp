#include "ElementaryOperations.h"
#include "Types.h"

namespace ImageProc {
namespace elementary {

    void adjustBrightness(Image& image, int brightness)
    {
        imgVec& imgMatrix = image.getImgVec();

        for (auto& row : imgMatrix) {
            for (Pixel& pixel : row) {
                int new_value_r = pixel.r + brightness;
                int new_value_g = pixel.g + brightness;
                int new_value_b = pixel.b + brightness;

                pixel.r = (new_value_r > 255) ? 255 : (new_value_r < 0) ? 0 : new_value_r;
                pixel.g = (new_value_g > 255) ? 255 : (new_value_g < 0) ? 0 : new_value_g;
                pixel.b = (new_value_b > 255) ? 255 : (new_value_b < 0) ? 0 : new_value_b;
            }
        }
    }

    void adjustContrast(Image& image, float factor)
    {
        auto& imgMatrix = image.getImgVec();

        for (auto& row : imgMatrix) {
            for (Pixel& pixel : row) {
                float contrastFactor = (259.0f * (factor + 255.0f)) / (255.0f * (259.0f - factor));

                int newRed = static_cast<int>(contrastFactor * (static_cast<float>(pixel.r) - 128.0f) + 128.0f);
                int newGreen = static_cast<int>(contrastFactor * (static_cast<float>(pixel.g) - 128.0f) + 128.0f);
                int newBlue = static_cast<int>(contrastFactor * (static_cast<float>(pixel.b) - 128.0f) + 128.0f);

                pixel.r = static_cast<unsigned char>(std::min(255, std::max(0, newRed)));
                pixel.g = static_cast<unsigned char>(std::min(255, std::max(0, newGreen)));
                pixel.b = static_cast<unsigned char>(std::min(255, std::max(0, newBlue)));
            }
        }
    }

    void createNegative(Image& image)
    {
        imgVec& imgMatrix = image.getImgVec();

        for (auto& row : imgMatrix) {
            for (Pixel& pixel : row) {
                pixel.r = 255 - pixel.r;
                pixel.g = 255 - pixel.g;
                pixel.b = 255 - pixel.b;
            }
        }
    }

} // namespace elementary
} // namespace ImageProc
