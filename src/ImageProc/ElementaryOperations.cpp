#include "ElementaryOperations.h"
#include "Types.h"

namespace ImageProc {
namespace elementary {

void adjustBrightness(Image& image, int brightness) {
    
	imgVec& imgMatrix = image.getImgVec();
	
	for (auto& row : imgMatrix) {
        for (unsigned char& element : row) {
            int new_value = element + brightness;
        	element = (new_value > 255) ? 255 : (new_value < 0) ? 0 : new_value;

		}
    }
}

void adjustContrast(Image& image, float factor) {
    float average = 0;

    auto& imgMatrix = image.getImgVec();

    int height = imgMatrix.size();
    int width = imgMatrix[0].size();
    int spectrum = image.getSpectrum();

    for (auto& row : imgMatrix) {
        for (auto& element : row) {
            average += element;
        }
    }
    average /= (height * width * spectrum);
    
    for (auto& row : imgMatrix) {
        for (auto& element : row) {
            float new_value = average + factor * (element - average);
            element = (new_value > 255) ? 255 : (new_value < 0) ? 0 : new_value;
        }
    }  
}

void createNegative(Image& image) {
    imgVec& imgMatrix = image.getImgVec();
    
    for (auto& row : imgMatrix) {
        for (unsigned char& element : row) {
            element = 255 - element;
        }
    }
}

} // namespace elementary
} // namespace ImageProc
