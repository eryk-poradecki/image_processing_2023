#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

namespace ImageProc {

using imgVec = std::vector<std::vector<unsigned char>>;

class Image{
	public:
	Image(imgVec& img, const short spectrum);
	imgVec& getImgVec() const;
	int getHeight() const;
	int getWidth() const;
	int getSpectrum() const;

	private:
	int mWidth, mHeight;
	imgVec& mImgVec;
	const short mSpectrum;
};


} // namespace ImageProc
#endif // IMAGE_H
