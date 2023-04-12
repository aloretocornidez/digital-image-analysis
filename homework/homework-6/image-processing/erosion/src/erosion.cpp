#include <iostream>
#include "erosion.hpp"

using namespace cv;


erosion::erosion()
{
  std::cout << "Erosion Object Constructed" << std::endl;
}

erosion::~erosion()
{
  std::cout << "Erosion Object Destroyed" << std::endl;
}

void erosion::printHello()
{
  std::cout << "Erosion says hello." << std::endl;
}

void erosion::erodeImage(Mat &input, Mat &output)
{
  std::cout << "Eroding Image using Personal Implementation" << std::endl;

  




}

void erosion::openCVErodeImage(Mat &input, Mat &output)
{
  std::cout << "Eroding Image using OpenCV" << std::endl;

  int SIZE = 11;

  // Create a solid 11 x 11 square kernel.
  Mat k = Mat::ones(SIZE, SIZE, CV_8U);

  // Erode the image.
  cv::erode(input, output, k);
}
