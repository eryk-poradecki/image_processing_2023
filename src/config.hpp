#pragma once
#include <string>

namespace config {

std::string programDescription = "This program is used to process images using various image processing techniques such as elementary operations, geometric operations, noise removal, and image analysis.";

std::string programUsageInfo = "Usage: ImageProcApp [-f] [--brightness] [--contrast] [--negative] [--vflip] [--hflip] [--dflip] [--shrink] [--enlarge] [--adaptive] [--min] [--max] [--wmin] [--wmax] [--hmin] [--hmax] [--mse] [--pmse] [--psnr] [--md] [--snr]\n"
                               "\n"
                               "Options:\n"
                               "  -f\t\tSpecify the input image file.\n"
                               "  --brightness\tAdjust the brightness of the image by the specified factor.\n"
                               "  --contrast\tAdjust the contrast of the image by the specified factor.\n"
                               "  --negative\tCreate a negative of the input image.\n"
                               "  --vflip\tFlip the image vertically.\n"
                               "  --hflip\tFlip the image horizontally.\n"
                               "  --dflip\tFlip the image diagonally.\n"
                               "  --shrink\tShrink the image by the specified factor.\n"
                               "  --enlarge\tEnlarge the image by the specified factor.\n"
                               "  --adaptive\tApply adaptive median filter for noise removal.\n"
                               "  \t--wmin\tSet the minimum width for the adaptive median filter.\n"
                               "  \t--wmax\tSet the maximum width for the adaptive median filter.\n"
                               "  \t--hmin\tSet the minimum height for the adaptive median filter.\n"
                               "  \t--hmax\tSet the maximum height for the adaptive median filter.\n"
                               "  --min\t\tApply min filter for noise removal.\n"
                               "  --max\t\tApply max filter for noise removal.\n"
                               " \t--w\t\tSet the width for the min/max filter.\n"
                               " \t--h\t\tSet the height for the min/max filter.\n"
                               "  --mse\t\tCalculate Mean Squared Error (MSE) between the original and processed images.\n"
                               "  --pmse\tCalculate Peak Mean Squared Error (PMSE) between the original and processed images.\n"
                               "  --psnr\tCalculate Peak Signal-to-Noise Ratio (PSNR) between the original and processed images.\n"
                               "  --md\t\tCalculate Maximum Difference (MD) between the original and processed images.\n"
                               "  --snr\t\tCalculate Signal-to-Noise Ratio (SNR) between the original and processed images.\n"
                               "\n";
}; // namespace config
