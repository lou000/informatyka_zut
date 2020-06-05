import numpy as np
import scipy.sparse as sc
import pandas as pd
import math


# 1
def freq(x, prob=True):
    count = [[], []]
    for cell in x:
        found = False
        for i, y in enumerate(count[0]):
            if y == cell:
                found = True
                cell[i] += 1
        if not found:
            count[0].append(cell)
            count[1].append(1)
    if prob:
        pi = []
        size = len(x)
        for y in count[1]:
            pi.append(y / size)
        return count[0], pi
    else:
        return count[0], count[1]


# 2
def freq2(x, y, prob=True):
    size = len(x) if len(x) < len(y) else len(y)
    count = [[], []]
    for i in range(size):
        tp = (x[i], y[i])
        try:
            idx = count[0].index(tp)
        except ValueError:
            idx = 0
        if idx:
            count[1][idx] += 1
        else:
            count[0].append(tp)
            count[1].append(1)
    if prob:
        pi = []
        for y in count[1]:
            pi.append(y / size)
        return count[0], pi
    else:
        return count[0], count[1]


# 3
def entropy(x):
    _sum = 0
    idc, y = freq(x)
    for p in y:
        _sum -= p*math.log(p, 2)
    return _sum


def info_gain(x, y):
    _sum = 0
    idc, z = freq2(x, y)
    for p in z:
        _sum -= p*math.log(p, 2)
    return entropy(x) + entropy(y) - _sum


# 4
zoo = pd.read_csv('zoo.csv')

data = [[], []]

for col in zoo.columns:
    data[0].append(col)
    data[1].append(info_gain(col))
