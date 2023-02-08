from PIL import Image
import math
import statistics


# This function serves as a wrapper for image processing in a system.
def sweeping(parameters):

    # Get image height and width.
    width, height = parameters["image"].size

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


def darken(row, column, parameters):

    image = parameters["image"]
    N = parameters["filterN"]
    # Calculate New Pixel Value

    pixelValue = image.getpixel((column, row))

    # Put new pixel value in the image.
    image.putpixel((column, row), pixelValue - N)


# params: radius of filter.
def rmsFilter(row, column, parameters):

    # Radius of the filter.
    radius = parameters["filterN"]
    image = parameters["image"]

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


def getMedianColumn(image, row, column):

    values = []
    try:
        value1 = image.getpixel((column, row))
    except:
        # print(f"value 1 at {row}, {column}, not available.")
        pass
    else:
        values.append(value1)

    try:
        value2 = image.getpixel((column, row - 1))
    except:
        # print(f"value 2 at {row - 1}, {column}, not available.")
        pass
    else:
        values.append(value2)

    try:
        value3 = image.getpixel((column, row + 1))
    except:
        # print(f"value 3 at {row+1}, {column}, not available.")
        pass
    else:
        values.append(value3)

    # median = statistics.median(values)
    # # print(f"Values retrieved from ({row}, {column})\n{values}\nMedian: {median}")
    # return median
    if(len(values) > 0):
        median = statistics.median(values)
        # print(f"Values retrieved from ({row}, {column})\n{values}\nMedian: {median}")
        return median
    else:
        return None


def getMedianRow(image, row, column):

    values = []
    try:
        value1 = image.getpixel((column, row))
    except:
        # print(f"value 1 at {row}, {column}, not available.")
        pass
    else:
        values.append(value1)

    try:
        value2 = image.getpixel((column - 1, row))
    except:
        # print(f"value 2 at {row}, {column - 1}, not available.")
        pass
    else:
        values.append(value2)

    try:
        value3 = image.getpixel((column + 1, row))
    except:
        # print(f"value 3 at {row}, {column + 1}, not available.")
        pass
    else:
        values.append(value3)

    if(len(values) > 0):
        median = statistics.median(values)
        # print(f"Values retrieved from ({row}, {column})\n{values}\nMedian: {median}")
        return median
    else:
        return None

def keyNotInDict(dic, key):
    if key in dic.keys():
        return False
    else:
        return True


def edgeDetection(row, column, parameters):
    # Radius of the filter.
    threshhold = parameters["filterN"]
    image = parameters["image"]


    # Width and Height of the image for bounds checking.
    width, height = image.size

    # create a map of the f1 pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "f1")):
        parameters["f1"] = Image.new((width, height))
        f1Map = parameters["f1"]
    
    # create a map of the f1 pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "f2")):
        parameters["f2"] = Image.new((width, height))
        f2Map = parameters["f2"]

    # create a map of the gradient magnitude pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "gradientMagnitude")):
        parameters["gradientMagnitude"] = Image.new((width, height))
        gradientMagnitudeMap = parameters["gradientMagnitude"]


    # create a map of the gradient direction pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "gradientDirection")):
        parameters["gradientDirection"] = Image.new((width, height))
        gradientMagnitudeMap = parameters["gradientDirection"]

    # get the three columns left of this pixel
    # get the median from those three pixels
    # if(column -1 > 0 &&):
    leftMedian = getMedianColumn(image, row, column - 1)

    # get the three columns right of this pixel
    # get the median from those three pixels
    # if(column + 1 < width)
    rightMedian = getMedianColumn(image, row, column + 1)
    
    # calculate the differents between those two values to get f1.
    if(leftMedian == None):
        f1 = rightMedian
    elif(rightMedian == None):
        f1 = leftMedian
    else:
        f1 = rightMedian - leftMedian

    # generating the values of f2.
    f1Map.putpixel((column, row), f1)

    # get the three rows above this pixel
    # get the median from those three pixels
    upperMedian = getMedianRow(image, row - 1, column)

    # get the three rows below this pixel
    # get the median from those three pixels
    lowerMedian = getMedianRow(image, row + 1, column)

    # calculate the difference between those two values for f2.
    if(upperMedian == None):
        f2 = lowerMedian
    elif(lowerMedian == None):
        f2 = upperMedian
    else:
        f2 = upperMedian - lowerMedian

    # generating the values of f2.
    f2Map.putpixel((column, row), f2)


    # calculating gradient magnitude. Adding it to the pixel map of the gradient magnitude
    gradientMagnitude = math.sqrt((f2 * f2) + (f1 * f1))
    gradientMagnitudeMap.putpixel((column, row), gradientMagnitude)



    # calculating gradient diection. Adding it to the pixel map of the gradient magnitude
    gradientDirection = math.atan2(f2, f1)
    gradientDirectionDegrees = (180 / math.pi) * gradientDirection
    gradientMagnitudeMap.putpixel((column, row), gradientDirectionDegrees)

    if(gradientMagnitude > threshhold):
        print(f"The gradient ({gradientMagnitude}) is bigger than the threshold ({threshhold}) at ({row},{column})")


def filterSelectorWrapper(row, column, parameters):

    # Accessing the filter type within paramters.
    filterType = parameters["filterType"]

    # print(f"Inside of filterSelectorWrapper: parameters: {parameters}")

    if filterType == "rmsFilter":
        rmsFilter(row, column, parameters)

    elif filterType == "darken":
        darken(parameters)

    elif filterType == "edgeDetection":
        edgeDetection(row, column, parameters)


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
    filterType = "edgeDetection"

    filterSize = 35

    parameters = {"image": inputImage, "filterType": filterType, "filterN": filterSize}

    # Conducts processing on the image.
    sweeping(parameters)

    # Save New Image
    inputImage.save("edge-detection.png")

    print("Coordinate Format: [Column, Row]")

    # Printing Image Pixel Values as well as a mean filter pixel values for comparison.
    print("Printing rms filter pixel values (N=35):")
    printImagePixelValues(inputImage)

    # meanAverageBlurImage = originalImage.copy().filter(ImageFilter.BoxBlur(13))
    # print("Printing Mean Filter pixel values (N=13):")
    # printImagePixelValues(meanAverageBlurImage)
    # meanAverageBlurImage.save('meanFilterImage.png')


if __name__ == "__main__":
    main()
