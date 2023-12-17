#include "kernels.h"
#include <vector>

std::vector<std::vector<unsigned char>> kernelCross = {
    { 0, 1, 0 },
    { 1, 1, 1 },
    { 0, 1, 0 }
};

std::vector<std::vector<unsigned char>> kernelFull = {
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 }
};
std::vector<std::vector<unsigned char>> kernel1 = {
    { 0, 0, 0 },
    { 1, 1, 1 },
    { 0, 0, 0 }
};
std::vector<std::vector<unsigned char>> kernel2 = {
    { 0, 0, 0 },
    { 1, 0, 1 },
    { 0, 0, 0 }
};

const std::vector<std::vector<std::vector<unsigned char>>> Kernels::allKernels = {
    kernelCross,
    kernelFull,
    kernel1,
    kernel2
};
