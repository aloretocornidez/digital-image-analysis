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

  // Running kittler's method to best threshold.
  // This method assumes an 8-bit image.
  double maxSigma = 0;

  // Get the number of row and column pixels
  int rows = buffer.rows;
  int columns = buffer.cols;

  // A histogram of the pixel values in the pixels in the image.
  int pixelValueHistogram[256];

  double probabilityDistribution[256];

  double jValues[256];

  // Total number of pixels in the image.
  int totalImagePixels = rows * columns;

  // Populate the pixel value histogram and probability histogram.
  for (int i = 0; i < 256; i++)
  {
    pixelValueHistogram[i] = 0;
    int temp = 0;

    // Scan the entire image.
    for (int row = 0; row < buffer.rows; row++)
    {
      for (int column = 0; column < buffer.cols; column++)
      {

        // Get the value of the pixel at that coordinate.
        int pixelValue = inputImage.at<Vec3b>(row, column)[0];

        // Atomic add the value of the pixel.

        if (pixelValue == i)
        {
          temp++;
          // std::cout << pixelValue << " " << temp << std::endl;
        }
      }
    }

    // Setting the value of the number of pixels that match the current threshold.
    pixelValueHistogram[i] = temp;

    // Populating the probability distribution histogram after all of the pixels are counted.
    probabilityDistribution[i] = (double)pixelValueHistogram[i] / (double)totalImagePixels;

    // std::cout << "Pixel Value Histogram at " << i << ": " << pixelValueHistogram[i] << std::endl;
  }

  // Test each different threshold value.
  for (int currentThreshold = 0; currentThreshold < 256; currentThreshold++)
  {
    // std::cout << "Testing New Threshold: " << currentThreshold << std::endl;

    // Calculating q1 for the specified theshold.
    double q1 = 0;
    // This gets the sum of all of the pixels that are below the specified threshold.
    for (int i = 0; i < currentThreshold; i++)
    {
      q1 = q1 + probabilityDistribution[i];
    }

    // This is the second value for Kittler's and Illingworth's method.
    double q2 = 1 - q1;

    // Printing the qu values.
    std::cout << "q1: " << q1 << " q2: " << q2 << std::endl;

    // Calculate the new mu values. THey are initialized to zero because we know that q1 and q2 are positive.
    double mu1 = 0;
    double mu2 = 0;

    for (int i = 0; i < currentThreshold; i++)
    {
      mu1 = mu1 + (i * probabilityDistribution[i] / q1);
    }
    for (int i = currentThreshold + 1; i < 256; i++)
    {
      mu2 = mu2 + (i * probabilityDistribution[i] / q2);
    }



    // TODO: Figure out the edge case whenever q1 or q2 are equal to 1 and zero.



    // std::cout << "mu1: " << mu1 << " mu2: " << mu2 << std::endl;

    // Calculating the new sigma values.
    double sigmaSquared1 = 0;
    double sigmaSquared2 = 0;

    // Calculating sigmaSquared1
    for (int i = 0; i < currentThreshold; i++)
    {
      sigmaSquared1 = sigmaSquared1 + ((1 - mu1) * (1 - mu1) * probabilityDistribution[i] / q1);
    }

    // Calculating sigmaSquared2
    for (int i = currentThreshold + 1; i < 256; i++)
    {
      sigmaSquared2 = sigmaSquared2 + ((1 - mu2) * (1 - mu2) * probabilityDistribution[i] / q2);
    }

    double sigma1 = sqrt(sigmaSquared1);
    double sigma2 = sqrt(sigmaSquared2);

    // std::cout << "sigma1: " << sigma1 << " sigma2: " << sigma2 << std::endl;

    jValues[currentThreshold] = -q1 * log10(q1) - q2 * log10(q2) + q1 * log10(sigma1) + q2 * log10(sigma2);

    // std::cout << "jValue[" << currentThreshold << "]: " << jValues[currentThreshold] << std::endl;

    /*
// Parameters used in kittler method for each new threshold.
double currentSigma = 0;
int pixelsAboveThreshold = 0;
// Scan each row and column and calculate the value.
for (int row = 0; row < rows; row++)
{
  for (int column = 0; column < columns; column++)
  {
    int pixelValue = buffer.at<Vec3b>(row, column)[0];

    if (pixelValue < currentThreshold)
    {
      // Do nothing for now.
    }
    else
    {
      pixelsAboveThreshold++;
    }
  }
}

// Calculate the current sigma value.

    // Found the best threshold.
if (currentSigma > maxSigma)
{
  maxSigma = currentSigma;
  bestTheshold = currentThreshold;

  std::cout << "New Best Threshdol and sigma found: " << maxSigma << " & " << bestTheshold << std::endl;
}
*/
  }

  // Find the best threshold using the jValues.
  int bestTheshold = -1;

  double bestJValue = sizeof(double);
  bestTheshold = 0;

  for (int i = 0; i < 256; i++)
  {

    if (jValues[i] < bestJValue)
    {
      bestTheshold = i;
      // std::cout << bestTheshold << std::endl;
    }
  }

  // std::cout << "Best Threshold: " << bestTheshold << std::endl;
  // std::cout << "Best J Value: " << bestJValue << std::endl;

  // Use the best threshold to run binarization of the image.
  for (int row = 0; row < buffer.rows; row++)
  {
    for (int column = 0; column < buffer.cols; column++)
    {
      int pixelValue = buffer.at<Vec3b>(row, column)[0];

      if (pixelValue < 91)
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
