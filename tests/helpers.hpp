#include <vector>
#include "ImageProc/Types.h"

bool areVectorsEqual(const std::vector<std::vector<unsigned char>>& vector1, const std::vector<std::vector<unsigned char>>& vector2);

bool areImageVectorsEqual(const std::vector<std::vector<ImageProc::Pixel>>& vector1, const std::vector<std::vector<ImageProc::Pixel>>& vector2);

void printImageVector(const std::vector<std::vector<ImageProc::Pixel>>& imageVector);