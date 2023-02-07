from PIL import Image
import math


# This function serves as a wrapper for image processing in a system.
def sweeping(parameters):

    # Get image height and width.
    width, height = parameters[0].size

    # Moves the coordinate at which convolution occurs.
    for column in range(width):
        for row in range(height):
            filterSelectorWrapper(row, column, parameters)




def getKernelValues(parameters):

    # parse parameters
    image, row, column, horizontal, vertical = parameters

    # print(image.getpixel((column - horizontal, row - vertical)))

    sumOfPixelValues = 0
    numberOfPixels = 0

    # calculate all new dots.
    try:
        value = image.getpixel((column - horizontal, row - vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value**2
        numberOfPixels = numberOfPixels + 1

    try:
        value = image.getpixel((column - horizontal, row + vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value**2
        numberOfPixels = numberOfPixels + 1

    try:
        value = image.getpixel((column + horizontal, row - vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value**2
        numberOfPixels = numberOfPixels + 1

    try:
        value = image.getpixel((column + horizontal, row + vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value**2
        numberOfPixels = numberOfPixels + 1

    return sumOfPixelValues, numberOfPixels




def darken(row, column, params):


    image = params[0]
    N = params[1]
    # Calculate New Pixel Value

    pixelValue = image.getpixel((column, row))

    # Put new pixel value in the image.
    image.putpixel((column, row), pixelValue - N)


# params: radius of filter.
def rmsFilter(row, column, params):

    # Radius of the filter.
    radius = params[2]
    image = params[0]

    # Width and Height of the image for bounds checking.
    width, height = image.size
    sumOfPixelValues = 0
    totalNumberOfPixels = 0

    for horizontal in range(radius):
        for vertical in range(radius):

            # pythagorian theorem for euclidian distance.
            euclidianDistance = math.sqrt(horizontal**2 + vertical**2)

            # Pixel is included in calculations if within the radius.
            if euclidianDistance < radius:

                # set up parameters for a the function call to find the values within the radius.
                parameters = image, row, column, horizontal, vertical

                # function returns the number of pixels that were found in the image.
                sumOfPixelValuesInKernel, numberOfPixelsInKernel = getKernelValues(
                    parameters
                )

                # Add the sums in a kernel to the total sums of the image.
                sumOfPixelValues = sumOfPixelValues + sumOfPixelValuesInKernel
                totalNumberOfPixels = totalNumberOfPixels + numberOfPixelsInKernel

                # print(sumOfPixelValues, totalNumberOfPixels)

                # image.putpixel((column, row), newPixelValue)

    newPixelValue = math.sqrt((1 / totalNumberOfPixels) * sumOfPixelValues)

    newPixelValue = int(newPixelValue)
    image.putpixel((column, row), newPixelValue)

    # # Calculate New Pixel Value
    # pixelValue = image.getpixel((column, row))

    # # Put new pixel value in the image.
    # image.putpixel((column, row), pixelValue)


def edgeDetection(parameters):
    # Radius of the filter.
    radius = parameters[2]
    image = parameters[0]

    # Width and Height of the image for bounds checking.
    width, height = image.size
    sumOfPixelValues = 0
    totalNumberOfPixels = 0

    for horizontal in range(radius):
        for vertical in range(radius):
            


def filterSelectorWrapper(row, column, parameters):

    # Accessing the filter type within paramters.
    filterType = parameters[1]

    if filterType == "rmsFilter":
        rmsFilter(row, column, parameters)

    elif filterType == "darken":
        darken(parameters)

    elif filterType == 'edgeDetection':
        edgeDetection(parameters)


# Prints the pixel values in an image.
def printImagePixelValues(image):

    rowArray = [309, 310, 311, 312, 313]
    columnArray = [309, 310, 311, 312, 313]

    print("Image Pixel Coordinates")

    for row in rowArray:
        for column in columnArray:
            print(f"[{column}, {row}]", end=" ")
        print("")

    print("\nImage Pixel Values:")

    for row in rowArray:
        for column in columnArray:

            # Get Current Pixel Value
            pixelValue = image.getpixel((column, row))
            print(pixelValue, end=" ")

        print("")










# @click.command()
# @click.option('-N', default=1, help='The size of N that is used for the Filter (if applicable)')
# @click.option('-f', default='darken', help='filter type. Examples: rmsFilter, darken, edgeDetection')




def main():

    # Open image using PIL
    originalImage = Image.open("cman.png")

    # Create input image buffer
    inputImage = originalImage.copy()

    # Setting up to call edge detection with a threshold of 35.
    filterType = 'edgeDetection'

    filterSize = 3

    parameters = (inputImage, filterType, filterSize)

    # Conducts processing on the image.
    sweeping(parameters)



    # Save New Image
    inputImage.save("edge-detection.png")


    print('Coordinate Format: [Column, Row]')

    # Printing Image Pixel Values as well as a mean filter pixel values for comparison.
    print("Printing rms filter pixel values (N=35):")
    printImagePixelValues(inputImage)

    # meanAverageBlurImage = originalImage.copy().filter(ImageFilter.BoxBlur(13))
    # print("Printing Mean Filter pixel values (N=13):")
    # printImagePixelValues(meanAverageBlurImage)
    # meanAverageBlurImage.save('meanFilterImage.png')


if __name__ == "__main__":
    main()
