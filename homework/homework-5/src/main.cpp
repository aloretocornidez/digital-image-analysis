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
  initializeLabels(L);


  updateLabels(L);

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
