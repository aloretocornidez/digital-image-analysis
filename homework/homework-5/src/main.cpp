#include "functions.hpp"
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

  // Initialize the Labels in the image.
  initializeLabels(L);


  // Update Labels
  updateLabels(L);

  L.convertTo(L, CV_16F);

  // Save the binarized image.
  String imageName = argv[1];
  removeFileExtension(imageName);
  imageName.append("-haralick.png");

  std::cout << "New File Name: " << imageName << std::endl;
  imwrite(imageName, L);

  // Opening the saved image.
  // Mat image = imread("test.png");
  // openWindow("Threshold Address", &image);

  // // Opening the original image for viewing.
  // // String windowName = "Address"; // Name of the window
  // // openWindow("Address Original", &inputImage);

  return 0;
}
