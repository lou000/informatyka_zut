from sklearn.datasets import fetch_rcv1
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
                count[1][i] += 1
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
        _sum -= p * math.log(p, 2)
    return _sum


def info_gain(x, y):
    _sum = 0
    idc, z = freq2(x, y)
    for p in z:
        _sum -= p * math.log(p, 2)
    return entropy(x) + entropy(y) - _sum


# 4
zoo = pd.read_csv('zoo.csv')

data = [[], []]

for col in zoo.columns:
    data[0].append(col)
    data[1].append(info_gain(zoo[col], zoo['type']))
print(np.array(data))

# 5
# Jeżeli dobrze rozumiem co to znaczy atrybut rzadki to moje funkcje działają na nich domyślnie
# Jeżeli w poleceniu chodziło o to żeby przekazać do funkcji obiekt np. csc_matrix z pakietu scipy.sparse
# to powinno być to sprecyzowane.
# Dla przyjmowanych danych typ zmiennych rzadkich musi być zdefiniowany, czasami będzie to 0, ale może to być NULL itd.

# row = np.array([0, 2, 2, 0, 1, 2])
# col = np.array([0, 0, 1, 2, 2, 2])
# data = np.array([1, 2, 3, 4, 5, 6])
# sc.csc_matrix((data, (row, col)), shape=(3, 3)).todense() ??????????????
#

# 6
# rcv1 = fetch_rcv1()
# X = rcv1["data"]
# Y = rcv1.target[:87]
# breakpoint()
