#include <opencv2/opencv.hpp>
#include "convenience.hpp"

void openWindow(cv::String windowName, cv::Mat *image);

int main(int argc, char **argv)
{

  // Usage for the program
  if (argc != 2)
  {
    std::cout << "Usage: {programName} path/to/image" << std::endl;
    return -1;
  }

  // Read the image file
  cv::Mat inputImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

  // Check for failure when opening the image.
  if (inputImage.empty())
  {
    std::cout << "Could not open or find the image" << std::endl;
    return -1;
  }

  // Creating an image buffer.
  cv::Mat buffer = inputImage.clone();

  cv::Mat output = inputImage.clone();

  // Do image processing.
  for (int row = 0; row < buffer.rows; row++)
  {
    for (int column = 0; column < buffer.cols; column++)
    {
      int pixelValue = buffer.at<cv::Vec3b>(row, column)[0]; // blue
      // int value2 = buffer.at<cv::Vec3b>(row, column)[1]; // green
      // int value3 = buffer.at<cv::Vec3b>(row, column)[2]; // red


      if(pixelValue)


      std::cout << "(Row, Column): (" << row << "," << column << ")"
                << "\nPixel Value: " << pixelValue << std::endl; //", " << value2 << ", " << value3 << std::endl;

      buffer.at<cv::Vec3b>(row, column)[0] = 200; // blue
    }
  }

  cv::imwrite("test.png", buffer);

  cv::imshow("Testing Image", cv::imread("test.png"));
  cv::waitKey(0);

  // Opening the image for viewing.
  cv::String windowName = "Address"; // Name of the window
  openWindow(windowName, &inputImage);

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