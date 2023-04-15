#include "homework-6.hpp"

void showOneImage(cv::String windowName, cv::Mat &image)
{

    cv::namedWindow(windowName); // Create a window

    cv::imshow(windowName, image); // Show our image inside the created window.

    cv::waitKey(0); // Wait for any keystroke in the window

    cv::destroyWindow(windowName); // destroy the created window
}

void showTwoImages(cv::String windowName1, cv::Mat &image1, cv::String windowName2, cv::Mat &image2)
{

    cv::namedWindow(windowName1); // Create a window

    cv::imshow(windowName1, image1); // Show our image inside the created window.


    cv::namedWindow(windowName2); // Create a window

    cv::imshow(windowName2, image2); // Show our image inside the created window.

    cv::waitKey(0); // Wait for any keystroke in the window

    cv::destroyWindow(windowName1); // destroy the created window
    cv::destroyWindow(windowName2); // destroy the created window

}


void removeFileExtension(cv::String &imageName)
{
  size_t last = imageName.find_last_of(".");
  imageName = imageName.substr(0, last);
}