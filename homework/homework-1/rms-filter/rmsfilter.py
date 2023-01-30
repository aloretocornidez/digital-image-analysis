from PIL import Image
import math
    




# This function serves as a wrapper for image processing in a system.
def imageProcessing(width, height, image, params):
    # Moves the coordinate at which convolution occurs.
    for column in range(width):
        for row in range(height):
            filterWrapperSelector(row, column, image, params)






# params: radius of filter.
def rmsFilter(row, column, image, params):
    
    # Radius of the filter.
    radius = params[1]

    # Width and Height of the image for bounds checking.
    width, height = image.size


    sumOfPixelValues = 0
    totalNumberOfPixels = 0

    for horizontal in range(radius):
        for vertical in range(radius):

            # pythagorian theorem for euclidian distance.
            euclidianDistance = math.sqrt(horizontal**2 + vertical**2)


            # Pixel is included in calculations if within the radius.
            if(euclidianDistance < radius):
                
                # set up parameters for a the function call to find the values within the radius.
                parameters = image, row, column, horizontal, vertical 

                # function returns the number of pixels that were found in the image.
                sumOfPixelValuesInKernel, numberOfPixelsInKernel = getKernelValues(parameters)

                # Add the sums in a kernel to the total sums of the image.
                sumOfPixelValues = sumOfPixelValues + sumOfPixelValuesInKernel
                totalNumberOfPixels = totalNumberOfPixels + numberOfPixelsInKernel

                # print(sumOfPixelValues, totalNumberOfPixels)


                # image.putpixel((column, row), newPixelValue)


    newPixelValue = math.sqrt((1 / totalNumberOfPixels) * sumOfPixelValues )

    newPixelValue = int(newPixelValue)
    image.putpixel((column, row), newPixelValue)

    
                

    # # Calculate New Pixel Value
    # pixelValue = image.getpixel((column, row))

    # # Put new pixel value in the image.
    # image.putpixel((column, row), pixelValue)



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
        sumOfPixelValues = sumOfPixelValues + value ** 2
        numberOfPixels = numberOfPixels + 1
        

    try:
        value = image.getpixel((column - horizontal, row + vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value ** 2
        numberOfPixels = numberOfPixels + 1
        
    
    try:
        value = image.getpixel((column + horizontal, row - vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value ** 2
        numberOfPixels = numberOfPixels + 1

    try:
        value = image.getpixel((column + horizontal, row + vertical))
    except:
        pass
    else:
        sumOfPixelValues = sumOfPixelValues + value ** 2
        numberOfPixels = numberOfPixels + 1

    return sumOfPixelValues, numberOfPixels

    

def darken(row, column, image, params):

    N = params[1]
    # Calculate New Pixel Value


    pixelValue = image.getpixel((column, row))


    # Put new pixel value in the image.
    image.putpixel((column, row), pixelValue - N)

def filterWrapperSelector(row, column, image, parameters):

    # Accessing the filter type within paramters.
    filterType = parameters[0]

    if(filterType == 'rmsFilter'):
        rmsFilter(row, column, image, parameters)
    
    elif(filterType == 'darken'):
        darken(row, column, image, parameters)

# Prints the pixel values in an image.
def printImagePixelValues(image):
    width, height = image.size
    for column in range(width):
        for row in range(height):

            # Get Current Pixel Value
            pixelValue = image.getpixel((column, row))
            print(pixelValue)




def main():

    # Open image using PIL
    originalImage = Image.open('cman.png')

    # Create Input Buffer Image
    inputImage = originalImage.copy()

    
    # Extracting the width and height of the image.
    width, height = inputImage.size

    params = ('rmsFilter', 5)


    

    # Conducts processing on the image.
    imageProcessing(width, height, inputImage, params)


    # Print Pixel Values
    # printImagePixelValues(inputImage)
                


    # Save New Image
    inputImage.save('test.png')


    






    # convert an array into an image.
    # imageFromArray = Image.fromarray(pixelMap, mode='L')










if __name__ == "__main__":
    main()