#include "functions.hpp"


void populateHistogram(Mat &inputImage, int *pixelValueHistogram, double *probabilityDistribution)
{
  int rows = inputImage.rows;
  int columns = inputImage.cols;
  int totalImagePixels = rows * columns;

  // Populate the pixel value histogram and probability histogram.
  // Initialize the histogram to zeros.
  for (int i = 0; i < 256; i++)
  {
    pixelValueHistogram[i] = 0;
  }

  // Scan the entire image and populate the pixel values.
  for (int row = 0; row < rows; row++)
  {
    for (int column = 0; column < columns; column++)
    {

      // Get the value of the pixel at that coordinate.
      int pixelValue = inputImage.at<uint8_t>(row, column);

      // Incrementing the value of the number of pixels that match the current threshold.
      pixelValueHistogram[pixelValue]++;
    }
  }
}

void populateDistributionArray(double *probabilityDistribution, int *pixelValueHistogram, int totalImagePixels)
{

  // Populate the pixel value histogram and probability histogram.
  for (int i = 0; i < 256; i++)
  {
    // Populating the probability distribution histogram after all of the pixels are counted.
    probabilityDistribution[i] = (double)pixelValueHistogram[i] / (double)totalImagePixels;

    // std::cout << "Pixel Value Histogram at " << i << ": " << pixelValueHistogram[i] << std::endl;
  }
}

void calculateJValues(int threshold, double *probabilityDistribution, double &q1, double &q2, double &mu1, double &mu2, double &sigmaSquared1, double &sigmaSquared2, double *jValues)
{

  // Calculating q1 for the specified theshold.
  q1 = 0;
  // This gets the sum of all of the pixels that are below the specified threshold.
  for (int i = 0; i < threshold; i++)
  {
    q1 += probabilityDistribution[i];
  }

  // This is the second value for Kittler's and Illingworth's method.
  q2 = 1 - q1;

  // Calculate the new mu values. THey are initialized to zero because we know that q1 and q2 are positive.
  mu1 = 0;
  mu2 = 0;

  for (int i = 0; i < threshold; i++)
  {
    mu1 += ((double)i * (probabilityDistribution[i] / q1));
  }

  for (int i = threshold + 1; i < 256; i++)
  {
    mu2 += ((double)i * (probabilityDistribution[i] / q2));
  }

  // TODO: Figure out the edge case whenever q1 or q2 are equal to 1 and zero.

  // std::cout << "mu1: " << mu1 << " mu2: " << mu2 << std::endl;

  // Calculating the new sigma values.
  sigmaSquared1 = 0;
  sigmaSquared2 = 0;

  // Calculating sigmaSquared1
  for (int i = 0; i < threshold; i++)
  {
    sigmaSquared1 += ((i - mu1) * (i - mu1) * probabilityDistribution[i] / q1);
  }

  // Calculating sigmaSquared2
  for (int i = threshold + 1; i < 256; i++)
  {
    sigmaSquared2 += ((i - mu2) * (i - mu2) * probabilityDistribution[i] / q2);
  }

  double sigma1 = sqrt(sigmaSquared1);
  double sigma2 = sqrt(sigmaSquared2);

  // std::cout << "sigma1: " << sigma1 << " sigma2: " << sigma2 << std::endl;

  // jValues[currentThreshold] = -q1 * std::log10(q1) - q2 * std::log10(q2) + q1 * std::log10(sigma1) + q2 * std::log10(sigma2);
  jValues[threshold] = 0 - (q1 * std::log(q1)) - (q2 * std::log(q2)) + (q1 * std::log(sigma1)) + (q2 * std::log(sigma2));
}

void printArrayValues(int *pixelValueHistogram, double *probabilityDistribution, double *jValues)
{
  // PRINTING ALL OF THE ARRAY VALUES
  // std::cout << "Printing Arrays: i pixelHistogram probabilityDistribution jValues " << std::endl;
  for (int i = 0; i < 256; i++)
  {
    std::cout << i << " " << pixelValueHistogram[i] << " " << probabilityDistribution[i] << " " << jValues[i] << std::endl;
  }
  // for (int i = 0; i < 256; i++)
  // {
  //   std::cout << i << " " << pixelValueHistogram[i] << std::endl;
  // }
  // for (int i = 0; i < 256; i++)
  // {
  //   std::cout << i << " " << probabilityDistribution[i] << std::endl;
  // }
  // for (int i = 0; i < 256; i++)
  // {
  //   std::cout << i << " " << jValues[i] << std::endl;
  // }
}

void findMinimumJValue(int &minimumJValueIndex, double *jValues)
{
  // Set the best value to the largest value possible.
  double bestJValue = std::numeric_limits<double>::max();

  // Check each possible j value to find the smallest jValue.
  for (int i = 0; i < 256; i++)
  {
    double currentJValue = jValues[i];

    // Find the minimum J value.
    if (
        // Check if the value is not a number.
        !isnan(currentJValue) &&

        // Check if the value not +-infinity.
        !std::isinf(currentJValue) &&

        // Check if the value is the new minimum.
        currentJValue < bestJValue)
    {
      // std::cout << "Updating best j value from (" << bestJValue << ") to (" << bestJValue << ") At index: " << i << std::endl;
      bestJValue = currentJValue;
      minimumJValueIndex = i;
    }
  }
}

void binarizeImage(Mat &output, int threshold)
{

  std::cout << "Binarizing Image with threshold found in Kittler's Algorithm: " << threshold << std::endl;

  // Use the best threshold to run binarization of the image.
  for (int row = 0; row < output.rows; row++)
  {
    for (int column = 0; column < output.cols; column++)
    {
      int pixelValue = output.at<uint8_t>(row, column);

      if (pixelValue < threshold)
      {
        output.at<uint8_t>(row, column) = 255;
      }
      else
      {
        output.at<uint8_t>(row, column) = 0;
      }
    }
  }
}

void removeFileExtension(String &imageName)
{
  size_t last = imageName.find_last_of(".");
  imageName = imageName.substr(0, last);
}

void openWindow(String windowName, Mat *image)
{

  namedWindow(windowName); // Create a window

  imshow(windowName, *image); // Show our image inside the created window.

  waitKey(0); // Wait for any keystroke in the window

  destroyWindow(windowName); // destroy the created window
}
