#include "ElementaryOperations.h"

namespace elementary {

void adjustBrightness(Image& imageArray, int width, int height, int spectrum, float constant) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * spectrum; ++j) {
            int new_value = imageArray[i][j] + constant;
            imageArray[i][j] = (new_value > 255) ? 255 : (new_value < 0) ? 0 : new_value;
        }
    }
}

void adjustContrast(Image& imageArray, int width, int height, int spectrum, float factor) {
    float average = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * spectrum; ++j) {
            average += imageArray[i][j];
        }
    }
    average /= (height * width * spectrum);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * spectrum; ++j) {
            float new_value = average + factor * (imageArray[i][j] - average);
            imageArray[i][j] = (new_value > 255) ? 255 : (new_value < 0) ? 0 : new_value;
        }
    }
}

void createNegative(Image& imageArray, int width, int height, int spectrum) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * spectrum; ++j) {
            imageArray[i][j] = 255 - imageArray[i][j];
        }
    }
}

} // namespace elementary
