#pragma once
#include <ImageProc/Types.h>

namespace ImageProc::morph {
ImageProc::imgVec dilation(ImageProc::Image& img);

ImageProc::imgVec erosion(ImageProc::Image& img);

ImageProc::imgVec opening(ImageProc::Image& img);

ImageProc::imgVec closing(ImageProc::Image& img);

ImageProc::imgVec elementwiseDivision(const imgVec& img1, const imgVec& img2);

ImageProc::imgVec operationM1(ImageProc::Image& img);
}
