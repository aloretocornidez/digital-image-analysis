#include <opencv2/opencv.hpp>
#include "convenience.hpp"

using namespace cv;

void openWindow(String windowName, Mat *image);
// void convolution(Mat *input, Mat *output);

int main(int argc, char **argv)
{

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

  // Creating an image buffer.
  Mat buffer = inputImage.clone();
  Mat output = inputImage.clone();

  // Running otsu's method to best threshold (with the largest invariance.)
  double maxSigma = 0;
  int bestTheshold = -1;

  // Test each sigma value.
  for (int currentThreshold = 0; currentThreshold < 256; currentThreshold++)
  {
    std::cout << "Testing New Threshold: " << currentThreshold << std::endl;

    // Parameters used in otsu's method for each new threshold.
    double currentSigma = 0;
    int pixelsAboveThreshold = 0;

    // Get the number of row and column pixels
    int rows = buffer.rows;
    int columns = buffer.cols;

    // Total number of pixels in the image.
    int totalImagePixels = rows * columns;

    // Scan each row and column and calculate the value.
    for (int row = 0; row < rows; row++)
    {
      for (int column = 0; column < columns; column++)
      {
        int pixelValue = buffer.at<Vec3b>(row, column)[0];

        if (pixelValue < currentThreshold)
        {
          output.at<Vec3b>(row, column)[0] = 255; // blue
        }
        else
        {
          output.at<Vec3b>(row, column)[0] = 0;
        }
      }
    }

    // Calculate the current sigma value.
    

    // Found the best threshold.
    if (currentSigma > maxSigma)
    {
      maxSigma = currentSigma;
      bestTheshold = currentThreshold;
    }
  }

  // Use the best threshold to run binarization of the image.
  for (int row = 0; row < buffer.rows; row++)
  {
    for (int column = 0; column < buffer.cols; column++)
    {
      int pixelValue = buffer.at<Vec3b>(row, column)[0];

      if (pixelValue < bestTheshold)
      {
        output.at<Vec3b>(row, column)[0] = 255;
      }
      else
      {
        output.at<Vec3b>(row, column)[0] = 0;
      }
    }
  }

  // Save the best image.
  imwrite("test.png", output);

  // Opening the saved image.
  Mat image = imread("test.png");
  openWindow("Threshold Address", &image);

  // Opening the original image for viewing.
  String windowName = "Address"; // Name of the window
  openWindow("Address Original", &inputImage);

  return 0;
}

void openWindow(String windowName, Mat *image)
{

  namedWindow(windowName); // Create a window

  imshow(windowName, *image); // Show our image inside the created window.

  waitKey(0); // Wait for any keystroke in the window

  destroyWindow(windowName); // destroy the created window
}
