#pragma once
#include <matplot/freestanding/axes_functions.h>
#include <string>
#include <vector>
#include "ImageProc/Types.h"
#include <matplot/matplot.h>

// cpp17 magic namespace
namespace ImageProc::histogram{
	constexpr size_t NUM_BINS = 255; 

	void createAndSaveHist(ImageProc::Image& img, std::string filename, size_t nBins = NUM_BINS);	

	std::vector<std::vector<unsigned char>> splitRGBImgToSaperateLayerRGB(ImageProc::Image& img);

	imgVec createHistorgram(ImageProc::Image& img, size_t nBins);}
