#include "helpers.hpp"
#include "ImageProc/Types.h"
#include <iostream>

bool areVectorsEqual(const std::vector<std::vector<std::vector<unsigned char>>>& vector1, const std::vector<std::vector<std::vector<unsigned char>>>& vector2)
{
    if (vector1.size() != vector2.size()) {
        return false;
    }

    for (size_t i = 0; i < vector1.size(); ++i) {
        const auto& subVector1 = vector1[i];
        const auto& subVector2 = vector2[i];

        if (subVector1.size() != subVector2.size()) {
            return false;
        }

        for (size_t j = 0; j < subVector1.size(); ++j) {
            const auto& innerVector1 = subVector1[j];
            const auto& innerVector2 = subVector2[j];

            if (innerVector1.size() != innerVector2.size()) {
                return false;
            }

            for (size_t k = 0; k < innerVector1.size(); ++k) {
                if (innerVector1[k] != innerVector2[k]) {
                    return false;
                }
            }
        }
    }

    return true;
}

// void printImageVector(const std::vector<std::vector<unsigned char>>& imageVector)
// {
//     for (const auto& row : imageVector) {
//         for (const ImageProc::Pixel& pixel : row) {
//             std::cout << "{" << static_cast<int>(pixel.r) << ", " << static_cast<int>(pixel.g) << ", " << static_cast<int>(pixel.b) << "} ";
//         }
//         std::cout << std::endl;
//     }
// }
