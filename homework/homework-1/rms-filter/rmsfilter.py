
from PIL import Image
    



def kernelModification(image, kernel):

    print(image, kernel)



def convolution(width, height, image, inputKernel):
    print(f"Inside Image with parameters: {width}, {height}, {image}")
    for i in range(width):
        for j in range(height):
            pixel = image.getpixel((i, j))
            print(f"Width: {i}\nLength: {j}\nValue: {pixel}\n\n")

def main():

    # Open image using PIL
    inputImage = Image.open('cman.png')


    # Extracting pixel map.
    pixel_map = inputImage.load()
    
    # Extracting the width and height of the image.
    width, height = inputImage.size

    print(width, height)

    convolution(width, height, inputImage, kernel='')



    print(pixel_map)
    






    # # convert an array into an image.
    # imageFromArray = Image.fromarray(imageArray, mode='L')


    # # save new image.
    # imageFromArray.save('test.png')









if __name__ == "__main__":
    main()