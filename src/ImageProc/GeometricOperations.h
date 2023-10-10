#pragma once

#include "Types.h"

namespace ImageProc {

    namespace geometric {

    void verticalFlip(Image& image);

    void horizontalFlip(Image& image);

    void diagonalFlip(Image& image);

    imgVec shrinkImage(const Image& image, int shrinkFactor);

    imgVec enlargeImage(const Image& image, int enlargeFactor);
    
} // namespace geometric
} // namespace ImageProc
