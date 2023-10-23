#pragma once
#include <exception>
#include <string>

namespace ImageProc {
class ImgSpectrumValueException : public std::exception {
public:
    const char* what() const noexcept override;
};

class DimImgValueException : public std::exception {
public:
    const char* what() const noexcept override;
};

}