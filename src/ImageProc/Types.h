#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

namespace ImageProc {

using imgVec = std::vector<std::vector<std::vector<unsigned char>>>;

class Image {
public:
    Image(imgVec& img);
   [[nodiscard]] imgVec& getImgVec() const noexcept;
   [[nodiscard]] int getHeight() const noexcept;
   [[nodiscard]] int getWidth() const noexcept;
   [[nodiscard]] int getSpectrum() const noexcept;

    bool operator!=(const Image& other) const;
    bool operator==(const Image& other) const;

private:
    int mWidth, mHeight;
    imgVec& mImgVec;
    short mSpectrum;
};

} // namespace ImageProc
#endif // IMAGE_H
