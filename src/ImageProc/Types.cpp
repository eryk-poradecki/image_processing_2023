#include "Types.h"

using namespace ImageProc;



Image::Image(imgVec& img, short spectrum):mImgVec(img),mSpectrum(spectrum) {}
imgVec&  Image::getImgVec() const{
	return mImgVec;
}

int Image::getHeight() const{
	return mHeight;
}
int Image::getWidht() const{
	return mWidht;
}
int Image::getSpectrum() const{
	return mSpectrum;
}
