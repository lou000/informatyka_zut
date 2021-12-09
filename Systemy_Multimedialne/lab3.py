import sys
import numpy as np
import matplotlib.pyplot as plt


def get_size(obj, seen=None):
    """Recursively finds size of objects"""
    size = sys.getsizeof(obj)
    if seen is None:
        seen = set()
    obj_id = id(obj)
    if obj_id in seen:
        return 0
    # Important mark as seen *before* entering recursion to gracefully handle
    # self-referential objects
    seen.add(obj_id)
    if isinstance(obj, np.ndarray):
        size += obj.nbytes
    elif isinstance(obj, dict):
        size += sum([get_size(v, seen) for v in obj.values()])
        size += sum([get_size(k, seen) for k in obj.keys()])
    elif hasattr(obj, '__dict__'):
        size += get_size(obj.__dict__, seen)
    elif hasattr(obj, '__iter__') and not isinstance(obj, (str, bytes, bytearray)):
        size += sum([get_size(i, seen) for i in obj])
    return size


def encodeRLE(_data):
    data = _data.copy()
    shape = data.shape
    data = data.flatten()

    # preallocate and encode shape at the start
    newData = np.empty(data.shape[0] * 2 + len(shape) + 1).astype(_data.dtype)
    newData[0] = len(shape)
    shapeIndex = 0
    for shp in shape:
        newData[1+shapeIndex] = shp
        shapeIndex += 1

    newDataIndex = len(shape) + 1
    currentIndex = 0
    while currentIndex < data.shape[0]:
        current_bit = data[currentIndex]
        n_repeats = 1
        while currentIndex + n_repeats < data.shape[0] and data[currentIndex + n_repeats] == current_bit:
            n_repeats += 1

        currentIndex += n_repeats
        newData[newDataIndex] = n_repeats
        newData[newDataIndex+1] = current_bit
        newDataIndex += 2

    return newData[:newDataIndex]


def decodeRLE(data):
    shpCount = data[0].astype(int)
    shape = np.empty(shpCount)

    size = 1
    for i in range(0, shpCount):
        shape[i] = data[i+1]
        size *= shape[i]
    shape = tuple(shape.astype(int))

    newData = np.empty(int(size)).astype(data.dtype)

    currentIndex = shpCount + 1
    newDataIndex = 0
    while currentIndex < data.shape[0]:
        n_repeats = data[currentIndex]
        for i in range(0, n_repeats):
            newData[newDataIndex] = data[currentIndex+1]
            newDataIndex += 1
        currentIndex += 2

    newData = np.reshape(newData, shape).astype(data.dtype)  # numpy keeps changing the array type on me
    return newData


image = (plt.imread('pics/0016.jpg'))
print(image.shape)
_ax = plt.subplot(1, 2, 1)
_ax.set_axis_off()
_ax.set_title('Original')
plt.imshow(image)

print('Original size:     ', get_size(image))
compressed = encodeRLE(image)
print('Compressed size:   ', get_size(compressed))
decompressed = decodeRLE(compressed)
print('Decompressed size: ', get_size(decompressed))

_ax = plt.subplot(1, 2, 2)
_ax.set_axis_off()
_ax.set_title('After compression/decompression cycle')
plt.imshow(decompressed)
plt.show()

