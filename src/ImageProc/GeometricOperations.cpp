#include "GeometricOperations.h"
#include "Types.h"

namespace ImageProc {

namespace geometric {

    void horizontalFlip(Image& image)
    {
        imgVec& imgMatrix = image.getImgVec();

        std::reverse(imgMatrix.begin(), imgMatrix.end());
    }

    void verticalFlip(Image& image)
    {
        imgVec& imgMatrix = image.getImgVec();

        for (auto& row : imgMatrix) {
            std::reverse(row.begin(), row.end());
        }
    }

} // namespace geometric
} // namespace ImageProc
