#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

namespace ImageProc {

using imgVec = std::vector<std::vector<std::vector<unsigned char>>>;

class Image {
public:
    Image(imgVec& img);
    Image& operator=(Image&& other) noexcept;
    Image();
    [[nodiscard]] imgVec& getImgVec() const noexcept;
    [[nodiscard]] int getHeight() const noexcept;
    [[nodiscard]] int getWidth() const noexcept;
    [[nodiscard]] int getSpectrum() const noexcept;
    void setImgVec(imgVec vec);

private:
    int mWidth, mHeight;
    mutable imgVec mImgVec;
    short mSpectrum;
};

} // namespace ImageProc
#endif // IMAGE_H
