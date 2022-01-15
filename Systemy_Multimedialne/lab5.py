import numpy as np
import matplotlib.pyplot as plt
import cv2
import math
import scipy.fftpack


def dct2(a):
    return scipy.fftpack.dct( scipy.fftpack.dct( a.astype(float), axis=0, norm='ortho' ), axis=1, norm='ortho' )


def idct2(a):
    return scipy.fftpack.idct( scipy.fftpack.idct( a.astype(float), axis=0 , norm='ortho'), axis=1 , norm='ortho')


def convertToYCbCrFromRGB(image):
    return cv2.cvtColor(image, cv2.COLOR_RGB2YCrCb).astype(int)


def convertToRGBFromYCbCr(image):
    return cv2.cvtColor(image.astype(np.uint8), cv2.COLOR_YCrCb2RGB).astype(int)


def chromaSubsample(_C, mode):
    if mode == "4:4:4":
        return _C

    out = np.empty((_C.shape[0], int(_C.shape[1]/2)))
    if mode == "4:2:2":
        for row in range(0, _C.shape[0]):
            for col in range(0, _C.shape[1], 2):
                out[row][int(col/2)] = _C[row][col]
        return out


def chromaUnsample(_C, mode):
    if mode == "4:4:4":
        return _C

    out = np.empty((_C.shape[0], _C.shape[1]*2))
    if mode == "4:2:2":
        for row in range(0, _C.shape[0]):
            for col in range(0, _C.shape[1]):
                out[row][col*2] = _C[row][col]
                out[row][col*2+1] = _C[row][col]
        return out


def zigzag(A):
    template= n= np.array([
            [0,  1,  5,  6,  14, 15, 27, 28],
            [2,  4,  7,  13, 16, 26, 29, 42],
            [3,  8,  12, 17, 25, 30, 41, 43],
            [9,  11, 18, 24, 31, 40, 44, 53],
            [10, 19, 23, 32, 39, 45, 52, 54],
            [20, 22, 33, 38, 46, 51, 55, 60],
            [21, 34, 37, 47, 50, 56, 59, 61],
            [35, 36, 48, 49, 57, 58, 62, 63],
            ])
    if len(A.shape)==1:
        B=np.zeros((8,8))
        for r in range(0,8):
            for c in range(0,8):
                B[r,c]=A[template[r,c]]
    else:
        B=np.zeros((64,))
        for r in range(0,8):
            for c in range(0,8):
                B[template[r,c]]=A[r,c]
    return B

QY= np.array([
        [16, 11, 10, 16, 24,  40,  51,  61],
        [12, 12, 14, 19, 26,  58,  60,  55],
        [14, 13, 16, 24, 40,  57,  69,  56],
        [14, 17, 22, 29, 51,  87,  80,  62],
        [18, 22, 37, 56, 68,  109, 103, 77],
        [24, 36, 55, 64, 81,  104, 113, 92],
        [49, 64, 78, 87, 103, 121, 120, 101],
        [72, 92, 95, 98, 112, 100, 103, 99],
        ])

QC= np.array([
        [17, 18, 24, 47, 99, 99, 99, 99],
        [18, 21, 26, 66, 99, 99, 99, 99],
        [24, 26, 56, 99, 99, 99, 99, 99],
        [47, 66, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        ])

ones = np.ones((8, 8 ))


def compress(channel, samplingMode, qTable):
    sampled = chromaSubsample(channel, samplingMode)
    sampled = sampled.astype(int) - 128
    dct = dct2(sampled)

    out = np.zeros(sampled.shape[0]*sampled.shape[1])
    indx = 0
    for row in range(0, dct.shape[0], 8):
        for col in range(0, dct.shape[1], 8):
            zz = dct[row:row+8, col:col+8]
            temp = zigzag(zz)
            out[indx:indx+64] = np.round(temp/qTable.flatten()).astype(int)
            indx += 64
    return out


def decompress(channel, samplingMode, qTable):
    if samplingMode ==  "4:2:2":
        out = np.zeros((int(np.sqrt(channel.shape[0]*2)), int(np.sqrt(channel.shape[0]*2)/2)))
    else:
        out = np.zeros((int(np.sqrt(channel.shape[0])), int(np.sqrt(channel.shape[0]))))

    for idx, i in enumerate(range(0, channel.shape[0], 64)):
        dequantized = channel[i:i+64] * qTable.flatten()
        unzigzaged = zigzag(dequantized)

        x = (idx*8) % out.shape[1]
        y = int((idx*8)/out.shape[1])*8
        out[y:y+8, x:x+8] = unzigzaged

    undcted = idct2(out)+128
    undcted = np.clip(undcted, 0, 255).astype(np.uint8)
    unsampled = chromaUnsample(undcted, samplingMode)
    return unsampled


def cycle(channel, samplingMode, qTable):
    compressed = compress(channel, samplingMode, qTable)
    return decompress(compressed, samplingMode, qTable)

x = 1500
y = 1500
img = cv2.imread("pics/test3.jpg")[y:y+128, x:x+128]
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

fig, axs = plt.subplots(4, 2 , sharey=True   )
fig.set_size_inches(9, 13)
axs[0, 0].imshow(img)

img2 = convertToYCbCrFromRGB(img)
Y, Cr, Cb = np.clip(cv2.split(img), 0, 255)


axs[0,0].imshow(img)
axs[1,0].imshow(Y, cmap=plt.cm.gray)
axs[2,0].imshow(Cr, cmap=plt.cm.gray)
axs[3,0].imshow(Cb, cmap=plt.cm.gray)

sampling = "4:2:2"
one = False
Y2 = cycle(Y, sampling, ones if one else QY)
Cr2 = cycle(Cr, sampling, ones if one else QC)
Cb2 = cycle(Cb, sampling, ones if one else QC)

axs[0,1].imshow(np.dstack([Y2,Cr2,Cb2]).astype(np.uint8))
axs[1,1].imshow(Y2, cmap=plt.cm.gray)
axs[2,1].imshow(Cr2, cmap=plt.cm.gray)
axs[3,1].imshow(Cb2, cmap=plt.cm.gray)

plt.show()