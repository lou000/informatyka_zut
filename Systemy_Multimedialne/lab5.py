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
    assert J>=a and J>=b and ((a==0 or b==0) or (a == b)) and _C.shape[0]%2==0 and _C.shape[1]%J==0
    C = _C.copy()
    newY = _C.shape[0]/2 if (a==0 or b==0) else _C.shape[0]
    newX = _C.shape[1]*(a/J) if a>0 else _C.shape[1]*(b/J)
    B = np.empty((int(newY), int(newX)))

    iA = 0
    iB = 0
    iY = 0
    for row in range(0, C.shape[0], 2):
        for col in range(0, C.shape[1], J):
            if a == 1:
                B[iY][iA] = C[row][col]
                iA += 1
            elif a!=0:
                step = math.ceil(J / a)
                start = 0 if round(J/a)>1 else step
                remainder = a - round(J/step)
                for i in range(start*remainder, J, step):
                    B[iY][iA] = C[row][col+i]
                    iA += 1

            if b == 1:
                y = iY if a==0 else iY+1
                B[y][iB] = C[row+1][col]
                iB += 1
            elif b!=0:
                y = iY if a == 0 else iY + 1
                step = math.ceil(J / b)
                start = 0 if round(J/b)>1 else step
                remainder = b - round(J/step)
                for i in range(start*remainder, J, step):
                    B[y][iB] = C[row+1][col+i]
                    iB += 1

        iA = 0
        iB = 0
        if a==0 or b==0:
            iY+=1
        else:
            iY+=2
    return B


test = np.array([[1,2,3,4,5,6,7,8], [9,10,11,12,13,14,15,16]])

print(chromaSubsample(test, 4, 0, 1))
