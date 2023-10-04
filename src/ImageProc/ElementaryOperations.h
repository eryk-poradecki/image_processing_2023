#ifndef ELEMENTARY_OPERATIONS_H
#define ELEMENTARY_OPERATIONS_H

#define cimg_display 0

#include "../../libs/CImg.h"
#include "Types.h"

namespace ImageProc{
namespace elementary {
    void adjustBrightness(Image& imageArray, int width, int height, int spectrum, float constant);
    
    void adjustContrast(Image& imageArray, int width, int height, int spectrum, float factor);

    void createNegative(Image& imageArray, int width, int height, int spectrum);

} // namespace elementary
} // namespace ImageProc

#endif // ELEMENTARY_OPERATIONS_H
