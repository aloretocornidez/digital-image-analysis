#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <opencv2/opencv.hpp>
using namespace cv;

void populateHistogram(Mat &inputImage, int *pixelValueHistogram, double *probabilityDistribution);
void populateDistributionArray(double *probabilityDistribution, int *pixelValueHistogram, int totalImagePixels);
void calculateJValues(int currentThreshold, double *probabilityDistribution, double &q1, double &q2, double &mu1, double &mu2, double &sigmaSquared1, double &sigmaSquared2, double *jValues);
void printArrayValues(int *pixelValueHistogram, double *probabilityDistribution, double *jValues);
void findMinimumJValue(int &bestThreshold, double *jValues);
void binarizeImage(Mat &output, int threshold);
void removeFileExtension(String &imageName);
void openWindow(String windowName, Mat *image);


#endif