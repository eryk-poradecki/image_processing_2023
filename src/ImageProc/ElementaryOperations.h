#ifndef ELEMENTARY_OPERATIONS_H
#define ELEMENTARY_OPERATIONS_H

#define cimg_display 0

#include "../../libs/CImg.h"

namespace elementary {
    void adjustBrightness(cimg_library::CImg<unsigned char>& image, float factor);


} // namespace elementary

#endif // ELEMENTARY_OPERATIONS_H
