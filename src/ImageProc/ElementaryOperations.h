#ifndef ELEMENTARY_OPERATIONS_H
#define ELEMENTARY_OPERATIONS_H

#define cimg_display 0

#include "../../libs/CImg.h"
#include "Types.h"

namespace ImageProc{
namespace elementary {
    void adjustBrightness(Image& image, int brightness);
    
    void adjustContrast(Image& image,int spectrum, float factor);

    void createNegative(Image& image, int spectrum);

} // namespace elementary
} // namespace ImageProc

#endif // ELEMENTARY_OPERATIONS_H
