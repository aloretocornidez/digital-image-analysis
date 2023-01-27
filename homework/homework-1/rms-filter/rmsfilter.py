from PIL import Image
    




def kernelModification(row, column, image):

    # Calculate New Pixel Value


    pixelValue = image.getpixel((column, row))


    # Put new pixel value in the image.
    image.putpixel((column, row), pixelValue - 100)




# Prints the pixel values in an image.
def printImagePixelValues(image):
    width, height = image.size
    for column in range(width):
        for row in range(height):

            # Get Current Pixel Value
            pixelValue = image.getpixel((column, row))
            # print(pixelValue)


# This function serves as a wrapper for image processing in a system.
def imageProcessing(width, height, image):
    # Moves the coordinate at which convolution occurs.
    for column in range(width):
        for row in range(height):
            kernelModification(row, column, image)

def main():

    # Open image using PIL
    inputImage = Image.open('cman.png')


    # Extracting pixel map.
    pixelMap = inputImage.load()
    
    # Extracting the width and height of the image.
    width, height = inputImage.size


    

    # Conducts processing on the image.
    imageProcessing(width, height, inputImage)


    # Print Pixel Values
    printImagePixelValues(inputImage)
                


    # Save New Image
    inputImage.save('test.png')


    






    # convert an array into an image.
    # imageFromArray = Image.fromarray(pixelMap, mode='L')










if __name__ == "__main__":
    main()