#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

namespace ImageProc {

struct Pixel {
	unsigned char r, g, b;
};

using imgVec = std::vector<std::vector<Pixel>>;

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
