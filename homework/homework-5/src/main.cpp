#include <opencv2/opencv.hpp>
#include "functions.hpp"

using namespace cv;



int main(int argc, char **argv)
{

  // Usage for the program
  if (argc != 2)
  {
    std::cout << "Usage: {programName} path/to/image" << std::endl;
    return -1;
  }

  // // Read the image file
  // Mat inputImage = imread(argv[1], IMREAD_GRAYSCALE);

  // // Check for failure when opening the image.
  // if (inputImage.empty())
  // {
  //   std::cout << "Could not open or find the image" << std::endl;
  //   return -1;
  // }

  // Mat output = inputImage.clone();

  // // A histogram of the pixel values in the pixels in the image.
  // int pixelValueHistogram[256];
  // double probabilityDistribution[256];
  // double jValues[256];

  // // Populating the grayscale histogram and creating the
  // populateHistogram(inputImage, pixelValueHistogram, probabilityDistribution);

  // // Populating the probability distribution array.
  // int totalImagePixels = inputImage.rows * inputImage.cols;
  // populateDistributionArray(probabilityDistribution, pixelValueHistogram, totalImagePixels);

  // // Test each different threshold value and calculate the values.
  // double q1, q2, mu1, mu2, sigmaSquared1, sigmaSquared2;
  // for (int currentThreshold = 0; currentThreshold < 256; currentThreshold++)
  // {

  //   calculateJValues(currentThreshold, probabilityDistribution,
  //                    q1, q2,
  //                    mu1, mu2,
  //                    sigmaSquared1, sigmaSquared2,
  //                    jValues);
  // }

  // // printArrayValues(pixelValueHistogram, probabilityDistribution, jValues);

  // // Find the best threshold using the jValues.
  // int bestThreshold = 0;
  // findMinimumJValue(bestThreshold, jValues);

  // // Use the best threshold to run binarization of the image.
  // binarizeImage(output, bestThreshold);

  // // Save the binarized image.
  // String imageName = argv[1];
  // removeFileExtension(imageName);
  // imageName.append("-binarized.png");

  // imwrite(imageName, output);

  // // // Opening the saved image.
  // // Mat image = imread("test.png");
  // // openWindow("Threshold Address", &image);

  // // Opening the original image for viewing.
  // // String windowName = "Address"; // Name of the window
  // // openWindow("Address Original", &inputImage);

  return 0;
}
