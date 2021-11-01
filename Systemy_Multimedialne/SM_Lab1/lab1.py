import numpy as np
import matplotlib.pyplot as plt
import cv2


def plotManyThings(image):
    R = image[:, :, 0]
    G = image[:, :, 1]
    B = image[:, :, 2]

    Y1 = 0.299  * R + 0.587  * G + 0.114  * B
    Y2 = 0.2126 * R + 0.7152 * G + 0.0722 * B

    plt.subplot(3, 3, 1)
    plt.imshow(image)
    plt.subplot(3, 3, 2)
    plt.imshow(Y1, cmap=plt.cm.gray)
    plt.subplot(3, 3, 3)
    plt.imshow(Y2, cmap=plt.cm.gray)
    plt.subplot(3, 3, 4)
    plt.imshow(R, cmap=plt.cm.gray)
    plt.subplot(3, 3, 5)
    plt.imshow(G, cmap=plt.cm.gray)
    plt.subplot(3, 3, 6)
    plt.imshow(B, cmap=plt.cm.gray)

    kopiaR = image.copy()
    kopiaR[:, :, 1:] = 0
    kopiaG = image.copy()
    kopiaG[:, :, [0, 2]] = 0
    kopiaB = image.copy()
    kopiaB[:, :, :2] = 0
    plt.subplot(3, 3, 7)
    plt.imshow(kopiaR)
    plt.subplot(3, 3, 8)
    plt.imshow(kopiaG)
    plt.subplot(3, 3, 9)
    plt.imshow(kopiaB)
    plt.show()


# plotManyThings(plt.imread('pic1.png'))
# plotManyThings(plt.imread('pic2.jpg')[200:500, 200:500])

def colorFit(_col, palette):
    a = np.linalg.norm(palette-_col, axis=1)
    return palette[np.argmin(a)]


def colorFitStack(_col, palette):
    return palette[np.abs(palette - _col).argmin()]


def randomDither(_image):
    r = np.random.rand(_image.shape[0], _image.shape[1])
    for row in range(0, _image.shape[0]):
        for col in range(0, _image.shape[1]):
            _image[row, col] = _image[row, col] > r[row, col]

def organizedM2(_image):



image = plt.imread('0009.png')
image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
image2 = image.copy()
nCol = 4
table = np.linspace(0, 1, nCol).reshape((nCol, 1))

for row in range(0, image.shape[0]):
    for pixel in range(0, image.shape[1]):
        image2[row, pixel] = colorFit(image2[row, pixel], table)


plt.subplot(1, 3, 1)
plt.imshow(image, cmap=plt.cm.gray)

plt.subplot(1, 3, 2)
plt.imshow(image2, cmap=plt.cm.gray)

image3 = image.copy()
randomDither(image3)
plt.subplot(1, 3, 3)
plt.imshow(image3, cmap=plt.cm.gray)


plt.show()
