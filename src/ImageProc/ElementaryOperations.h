#pragma once

#include "Types.h"

namespace ImageProc{
namespace elementary {
    void adjustBrightness(Image& image, int brightness);
    
    void adjustContrast(Image& image, float factor);

    void createNegative(Image& image);

} // namespace elementary
} // namespace ImageProc
