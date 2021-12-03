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
    newData = np.empty(data.shape[0] * 2 + len(shape) + 1)
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
    shape = data.shape
    data.flatten()


image = (plt.imread('pics/0008.png')*255).astype(int)
print(image.shape)
plt.imshow(image)
plt.show()
test = image[0:20, 0:20]  # np.array([1, 1, 3, 3, 3, 2, 8])
plt.imshow(test)
plt.show()

print(test, get_size(test))
print(encodeRLE(test), get_size(encodeRLE(test)))


