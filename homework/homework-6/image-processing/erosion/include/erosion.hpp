#ifndef __EROSION_H__
#define __EROSION_H__

#include <iostream>
#include <opencv2/opencv.hpp>

class erosion
{
private:
public:
    erosion();
    ~erosion();

    // Print Function to test class/namespace.
    void printHello();

    // Erosion Process
    static void erodeImage(cv::Mat &input, cv::Mat &output, int kernelSize);

    // Open CV Erode Image
    static void openCVErodeImage(cv::Mat &input, cv::Mat &output);
};

#endif