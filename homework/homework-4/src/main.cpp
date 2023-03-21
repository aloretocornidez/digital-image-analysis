#include <opencv2/opencv.hpp>
#include "convenience.hpp"

void openWindow(cv::String windowName, cv::Mat *image);

int main(int argc, char **argv)
{
  // Read the image file
  cv::Mat inputImage = cv::imread("address.png");

  // Check for failure when opening the image.
  if (inputImage.empty())
  {
    std::cout << "Could not open or find the image" << std::endl;
    std::cin.get(); // wait for any key press
    return -1;
  }

  // Creating an image buffer.
  cv::Mat clone = inputImage.clone();







  // scanning each pixel
  for (int row = 0; row < clone.rows; row++)
  {
    for (int column = 0; column < clone.cols; column++)
    {
      int value = clone.at<cv::Vec3b>(row, column)[1];
      std::cout << "(Row, Column): (" << row << "," << column << ")"<< "\nPixel Value: " << value <<  std::endl;


    }
  }










  // Opening the image for viewing.
  cv::String windowName = "Address"; // Name of the window
  openWindow(windowName, &clone);

  // cv::namedWindow(windowName); // Create a window
  // cv::imshow(windowName, image); // Show our image inside the created window.
  // cv::waitKey(0); // Wait for any keystroke in the window
  // cv::destroyWindow(windowName); // destroy the created window

  return 0;
}

void openWindow(cv::String windowName, cv::Mat *image)
{

  cv::namedWindow(windowName); // Create a window

  cv::imshow(windowName, *image); // Show our image inside the created window.

  cv::waitKey(0); // Wait for any keystroke in the window

  cv::destroyWindow(windowName); // destroy the created window
}