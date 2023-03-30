#include <opencv2/opencv.hpp>
#include "functions.hpp"
#include <memory>

using namespace cv;

struct Matrix
{

  int rows, columns;
  uint64_t *matrix;

  Matrix(int rows, int columns) : rows(rows), columns(columns)
  {
    // This approach uses a single array since "new" cannot create
    // multidimensional arrays.
    // It also spares the performance cost of an array of arrays.
    matrix = new uint64_t[columns * rows];
  }

  ~Matrix()
  {
    // Release the memory after destroying the Matrix-object
    delete[] matrix;
  }

  /*Access the element at position [r]ow and [c]olumn.*/
  int getElement(int r, int c)
  {
    // matrix[c][r] is rewritten as matrix[column + columns * rows]
    // -> matrix <=> Single memory block
    return matrix[c + columns * r];
  }

  /*Set the element at position [r]ow and [c]olumn with given [val]ue.*/
  void setElement(int r, int c, int val)
  {
    matrix[c + columns * r] = val;
  }
};

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

  // Creating Output image to keep the input image as a buffer.
  Mat L = inputImage.clone();

  L.convertTo(L, CV_64F);

  // Initialize the Labels in the image.
  uint64_t nextLabel = 1;

  for (int row = 0; row < inputImage.rows; row++)
  {
    for (int column = 0; column < inputImage.cols; column++)
    {
      // If pixel is a foreground pixel.
      if (inputImage.at<uint64_t>(row, column) > 0)
      {
        L.at<uint64_t>(row, column) = nextLabel;
        nextLabel++;
      }
      else
      {
        L.at<uint64_t>(row, column) = 0;
      }
    }
  }

  bool change = false;

  // iteratively update the labels.
  do
  {
    // Top-down scan
    for (int row = 0; row < inputImage.cols; row++)
    {
      for (int column = 0; column < inputImage.cols; column++)
      {
        if (L.at<uint64_t>(row, column) != 0)
        {
          std::cout << "Top-down found: (" << row << "," << column << ")" << std::endl;
        }
      }
    }

    // Bottom-up scan
    for (int row = 0; row < inputImage.cols; row++)
    {
      for (int column = 0; column < inputImage.cols; column++)
      {
        if (L.at<uint64_t>(row, column) != 0)
        {
          std::cout << "Bottom Up found: (" << row << "," << column << ")" << std::endl;
        }
      }
    }
    change = true;

  } while (change == false);

  // Save the binarized image.
  String imageName = argv[1];
  removeFileExtension(imageName);
  imageName.append("-haralick.png");

  imwrite(imageName, L);

  // Opening the saved image.
  // Mat image = imread("test.png");
  // openWindow("Threshold Address", &image);

  // // Opening the original image for viewing.
  // // String windowName = "Address"; // Name of the window
  // // openWindow("Address Original", &inputImage);

  return 0;
}
