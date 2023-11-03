#include "ImgAnalysis.h"
#include "Exceptions.h"
#include "Types.h"
#include <cmath>
#include <cstdlib>
#include <tuple>

using namespace ImageProc;

int calculate_3DVecMax(imgVec& threeDVector, int chan);

std::tuple<float, float, float> analysis::calculateMSE(const Image& img1, const Image& img2) {
    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();

    double mseR = 0.0, mseG = 0.0, mseB = 0.0;
    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();
    int numPixels = imgMatrix2[0][0].size();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            for (int k = 0; k < numPixels; ++k) {
                if (numPixels == 1) {
                    double diff = static_cast<double>(imgMatrix1[i][j][k]) - static_cast<double>(imgMatrix2[i][j][k]);
                    mseR += diff * diff;
                } else if (numPixels == 3) {
                    double diffR = static_cast<double>(imgMatrix1[i][j][0]) - static_cast<double>(imgMatrix2[i][j][0]);
                    double diffG = static_cast<double>(imgMatrix1[i][j][1]) - static_cast<double>(imgMatrix2[i][j][1]);
                    double diffB = static_cast<double>(imgMatrix1[i][j][2]) - static_cast<double>(imgMatrix2[i][j][2]);

                    mseR += diffR * diffR;
                    mseG += diffG * diffG;
                    mseB += diffB * diffB;
                }
            }
        }
    }

    mseR /= static_cast<double>(numRows * numCols);
    mseG /= static_cast<double>(numRows * numCols);
    mseB /= static_cast<double>(numRows * numCols);

    if (numPixels == 1) {
        mseG = 0.0;
        mseB = 0.0;
    }

    return std::make_tuple(mseR, mseG, mseB);
}

std::tuple<float, float, float> analysis::calculatePSNR(const Image& img1, const Image& img2)
{
  
    imgVec imgMatrix1 = img1.getImgVec();

    int numRows = imgMatrix1.size();
    int numCols = imgMatrix1[0].size();
    int numPixels = imgMatrix1[0][0].size();

    auto [mseR, mseG, mseB] = analysis::calculateMSE(img1, img2);

    long denominatorR =  mseR * numCols * numRows;

    long maxR, maxG, maxB;

    long numeratorR, numeratorG, numeratorB;
    maxR = calculate_3DVecMax(imgMatrix1, 0);
    numeratorR = maxR* maxR * numCols * numRows;

    if(numPixels ==1){

        float psnrR = 10 * std::log10(numeratorR / denominatorR);
        return std::make_tuple(psnrR, 0,0);
    }
    else{
        long denominatorG =  mseG * numCols * numRows;
        long denominatorB =  mseB * numCols * numRows;

        maxG = calculate_3DVecMax(imgMatrix1,1);
        maxB = calculate_3DVecMax(imgMatrix1,2);

        numeratorG = maxG* maxG*  numCols * numRows;
        numeratorB = maxB* maxB*  numCols * numRows;
            
        float psnrR = 10 * std::log10(numeratorR / denominatorR);
        float psnrG = 10 * std::log10(numeratorG / denominatorG);
        float psnrB = 10 * std::log10(numeratorB / denominatorB);
        return std::make_tuple(psnrR, psnrG, psnrB);

    }

}

std::tuple<float, float, float> analysis::calculatePMSE(const Image& img1, const Image& img2)
{

    auto [mseR, mseG, mseB] = analysis::calculateMSE(img1, img2);
    imgVec imgMatrix1 = img1.getImgVec();
    int numPixels = imgMatrix1[0][0].size();
    int maxR, maxG, maxB;
    int denominatorR, denominatorB, denominatorG;

    maxR = calculate_3DVecMax(imgMatrix1,0);
    denominatorR = maxR* maxR;

    if(numPixels ==1){
        maxG = 0;
        maxB = 0;
        denominatorB = 0;
        denominatorG = 0;

        float pmseR = mseR /(denominatorR);
        return std::make_tuple(pmseR, 0,0);
    }
    else{
        maxG = calculate_3DVecMax(imgMatrix1,1);
        maxB = calculate_3DVecMax(imgMatrix1,2);


        denominatorG= maxG* maxG;
        denominatorB = maxB* maxB;
            
        float pmseG = mseG /(denominatorG);
        float pmseR = mseR /(denominatorR);
        float pmseB = mseB /(denominatorB);
        return std::make_tuple(pmseR, pmseG, pmseB);
    }
}

std::tuple<int, int, int> analysis::calculateMD(const Image& img1, const Image& img2)
{


     imgVec imgMatrix1 = img1.getImgVec();
     imgVec imgMatrix2 = img2.getImgVec();

     int peakR = 0;
     int peakG = 0;
     int peakB = 0;

     int numRows = imgMatrix2.size();
     int numCols = imgMatrix2[0].size();
     int numPixels = imgMatrix2[0][0].size();

     int diff = 0;
         for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {

                if(numPixels ==1) {
                    diff = imgMatrix1[i][j][0] - imgMatrix2[i][j][0];
                    peakR = std::max(peakR, std::abs(diff));

                }else if (numPixels==3){
                    diff = imgMatrix1[i][j][0]- imgMatrix2[i][j][0];
                    peakR = std::max(peakR, std::abs(diff));

                    diff = imgMatrix1[i][j][1]- imgMatrix2[i][j][1];
                    peakG = std::max(peakG, std::abs(diff));

                    diff = imgMatrix1[i][j][2]- imgMatrix2[i][j][2];
                    peakB = std::max(peakB, std::abs(diff));
                }

            }
        }

        return std::make_tuple(peakR, peakG, peakB);
}


std::tuple<float, float, float> analysis::calculateSNR(const Image& img1, const Image& img2){
    imgVec imgMatrix1 = img1.getImgVec();
    imgVec imgMatrix2 = img2.getImgVec();

    int numRows = imgMatrix2.size();
    int numCols = imgMatrix2[0].size();
    int numPixels = imgMatrix2[0][0].size();

    float snrR = 0.0, snrG = 0.0, snrB = 0.0;

    long denominatorR = 1, denominatorG = 1, denominatorB = 1;
    long numeratorR = 0, numeratorG = 0, numeratorB = 0;
    int diff =0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {

                if (numPixels == 1) {
                    diff = imgMatrix1[i][j][0] - imgMatrix2[i][j][0];
                    denominatorR += diff * diff;
                    numeratorR += imgMatrix1[i][j][0] * imgMatrix1[i][j][0];
                } else if (numPixels == 3) {
                        diff = imgMatrix1[i][j][0] - imgMatrix2[i][j][0];
                        denominatorR += diff * diff;
                        numeratorR += imgMatrix1[i][j][0] * imgMatrix1[i][j][0];

                        diff = imgMatrix1[i][j][1] - imgMatrix2[i][j][1];
                        denominatorG += diff * diff;
                        numeratorG += imgMatrix1[i][j][1] * imgMatrix1[i][j][1];

                        diff = imgMatrix1[i][j][2] - imgMatrix2[i][j][2];
                        denominatorB += diff * diff;
                        numeratorB += imgMatrix1[i][j][2] * imgMatrix1[i][j][2];
                    }
                }

        }

    snrR = 10 * std::log10(static_cast<float>(numeratorR) / static_cast<float>(denominatorR));
    snrG = 10 * std::log10(static_cast<float>(numeratorG) / static_cast<float>(denominatorG));
    snrB = 10 * std::log10(static_cast<float>(numeratorB) / static_cast<float>(denominatorB));

    if (numPixels == 1) {
        snrG = 0.0;
        snrB = 0.0;
    }

    return std::make_tuple(snrR, snrG, snrB);
}

int analysis::calculate_3DVecMax(imgVec& threeDVector, int chan)
{

    int max_value = threeDVector[0][0][chan];
    for (const auto& layer : threeDVector) {
        for (const auto& row : layer) {
            int value = row[chan];
                if (value > max_value) {
                    max_value = value;
                }
        }
    }
    return max_value;
}
