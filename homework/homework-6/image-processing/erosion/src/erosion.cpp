#include <iostream>
#include "erosion.hpp"

using namespace cv;
using std::cout;
using std::endl;

erosion::erosion()
{
  cout << "Erosion Object Constructed" << endl;
}

erosion::~erosion()
{
  cout << "Erosion Object Destroyed" << endl;
}

void erosion::printHello()
{
  cout << "Erosion says hello." << endl;
}

void erosion::erodeImage(Mat &input, Mat &output, int kernelSize)
{
  // int kernelSize = 11;
  cout << "Eroding Image using Personal Implementation" << endl;

  // Scan every pixel in the image.
  for (int row = 0; row < input.rows; row++)
  {
    for (int column = 0; column < input.cols; column++)
    {
      // If the current pixel is a foreground pixel then the dilation operation is performed on that pixel.
      if (input.at<uchar>(row, column) == 0)
      {
        // std::cout << "Pixel is equal to zero: ("<< (int)input.at<uchar>(row,column) << ")" << std::endl;
        // Perform dilation.
        for (int i = -kernelSize / 2; i < kernelSize / 2; i++)
        {
          for (int j = -kernelSize / 2; j < kernelSize / 2; j++)
          {

            // Get the pixel value of the input at coordinate (row, column)
            int dilationRow = row + i;
            int dilationColumn = column + j;

            // This is a bounds check.
            if (dilationRow < output.rows && dilationColumn < output.cols && dilationRow >= 0 && dilationColumn >= 0)
            {
              // cout << "Dilation Coords: (" << dilationRow << "," << dilationColumn << ")" << endl;
              output.at<uchar>(dilationRow, dilationColumn) = 0;
            }
          } // dilation

        } // dilation row

      } // if a foreegound
      else
      {
        output.at<uchar>(row, column) = 255;
      }

    } // column

  } // row
}

void erosion::openCVErodeImage(Mat &input, Mat &output)
{
  cout << "Eroding Image using OpenCV" << endl;

  int kernel_size = 11;

  // Create a solid 11 x 11 square kernel.
  Mat k = Mat::ones(kernel_size, kernel_size, CV_8U);

  // Erode the image.
  cv::erode(input, output, k);
}