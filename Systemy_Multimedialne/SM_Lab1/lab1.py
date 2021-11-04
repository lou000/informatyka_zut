import numpy as np
import matplotlib.pyplot as plt
import cv2
from skimage.util import img_as_float


def colorFit(_col, _palette):
    a = np.linalg.norm(_palette - _col, axis=1)
    return _palette[np.argmin(a)]


def quantize(_image, _palette):
    outImage = _image.copy()
    for _row in range(0, _image.shape[0]):
        for _pixel in range(0, _image.shape[1]):
            outImage[_row, _pixel] = colorFit(_image[_row, _pixel], _palette)
    return outImage


def randomDither(_image):
    outImage = _image.copy()
    r = np.random.rand(_image.shape[0], _image.shape[1])
    for _row in range(0, _image.shape[0]):
        for _col in range(0, _image.shape[1]):
            outImage[_row, _col] = _image[_row, _col] > r[_row, _col]
    return outImage


def organizedM2(_image, _palette):
    outImage = _image.copy()
    m2 = np.matrix('0,8,2,10;'
                   '12,4,14,6;'
                   '3,11,1,9;'
                   '15,7,13,5')
    Mpre = 1 / 16 * (m2 + 1) - 0.5
    for _row in range(0, _image.shape[0]):
        for _col in range(0, _image.shape[1]):
            outImage[_row, _col] = colorFit(outImage[_row, _col] + Mpre[_row % 4, _col % 4], _palette)
    return outImage


def Floyd_Steinberg(_image, _palette):
    outImage = _image.copy()
    for _row in range(1, _image.shape[0]-1):
        for _col in range(1, _image.shape[1]-1):
            oldpixel = outImage[_row, _col].copy()
            newpixel = colorFit(oldpixel, _palette)
            outImage[_row, _col] = newpixel
            quant_error = oldpixel - newpixel
            outImage[_row + 1, _col    ] = np.clip(outImage[_row + 1, _col    ] + quant_error * 7 / 16, 0, 1)
            outImage[_row - 1, _col + 1] = np.clip(outImage[_row - 1, _col + 1] + quant_error * 3 / 16, 0, 1)
            outImage[_row    , _col + 1] = np.clip(outImage[_row    , _col + 1] + quant_error * 5 / 16, 0, 1)
            outImage[_row + 1, _col + 1] = np.clip(outImage[_row + 1, _col + 1] + quant_error * 1 / 16, 0, 1)
    return outImage


def do_it_all(_image, _palette):

    # check if image is greyscale
    greyscale = len(_image.shape) < 3

    _cmap = None
    width = 4
    if greyscale:
        _cmap = plt.cm.gray
        if len(_palette) == 2:
            width = 5

    _ax = plt.subplot(1, width, 1)
    _ax.set_axis_off()
    _ax.set_title('Oryginał')
    plt.imshow(_image, cmap=_cmap)

    _ax = plt.subplot(1, width, 2)
    _ax.set_axis_off()
    _ax.set_title('Kwantyzacja')
    plt.imshow(quantize(_image, _palette), cmap=_cmap)

    _ax = plt.subplot(1, width, 3)
    _ax.set_axis_off()
    _ax.set_title('Dithering zorganizowany')
    plt.imshow(organizedM2(_image, _palette), cmap=_cmap)

    _ax = plt.subplot(1, width, 4)
    _ax.set_axis_off()
    _ax.set_title('Floyd_Steinberg')
    plt.imshow(Floyd_Steinberg(_image, _palette), cmap=_cmap)

    if greyscale and len(_palette) == 2:
        _ax = plt.subplot(1, width, 5)
        _ax.set_axis_off()
        _ax.set_title('Dithering losowy')
        plt.imshow(randomDither(_image), cmap=_cmap)

    plt.tight_layout()
    plt.show()


image = img_as_float(plt.imread('0008.png'))
# image = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
image2 = img_as_float(plt.imread('0014.jpg'))
print(image.shape)

# Greyscale palette
greyscalePalette_1bit = np.linspace(0, 1, 2).reshape((2, 1))
greyscalePalette_2bit = np.linspace(0, 1, 4).reshape((4, 1))
greyscalePalette_4bit = np.linspace(0, 1, 8).reshape((8, 1))


# Color palettes
colorPalette_8bit = np.matrix('0., 0., 0.;'
                              '0., 0., 1.;'
                              '0., 1., 0.;'
                              '0., 1., 1.;'
                              '1., 0., 0.;'
                              '1., 0., 1.;'
                              '1., 1., 0.;'
                              '1., 1., 1.')
colorPalette_16bit = np.matrix('0,0,0;'
                               '0,1,1;'
                               '0,0,1;'
                               '1,0,1;'
                               '0,0.5,0;'
                               '0.5,0.5,0.5;'
                               '0,1,0;'
                               '0.5,0,0;'
                               '0,0,0.5;'
                               '0.5,0.5,0;'
                               '0.5,0,0.5;'
                               '1,0,0;'
                               '0.75,0.75,0.75;'
                               '0,0.5,0.5;'
                               '1,1,1;'
                               '1,1,0')

do_it_all(image, greyscalePalette_1bit)
do_it_all(image, greyscalePalette_2bit)
do_it_all(image, greyscalePalette_4bit)
# do_it_all(image2, colorPalette_8bit)
# do_it_all(image2, colorPalette_16bit)

# quantize with minimal colors
colorPalette_special = np.matrix('0.820, 0.318, 0.180;'
                                 '0.859, 0.820, 0.780;'
                                 '0.008, 0.016, 0.012;'
                                 '0.349, 0.149, 0.067;'
                                 '0.918, 0.686, 0.192;'
                                 '0.745, 0.247, 0.078;'
                                 '0.212, 0.102, 0.059;'
                                 '0.373, 0.149, 0.082;'
                                 '0.710, 0.235, 0.157;'
                                 '0.851, 0.631, 0.157;'
                                 '0.843, 0.843, 0.647;'
                                 '0.875, 0.506, 0.125;'
                                 '0.918, 0.514, 0.188;'
                                 '0.506, 0.165, 0.098;'
                                 '0.835, 0.333, 0.157;'
                                 '0.812, 0.235, 0.165;'
                                 '0.655, 0.220, 0.141')

# ax = plt.subplot(1, 2, 1)
# ax.set_axis_off()
# plt.imshow(image2)
#
# ax = plt.subplot(1, 2, 2)
# ax.set_axis_off()
# plt.imshow(quantize(image2, colorPalette_special))
#
# plt.show()