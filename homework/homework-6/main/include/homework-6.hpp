#ifndef __HOMEWORK_6_H__
#define __HOMEWORK_6_H__

#include <opencv2/opencv.hpp>


// Opens an image via the opencv api, waits for user interaction to close the image.
void showOneImage(cv::String windowName, cv::Mat &image);

// Opens two images via the opencv api, waits for user interaction to close the images.
void showTwoImages(cv::String windowName1, cv::Mat &image1, cv::String windowName2, cv::Mat &image2);

// Removes the file extension from the arguement name.
void removeFileExtension(cv::String &imageName);


#endif