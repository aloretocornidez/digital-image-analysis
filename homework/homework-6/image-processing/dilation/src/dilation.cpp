#include "dilation.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;
using std::cout;
using std::endl;

dilation::dilation()
{
  std::cout << "Dilation Object Constructed" << std::endl;
}

dilation::~dilation()
{
  std::cout << "Dilation Object Destroyed" << std::endl;
}

void dilation::printHello()
{
  std::cout << "Dilation says hello." << std::endl;
}

void dilation::dilateImage(Mat &input, Mat &output)
{
  std::cout << "Dilating Image using Personal Implementation" << std::endl;

  // Mat kernel = Mat::ones(kernelSize, kernelSize, CV_8U);

  // Scan every pixel in the image.
  for (int row = 0; row < input.rows; row++)
  {
    for (int column = 0; column < input.cols; column++)
    {

      // If the current pixel is a foreground pixel then the dilation operation is performed on that pixel.
      if ((int)input.at<uchar>(row, column) > 0)
      {

        // Perform dilation.
        int kernelSize = 11;
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
              output.at<uchar>(dilationRow, dilationColumn) = 255;
            }

          } // dilation column

        } // dilation row

      } // if a foreegound

    } // column

  } // row

} // dilation

void dilation::openCVDilateImage(Mat &input, Mat &output)
{
  std::cout << "Dilating Image using OpenCV" << std::endl;

  int SIZE = 11;
  Mat k = Mat::ones(SIZE, SIZE, CV_8U);
  cv::dilate(input, output, k);
}
