#include "homework-6.hpp"
#include "erosion.hpp"
#include "dilation.hpp"
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{

  // Usage for the program
  if (argc != 2)
  {
    std::cout << "Usage: {programName} path/to/image" << std::endl;
    return -1;
  }

  // Read the image file
  cv::Mat inputImage = imread(argv[1], cv::IMREAD_GRAYSCALE);

  // Check for failure when opening the image.
  if (inputImage.empty())
  {
    std::cout << "Could not open or find the image" << std::endl;
    return -1;
  }

  // Creating Output image buffers.
  // TODO: Make sure to change names back to image_{1..4} for homework submission.
  cv::Mat dilatedInputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8U);
  cv::Mat erodedInputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8U);
  cv::Mat image_3 = cv::Mat(inputImage.rows, inputImage.cols, CV_8U);
  cv::Mat image_4 = cv::Mat(inputImage.rows, inputImage.cols, CV_8U);

  // This is the kernel size that is being used.
  const int KERNEL_SIZE = 11;

  // Creating the First Image (Dilation)
  dilation::dilateImage(inputImage, dilatedInputImage, KERNEL_SIZE);
  // showTwoImages("Input Image", inputImage, "Image 1 (Dilation)", dilatedInputImage);

  // Creating the Second Image (Erosion)
  erosion::erodeImage(inputImage, erodedInputImage, KERNEL_SIZE);
  // showTwoImages("Input Image", inputImage, "Image 2 (Erosion)", erodedInputImage);

  // Creating the Third Image (Erosion then Dilation)
  dilation::dilateImage(erodedInputImage, image_3, KERNEL_SIZE);
  // showTwoImages("Eroded Image", erodedInputImage, "Image 3 (Erosion --> Dilation)", image_3);

  // // Creating the Fourth Image (Dilation then Erosion)
  erosion::erodeImage(dilatedInputImage, image_4, KERNEL_SIZE);
  // showTwoImages("Dilated Image", dilatedInputImage, "Image 4 (Dilation --> Erosion)", image_4);

  // Generating the image name
  cv::String imageName = argv[1];
  removeFileExtension(imageName);

  // Saving Images
  cv::imwrite(imageName + "-image-1.png", dilatedInputImage);
  cv::imwrite(imageName + "-image-2.png", erodedInputImage);
  cv::imwrite(imageName + "-image-3.png", image_3);
  cv::imwrite(imageName + "-image-4.png", image_4);


  // // Freeing Memory
  dilatedInputImage.release();
  erodedInputImage.release();
  image_3.release();
  image_4.release();



  

  return 0;
}
