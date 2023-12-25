#pragma once
#include <ImageProc/Types.h>
#include <string>

namespace ImageProc::morph {

ImageProc::imgVec morph(Image& inImage, const std::vector<std::vector<unsigned char>>& kernel, const std::string& type);
ImageProc::imgVec morph1(Image& inImage, const std::string& type);
ImageProc::imgVec opening(Image& img, const std::vector<std::vector<unsigned char>>& kernel);

ImageProc::imgVec closing(Image& img, const std::vector<std::vector<unsigned char>>& kernel);

ImageProc::imgVec elementwiseDivision(const imgVec& img1, const imgVec& img2);

ImageProc::imgVec operationM1(ImageProc::Image& img, const std::vector<std::vector<unsigned char>>& kernel);

bool shouldMergeRegions(const unsigned char seedValue, const unsigned char neighborValue);

imgVec hitOrMissTransformation(Image& img, const std::vector<std::vector<int>>& hitKernel, const std::vector<std::vector<int>>& missKernel);

std::vector<ImageProc::imgVec> regionGrowing(const std::vector<std::pair<int, int>>& seedPointList, const ImageProc::Image& img);
}
