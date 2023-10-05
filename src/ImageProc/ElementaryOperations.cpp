#include "ElementaryOperations.h"
#include "Types.h"

namespace ImageProc {
namespace elementary {

    void adjustBrightness(Image& image, int brightness)
    {

        imgVec& imgMatrix = image.getImgVec();

        for (auto& row : imgMatrix) {
            for (unsigned char& element : row) {
                int new_value = element + brightness;
                element = (new_value > 255) ? 255 : (new_value < 0) ? 0
                                                                    : new_value;
            }
        }
    }

void adjustContrast(Image& image, float factor)
{
    auto& imgMatrix = image.getImgVec();
    int height = imgMatrix.size();
    int width = imgMatrix[0].size();
    int spectrum = image.getSpectrum();

    for (auto& row : imgMatrix) {
        for (auto& pixel : row) {
            float contrastFactor = (259.0f * (factor + 255.0f)) / (255.0f * (259.0f - factor));

            int newRed = static_cast<int>(contrastFactor * (static_cast<float>(pixel) - 128.0f) + 128.0f);
            int newGreen = static_cast<int>(contrastFactor * (static_cast<float>(pixel) - 128.0f) + 128.0f);
            int newBlue = static_cast<int>(contrastFactor * (static_cast<float>(pixel) - 128.0f) + 128.0f);

            pixel = static_cast<unsigned char>(std::min(255, std::max(0, newRed)));
            pixel = static_cast<unsigned char>(std::min(255, std::max(0, newGreen)));
            pixel = static_cast<unsigned char>(std::min(255, std::max(0, newBlue)));
        }
    }

}


    void createNegative(Image& image)
    {
        imgVec& imgMatrix = image.getImgVec();

        for (auto& row : imgMatrix) {
            for (unsigned char& element : row) {
                element = 255 - element;
            }
        }
    }

} // namespace elementary
} // namespace ImageProc
