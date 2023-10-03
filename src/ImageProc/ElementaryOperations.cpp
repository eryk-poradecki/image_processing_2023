#include "ElementaryOperations.h"
#include "../../libs/CImg.h"

namespace elementary {

void adjustBrightness(cimg_library::CImg<unsigned char>& image, int constant) {
    int width = image.width();
    int height = image.height();
    int spectrum = image.spectrum();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < spectrum; ++c) {
                unsigned char& pixel = image(x, y, c);
                int new_value = pixel + constant;
                pixel = (new_value > 255) ? 255 : (new_value < 0) ? 0 : new_value;
            }
        }
    }
}


void adjustContrast(cimg_library::CImg<unsigned char>& image, float factor) {
    int width = image.width();
    int height = image.height();
    int spectrum = image.spectrum();

    float average = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < spectrum; ++c) {
                average += image(x, y, c);
            }
        }
    }
    average /= (width * height * spectrum);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < spectrum; ++c) {
                unsigned char& pixel = image(x, y, c);
                float new_value = average + factor * (pixel - average);
                pixel = (new_value > 255) ? 255 : (new_value < 0) ? 0 : new_value;
            }
        }
    }
}


} // namespace elementary