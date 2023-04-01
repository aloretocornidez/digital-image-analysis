#include "functions.hpp"

void populateHistogram(Mat &inputImage, int *pixelValueHistogram, double *probabilityDistribution)
{
  int rows = inputImage.rows;
  int columns = inputImage.cols;

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

void initializeLabels(Mat &inputImage)
{
  // Set up the first label.
  uint64_t nextLabel = 1;

  for (int row = 0; row < inputImage.rows; row++)
  {
    for (int column = 0; column < inputImage.cols; column++)
    {
      // If pixel is a foreground pixel, initialize a label
      if (inputImage.at<uint64_t>(row, column) > 0)
      {
        inputImage.at<uint64_t>(row, column) = nextLabel;
        nextLabel++;
      }
      else
      {
        // Makes sure there are no negative pixels in the image.
        inputImage.at<uint64_t>(row, column) = 0;
      }
    }
  }
}

void updateLabels(Mat &inputImage)
{
  // Iteratively update the labels.
  bool imageUpdated;
  do
  {
    // Set this variale to check if any changes have been made to the image.
    imageUpdated = false;

    // Top-down scan
    bool topDownUpdate = false;
    for (int row = 0; row < inputImage.cols; row++)
    {
      for (int column = 0; column < inputImage.cols; column++)
      {

        scanImage(inputImage, row, column, topDownUpdate);
        // if (topDownUpdate)
        // {
        //   // std::cout << "Image was updated in the top-down scan." << std::endl;
        // }
      }
    }

    // Bottom-up scan
    bool bottomUpUpdate = false;
    for (int row = inputImage.rows; row < 0; row--)
    {
      for (int column = inputImage.cols; column < 0; column--)
      {
        scanImage(inputImage, row, column, bottomUpUpdate);
        // if (bottomUpUpdate)
        // {
        //   std::cout << "Image was updated in the bottom-up scan." << std::endl;
        // }
      }
    }

    imageUpdated = topDownUpdate || bottomUpUpdate;

  }
  // If the image has been updated in this iteration, then you continue looping until there are no updates to the image.
  while (imageUpdated == true);
}

void scanImage(Mat &inputImage, int row, int column, bool &imageUpdated)
{
  // if the pixel is not a forground pixel, find the minimum value of the pixels surrounding this pixel and set them all to the minimum value.
  uint64_t pixelValue = inputImage.at<uint64_t>(row, column);
  if (pixelValue != 0)
  {
    // std::cout << "Found a non border pixel at (" << row << "," << column << "): " << pixelValue << std::endl;

    // Find the minimum pixel value within the current pixel's range.

    uint64_t miniumPixelValue = findMinimumPixel(inputImage, row, column);
    // std::cout << "Minimum Pixel Value found in vicinity: " << miniumPixelValue << std::endl;

    if (pixelValue != miniumPixelValue)
    {
      // std::cout << "New minimum pixel found: " << miniumPixelValue << "\nUpdating pixel value from : " << pixelValue << std::endl;

      imageUpdated = true;
      inputImage.at<uint64_t>(row, column) = miniumPixelValue;

      // This was used to check if the value of the minimum pixel value was correctly assigned
      if ((uint64_t)miniumPixelValue != inputImage.at<uint64_t>(row, column))
      {
        std::cout << "Value of pixel in image after assignment: " << inputImage.at<uint64_t>(row, column) << "\n" << std::endl;
      }
    }

    // int pixel = inputImage.at<uint64_t>(row, column);
    // std::cout << "Bottom Up found: (" << row << "," << column << ") --> " << pixel << std::endl;
  }
}

uint64_t findMinimumPixel(Mat &inputImage, int row, int column)
{
  uint64_t currentMinimumPixel = inputImage.at<uint64_t>(row, column);

  // Looking at all adjecent pixels.
  // i shall be used for rows.
  for (int i = -1; i <= 1; i++)
  {

    // j shall be used for columns.
    for (int j = -1; j <= 1; j++)
    {

      // If the pixel is within the image.
      if (isValidPixel(inputImage, i, j, row, column))
      {
        // Set test pixel to compare to current minimum.
        uint64_t testPixel = inputImage.at<uint64_t>(row + i, column + j);

        // std::cout << "Pixels that are being compared | TestPixel: "<< testPixel << " | Current Minimum: "<< currentMinimumPixel << std::endl;

        // Set the new minumum pixel.
        if (testPixel < currentMinimumPixel && testPixel != 0)
        {

          currentMinimumPixel = testPixel;
        }
      }
    }
  }
  return currentMinimumPixel;
}

// Checks to make sure that the coordinates that are being accessed are valid coordinates.
bool isValidPixel(Mat &inputImage, int i, int j, int row, int column)
{
  return row + i >= 0 && row + i < inputImage.rows && column + j >= 0 && column + j < inputImage.cols;
}

void processLabels(Mat &inputImage)
{
  // std::cout << "Processing Labels." << std::endl;

  // Scan the image and fill a vector with each unique label.
  for (int row = 0; row < inputImage.rows; row++)
  {
    for (int column = 0; column < inputImage.cols; column++)
    {
      
      if (inputImage.at<uint64_t>(row, column) != 0)
      {
        std::cout << "(" << row << "," << column << "): " << inputImage.at<uint64_t>(row, column) << std::endl;
      }
    }
  }
}