#ifndef __DILATION_H__
#define __DILATION_H__

#include <opencv2/opencv.hpp>

class dilation
{
private:
public:
    dilation();
    ~dilation();

    void printHello();

    static void dilateImage(cv::Mat &input, cv::Mat &output, int kernelSize);

    static void openCVDilateImage(cv::Mat &input, cv::Mat &output);
};

#endif