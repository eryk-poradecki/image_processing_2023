#ifndef ELEMENTARY_OPERATIONS_H
#define ELEMENTARY_OPERATIONS_H

#define cimg_display 0

#include "../../libs/CImg.h"
#include "Types.h"

namespace elementary {
    void adjustBrightness(Image& imageArray, int width, int height, int spectrum, float constant);
    
    void adjustContrast(Image& imageArray, int width, int height, int spectrum, float factor);

    void createNegative(Image& imageArray, int width, int height, int spectrum);

} // namespace elementary

#endif // ELEMENTARY_OPERATIONS_H
