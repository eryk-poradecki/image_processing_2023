#include "ElementaryOperations.h"
#include "../../libs/CImg.h"

namespace elementary {

void adjustBrightness(cimg_library::CImg<unsigned char>& image, float factor) {
    int width = image.width();
    int height = image.height();
    int spectrum = image.spectrum();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < spectrum; ++c) {
                unsigned char& pixel = image(x, y, c);
                int new_value = static_cast<int>(pixel * factor);
                pixel = (new_value > 255) ? 255 : new_value;
            }
        }
    }
}

} // namespace elementary