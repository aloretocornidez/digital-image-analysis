from PIL import Image, ImageFilter
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


def postSweeping(parameters):

    if(parameters["filterType"] == "edgeDetection"):
        print(f"Edge Detection Post Processing")
        # performing non maximum supression
        nonMaximumSuppression(parameters)
        
        # converting non maximum supression image into a black and white image.
        parameters["output"] = parameters["nms"].copy()
        nmsToEdge(parameters)

    






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

def nmsToEdge(parameters):
    image = parameters["output"]
    width, height = image.size

    for row in range(height):
        for column in range(width):
            if(image.getpixel((column, row)) == 1):
                image.putpixel((column, row), 255)

def convertToDegrees(parameters):
    image = parameters["gradientDirectionDegrees"]
    width, height = image.size

    for row in range(height):
        for column in range(width):
            value = image.getpixel((column, row)) * (180 / math.pi)
            image.putpixel((column, row), value)


def nonMaximumSuppression(parameters):

    # create a map of the  pixels and add it to the image parameters.
    gradientMagnitudeMap = parameters["gradientMagnitude"]
    gradientDirectionMap = parameters["gradientDirection"]

    width, height = parameters["image"].size
    if(keyNotInDict(parameters, "nms")):
        parameters["nms"] = Image.new('L', (width, height))
    nmsMap = parameters["nms"]


    PI = math.pi

    

    for row in range(height):
        for column in range(width):
            magnitude = gradientMagnitudeMap.getpixel((column, row))
            direction = gradientDirectionMap.getpixel((column, row))

            # set this point as the largest gradient value
            magnitudeIsLargest = 1


            # set the direction to 0 <= theta <= pi
            if direction < 0:
                direction = direction + math.pi


            ## These sets of if conditions each look at a direction within 45 degrees of each other
            ## If the magnidute of the adjecent pixel is larger than the current set pixel in the center,
            ## Then the magnitude of the pixel is not the largest and the pixel in the NMS map is set to 0
            ## if the current pixel is the largest, then the pixel is set to 1.
            # direction is 0 < theta < 45

            # print(f"nmsMap.size: [{nmsMap.size}]")
            # print(f"gradientMagnitude.size: [{gradientMagnitudeMap.size}]")
            # print(f"gradientDirection.size: [{gradientDirectionMap.size}]")
            # print(f"(Row, Column): [{row}, {column}] | (Height, Width): [{height}, {width}]")


            if (direction < PI / 4):
               
                # Boundary check
                if((row - 1 >= 0) and (column + 1 < width)):
                    # Check for the largest magitude
                    test = gradientDirectionMap.getpixel((column + 1, row - 1))
                    test = gradientDirectionMap.getpixel((column + 1, row))

                    if (math.tan(direction) * gradientMagnitudeMap.getpixel((column + 1, row - 1)) + (1 - math.tan(direction)) * gradientMagnitudeMap.getpixel((column + 1, row)) > magnitude):
                        magnitudeIsLargest = 0

                # Boundary check
                if((row + 1 < height) and (column - 1 >= 0)):
                    # Check if the magnitude is the largest
                    if (math.tan(direction) * gradientMagnitudeMap.getpixel((column - 1, row + 1)) + (1 - math.tan(direction)) * gradientMagnitudeMap.getpixel((column - 1, row)) > magnitude):
                        magnitudeIsLargest = 0
            

            # if the direction 45 <= theta <= 90
            elif ( (direction >= PI / 4) and (direction < PI / 2)):

                # boundary check
                if((row - 1 >= 0) and (column + 1 < width)):
                    # compare for largest magnitude value.
                    # cos(x) / sin(x) = cot(x)
                    if((math.cos(direction) / math.sin(direction)) * gradientMagnitudeMap.getpixel((column + 1, row - 1)) + (1 - (math.cos(direction) / math.sin(direction))) * gradientMagnitudeMap.getpixel((column, row-1)) > magnitude):
                        magnitudeIsLargest = 0

                # boundary check
                if((row + 1 < height) and (column - 1 >= 0)):
                   if( (math.cos(direction) / math.sin(direction)) * gradientMagnitudeMap.getpixel((column - 1, row + 1)) + (1 - (math.cos(direction) / math.sin(direction))) * gradientMagnitudeMap.getpixel((column, row+1)) > magnitude):
                        magnitudeIsLargest = 0

            # if the direction 90 <= theta <= 135
            elif ((direction >= PI / 2) and (direction < 3 * PI / 2)):

                # boundary check
                if((row - 1 >= 0) and (column - 1 >= 0)):
                    # compare for largest magnitude value.
                    if((-1 * (math.cos(direction) / math.sin(direction))) * gradientMagnitudeMap.getpixel((column - 1, row - 1)) + (1 + (math.cos(direction) / math.sin(direction))) * gradientMagnitudeMap.getpixel((column, row-1)) > magnitude):
                        magnitudeIsLargest = 0

                # boundary check
                if((row + 1 < height) and (column + 1 < width)):
                    if((-1 * (math.cos(direction) / math.sin(direction))) * gradientMagnitudeMap.getpixel((column + 1, row + 1)) + (1 + (math.cos(direction) / math.sin(direction))) * gradientMagnitudeMap.getpixel((column, row+1)) > magnitude):
                        magnitudeIsLargest = 0

            # if the direction 135 <= theta <= 180
            elif ((direction >= 3 * PI / 2)):

                # boundary check
                if((row - 1 >= 0) and (column - 1 >= 0)):
                    # compare for largest magnitude value.
                    if((-1 * math.tan(direction)) * gradientMagnitudeMap.getpixel((column - 1, row - 1)) + (1 + math.tan(direction)) * gradientMagnitudeMap.getpixel((column-1, row)) > magnitude):
                        magnitudeIsLargest = 0

                # boundary check
                if((row + 1 < height) and (column + 1 < width)):
                    if((-1 * math.tan(direction)) * gradientMagnitudeMap.getpixel((column + 1, row + 1)) + (1 + math.tan(direction)) * gradientMagnitudeMap.getpixel((column+1, row)) > magnitude):
                        magnitudeIsLargest = 0

            # Setting the pixel value of the nms map, it is still 1 if the value is the largest out of the pixels next to it.
            # The value is going to either be 1 or zero.
            nmsMap.putpixel((column, row), magnitudeIsLargest)
            



    # check if the gradient magnitude at (r,c) is a local maximum.
    


def edgeDetection(row, column, parameters):
    # Radius of the filter.
    threshhold = parameters["filterN"]
    image = parameters["image"]


    # Width and Height of the image for bounds checking.
    width, height = image.size

    # create a map of the f1 pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "f1")):
        parameters["f1"] = Image.new('F', (width, height))
    f1Map = parameters["f1"]
    
    # create a map of the f1 pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "f2")):
        parameters["f2"] = Image.new('F', (width, height))
    f2Map = parameters["f2"]

    # create a map of the gradient magnitude pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "gradientMagnitude")):
        # Map is initialized with a 32-bit floating point capbility.
        parameters["gradientMagnitude"] = Image.new('F', (width, height))
    gradientMagnitudeMap = parameters["gradientMagnitude"]


    # create a map of the gradient direction pixels and add it to the image parameters.
    if(keyNotInDict(parameters, "gradientDirection")):
        # Map is initialized with a 32-bit floating point capbility.
        parameters["gradientDirection"] = Image.new('F', (width, height))
    gradientDirectionMap = parameters["gradientDirection"]

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
        f2 = (upperMedian - lowerMedian)
        # print(f"f2 at ({row},{column}): {f2}")

    # generating the values of f2.
    f2Map.putpixel((column, row), f2)

    # print(f2Map.getpixel((column, row)))


    # calculating gradient magnitude. Adding it to the pixel map of the gradient magnitude
    gradientMagnitude = math.sqrt((f2 * f2) + (f1 * f1))
    # print(f"gradient magnitude at ({row},{column}): {gradientMagnitude}")


    if(gradientMagnitude > threshhold):
        gradientMagnitudeMap.putpixel((column, row), gradientMagnitude)
    else:
        gradientMagnitudeMap.putpixel((column, row), 0)





    # calculating gradient diection. Adding it to the pixel map of the gradient magnitude
    gradientDirection = math.atan2(f2, f1)
    gradientDirectionMap.putpixel((column, row), gradientDirection)

    # converting direction to degrees.
    # gradientDirectionDegrees = (180 / math.pi) * gradientDirection
    # gradientDirectionMap.putpixel((column, row), gradientDirectionDegrees)



    

    


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


def printCoordinateSystem(rowArray, columnArray):


    # print("Image Pixel Coordinates")

    for row in rowArray:
        for column in columnArray:
            print(f"[{column}, {row}]", end="\t")
        print("")


# Prints the pixel values in an image.
def printImagePixelValues(image, rowArray, columnArray):


    # print("Image Pixel Values:")

    for row in rowArray:
        for column in columnArray:

            # Get Current Pixel Value
            pixelValue = round(image.getpixel((column, row)), 2)
            print(pixelValue, end="\t")

        print("")


# @click.command()
# @click.option('-N', default=1, help='The size of N that is used for the Filter (if applicable)')
# @click.option('-f', default='darken', help='filter type. Examples: rmsFilter, darken, edgeDetection')


def main():

    # Open image using PIL
    imageFileName = "cman.png"
    originalImage = Image.open(imageFileName)
    print(f"Image opened: [{imageFileName}]")

    # Create input image buffer
    inputImage = originalImage.copy()
    print(f"Image copy created as buffer.")

    # Setting up to call edge detection with a threshold of 35.
    filterType = "edgeDetection"
    filterSize = 35
    parameters = {"image": inputImage, "filterType": filterType, "filterN": filterSize}
    print(f"Image parameters set: [{parameters}]")



    # Conducts processing on the image.
    print(f"Beginning Initial Image Processing")
    sweeping(parameters)
    print(f"Completed Initial Image Processing")

    print(f"Initializing post processing")
    postSweeping(parameters)
    print(f"Completed post processing")

    

    



    # These are the pixels that are being graded.
    rowArray = [359, 360, 361, 362, 363]
    columnArray = [149, 150, 151, 152, 153]

    print('\nPrinting Coordinate System')
    printCoordinateSystem(rowArray, columnArray)

    print('\nPrinting f1 values')
    printImagePixelValues(parameters["f1"], rowArray, columnArray)

    print('\nPrinting f2 values')
    printImagePixelValues(parameters["f2"],rowArray, columnArray)

    print('\nPrinting gradient magnitude values')
    printImagePixelValues(parameters["gradientMagnitude"], rowArray, columnArray)


    print('\nPrinting gradient direction values')
    # converting gradient direction values to degrees.
    parameters["gradientDirectionDegrees"] = parameters["gradientDirection"].copy()
    convertToDegrees(parameters)
    # printing values.
    printImagePixelValues(parameters["gradientDirectionDegrees"], rowArray, columnArray)

    print('\nPrinting non maximum suppression values')
    printImagePixelValues(parameters["nms"], rowArray, columnArray)


    print('\nPrinting output pixels')
    printImagePixelValues(parameters["output"], rowArray, columnArray)
    




    # Save New Image
    newImageFileName = "edge-detection.png"
    print(f"Saving new name: [newImageFileName: {newImageFileName}]")
    parameters["output"].save(newImageFileName)




    # Printing Image Pixel Values as well as a mean filter pixel values for comparison.
    # print("Coordinate Format: [Column, Row]")
    # print("Printing rms filter pixel values (N=35):")
    # printImagePixelValues(inputImage)

    # meanAverageBlurImage = originalImage.copy().filter(ImageFilter.BoxBlur(13))
    # print("Printing Mean Filter pixel values (N=13):")
    # printImagePixelValues(meanAverageBlurImage)
    # meanAverageBlurImage.save('meanFilterImage.png')


if __name__ == "__main__":
    main()
