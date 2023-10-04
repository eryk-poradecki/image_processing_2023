#ifndef ELEMENTARY_OPERATIONS_H
#define ELEMENTARY_OPERATIONS_H

#define cimg_display 0

#include "Types.h"

namespace ImageProc{
namespace elementary {
    void adjustBrightness(Image& image, int brightness);
    
    void adjustContrast(Image& image, float factor);

    void createNegative(Image& image);

} // namespace elementary
} // namespace ImageProc

#endif // ELEMENTARY_OPERATIONS_H
