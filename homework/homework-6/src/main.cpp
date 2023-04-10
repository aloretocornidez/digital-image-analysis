#include "homework-6.hpp"
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
  using namespace cv;

  // Usage for the program
  if (argc != 2)
  {
    std::cout << "Usage: {programName} path/to/image" << std::endl;
    return -1;
  }

  // Read the image file
  Mat inputImage = imread(argv[1], IMREAD_GRAYSCALE);

  // Check for failure when opening the image.
  if (inputImage.empty())
  {
    std::cout << "Could not open or find the image" << std::endl;
    return -1;
  }

  // Creating Output image to keep the input image as a buffer.
  Mat L = inputImage.clone();


  return 0;
}
