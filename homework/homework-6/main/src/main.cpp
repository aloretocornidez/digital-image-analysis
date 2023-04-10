#include "homework-6.hpp"
#include "erosion.hpp"
#include "dilation.hpp"

#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
  erosion testErosion;
  // dilation testDilation;


  testErosion.printHello();
  // testDilation.printHello();

  // // Usage for the program
  // if (argc != 2)
  // {
  //   std::cout << "Usage: {programName} path/to/image" << std::endl;
  //   return -1;
  // }

  // std::cout << "Running Homework 6 Driver with input file: " << argv[1] << std::endl;

  // // Read the image file
  // cv::Mat inputImage = imread(argv[1], cv::IMREAD_GRAYSCALE);

  // // Check for failure when opening the image.
  // if (inputImage.empty())
  // {
  //   std::cout << "Could not open or find the image" << std::endl;
  //   return -1;
  // }

  // // Creating Output image to keep the input image as a buffer.
  // cv::Mat inputBuffer = inputImage.clone();

  


  return 0;
}
