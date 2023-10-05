#include "helpers.hpp"

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
