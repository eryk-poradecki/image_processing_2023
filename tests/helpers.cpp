#include "helpers.hpp"
#include "ImageProc/Types.h"
#include <iostream>

bool areVectorsEqual(const std::vector<std::vector<unsigned char>>& vector1, const std::vector<std::vector<unsigned char>>& vector2)
{
    if (vector1.size() != vector2.size() || vector1[0].size() != vector2[0].size()) {
        return false;
    }

    for (int i = 0; i < vector1.size(); ++i) {
        for (int j = 0; j < vector1[0].size(); ++j) {
            if (vector1[i][j] != vector2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool areImageVectorsEqual(const std::vector<std::vector<ImageProc::Pixel>>& vector1, const std::vector<std::vector<ImageProc::Pixel>>& vector2)
{
    if (vector1.size() != vector2.size() || vector1[0].size() != vector2[0].size()) {
        return false;
    }

    for (int i = 0; i < vector1.size(); ++i) {
        for (int j = 0; j < vector1[0].size(); ++j) {
            if (vector1[i][j].r != vector2[i][j].r ||
                vector1[i][j].g != vector2[i][j].g ||
                vector1[i][j].b != vector2[i][j].b) {
                return false;
            }
        }
    }

    return true;
}

void printImageVector(const std::vector<std::vector<ImageProc::Pixel>>& imageVector) {
    for (const auto& row : imageVector) {
        for (const ImageProc::Pixel& pixel : row) {
            std::cout << "{" << static_cast<int>(pixel.r) << ", " << static_cast<int>(pixel.g) << ", " << static_cast<int>(pixel.b) << "} ";
        }
        std::cout << std::endl;
    }
}
