#pragma once
#include <ImageProc/Types.h>

namespace ImageProc::morph {
ImageProc::imgVec dilation(ImageProc::Image& img);

ImageProc::imgVec erosion(ImageProc::Image& img);
}
