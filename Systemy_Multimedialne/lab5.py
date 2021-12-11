import numpy as np
import matplotlib.pyplot as plt
import cv2
import math


def convertToYCbCrFromRGB(image):
    return cv2.cvtColor(image, cv2.COLOR_RGB2YCrCb).astype(int)


def convertToRGBFromYCbCr(image):
    return cv2.cvtColor(image.astype(np.uint8), cv2.COLOR_YCrCb2RGB).astype(int)


def chromaSubsample(_C, J, a, b):
    # this might seem complicated and it is, but it works for any reasonable J:a:b, from what I could test
    assert J>=a and J>=b and (a>0 or b>0) and _C.shape[0]%2==0 and _C.shape[1]%J==0
    C = _C.copy()
    for row in range(0, C.shape[0], 2):
        for col in range(0, C.shape[1], J):
            if a == 1:
                for i in range(1, J):
                    C[row][col+i] = C[row][col]
            elif a!=0:
                step = math.ceil(J / a)
                start = 0 if round(J/a)>1 else step
                remainder = a - round(J/step)
                for i in range(start*remainder, J, step):
                    for j in range(i+1, i+step):
                        if col+j<C.shape[1]:
                            C[row][col+j] = C[row][col+i]
            if b == 1:
                for i in range(1, J):
                    C[row+1][col+i] = C[row+1][col]
            elif b!=0:
                step = math.ceil(J / b)
                start = 0 if round(J/b)>1 else step
                remainder = b - round(J/step)
                for i in range(start*remainder, J, step):
                    for j in range(i+1, i+step):
                        if col+j<C.shape[1]:
                            C[row+1][col+j] = C[row+1][col+i]
            if a == 0:
                C[row] = C[row+1]
            if b == 0:
                C[row+1] = C[row]
    return C


test = np.array([[1,2,3,4,5,6,7,8], [9,10,11,12,13,14,15,16]])

print(chromaSubsample(test, 4, 3, 2))
