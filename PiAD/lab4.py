import math
import matplotlib.pyplot as plot
import numpy as np
from scipy.signal import argrelextrema

def disc(f, _fs):  # funkcja do dyskretyzacji
    _points = [[], []]
    for t in np.arange(0, 1, 1 / _fs):
        _points[0].append(t)
        _points[1].append(math.sin(2 * math.pi * f * t))
    return _points


freq = [20, 21, 30, 45, 50, 100, 150, 200, 250, 1000]

figure = plot.figure(figsize=(15, 10))
for i, fs in enumerate(freq):
    points = disc(10, fs)
    ax = figure.add_subplot(4, 3, i + 1)
    ax.plot(points[0], points[1], color=(np.random.uniform(0, 1), np.random.uniform(0, 1), np.random.uniform(0, 1)))
    ax.set_title(str(fs) + '[Hz]')

figure.tight_layout(pad=1.0)
plot.show()

# Twierdzenie o próbkowaniu, twierdzenie Nyquista–Shannona[a] – fundamentalne twierdzenie teorii informacji,
# telekomunikacji oraz cyfrowego przetwarzania sygnałów opisujące matematyczne podstawy procesów próbkowania sygnałów
# oraz ich rekonstrukcji:
#
# Z sygnału dyskretnego {\displaystyle x^{\star }(t)}x^{\star }(t) złożonego z próbek danego sygnału ciągłego {
# \displaystyle x(t)}x(t) można wiernie odtworzyć sygnał {\displaystyle x(t).}{\displaystyle x(t).}
#
# Jest podstawową zasadą pozwalającą przekształcać sygnał ciągły w czasie (często nazywany „sygnałem analogowym”) w
# sygnał dyskretny (często nazywany „sygnałem cyfrowym”). Ustanawia warunek dla częstotliwości próbkowania,
# która pozwala dyskretnej sekwencji próbek (cyfrowych) na przechwytywanie wszystkich informacji z sygnału ciągłego (
# analogowego) o skończonej szerokości pasma – częstotliwość Nyquista.

# Aliasing
plot.figure(figsize=(15, 10))
img = plot.imread('cat.jpg', format='jpg').copy()
plot.imshow(img)
plot.show()
print(img.shape)
print(len(img[0][0]))

plot.figure(figsize=(15, 10))
r = img[:, :, 0]
g = img[:, :, 1]
b = img[:, :, 2]
brightness = (np.maximum(r, g, b) + np.minimum(r, g, b)) / 2
plot.subplot(2, 2, 1)
plot.imshow(brightness, cmap=plot.get_cmap("gray"))

mean = (r + g + b) / 3
plot.subplot(2, 2, 2)
plot.imshow(mean, cmap=plot.get_cmap("gray"))

lumination = r * 0.21 + g * 0.72 + b * 0.07
plot.subplot(2, 2, 3)
plot.imshow(lumination, cmap=plot.get_cmap("gray"))
plot.tight_layout(pad=1.0)
plot.show()

plot.figure(figsize=(15, 10))
plot.subplot(2, 2, 1)
plot.hist(brightness.ravel(), bins=255)

plot.subplot(2, 2, 2)
plot.hist(mean.ravel(), bins=255)

plot.subplot(2, 2, 3)
plot.hist(lumination.ravel(), bins=255)
plot.tight_layout()
plot.show()

plot.figure(figsize=(15, 10))
h1 = plot.hist(lumination.ravel(), bins=16)
plot.grid(True)
plot.show()


def find_nearest(array, value):
    array = np.asarray(array)
    idx = (np.abs(array - value)).argmin()
    return array[idx]


plot.figure(figsize=(15, 10))
rows, columns = lumination.shape
for i in range(rows):
    for j in range(columns):
        lumination[i, j] = find_nearest(h1[1], lumination[i, j])

plot.imshow(lumination, cmap=plot.get_cmap("gray"))
plot.show()

plot.figure(figsize=(15, 10))

img2 = plot.imread('pic.jpg', format='jpg').copy()
plot.imshow(img2)
plot.show()

plot.figure(figsize=(15, 10))
r = img2[:, :, 0]
g = img2[:, :, 1]
b = img2[:, :, 2]

lumination = r * 0.21 + g * 0.72 + b * 0.07
h2 = plot.hist(lumination.ravel(), bins=255)
minima = argrelextrema(h2[0], np.less)
_min = np.mean(minima)
print(_min)
plot.show()

plot.figure(figsize=(15, 10))
rows, columns = lumination.shape
for i in range(rows):
    for j in range(columns):
        if lumination[i, j] > _min:
            lumination[i, j] = 1
        else:
            lumination[i, j] = 0

plot.imshow(lumination, cmap=plot.get_cmap("gray"))
plot.show()
