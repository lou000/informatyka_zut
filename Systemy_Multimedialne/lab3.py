import sys

import numpy as np
import matplotlib.pyplot as plt
from collections import namedtuple


# Original get_size function does not behave well with ndarray types,
# sys getsizeof returnes full size of array if its a direct reference,
# but it returns only the size of the array object when its a slice of an array

# test for yourself:
#
# arr = np.empty(1000)
# print(sys.getsizeof(arr))
# arr = arr[::]
# print(sys.getsizeof(arr))
#
# i modified the function below to exclude sys.getsizeof from ndarray calculation
# this omits the size of ndarray container from the calculations

def get_size(obj, seen=None):
    """Recursively finds size of objects"""
    # this is old code
    # size = sys.getsizeof(obj)

    # this is modified to properly work with ndarray views
    size = 0
    if not isinstance(obj, np.ndarray):
        size += sys.getsizeof(obj)

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
        newData[1 + shapeIndex] = shp
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
        newData[newDataIndex + 1] = current_bit
        newDataIndex += 2

    newData = newData[:newDataIndex].copy()
    return newData


def decodeRLE(data):
    shpCount = data[0].astype(int)
    shape = np.empty(shpCount)

    size = 1
    for i in range(0, shpCount):
        shape[i] = data[i + 1]
        size *= shape[i]
    shape = tuple(shape.astype(int))

    newData = np.empty(int(size)).astype(data.dtype)
    currentIndex = shpCount + 1
    newDataIndex = 0
    while currentIndex < data.shape[0]:
        n_repeats = data[currentIndex]
        for i in range(0, n_repeats.astype(int)):
            newData[newDataIndex] = data[currentIndex + 1]
            newDataIndex += 1
        currentIndex += 2

    newData = np.reshape(newData, shape).astype(data.dtype)  # numpy keeps changing the array type on me
    return newData


Node = namedtuple("Node", "color final level resolution topleft topright bottomleft bottomright")
nodeCount = 0


def createQuadTree(img, maxLevel=-1, level=0):
    global nodeCount
    nodeCount += 1
    color = np.mean(img, axis=(0, 1)).astype(int)
    final = (img == color).all()
    resolution = np.array([img.shape[0], img.shape[1]]).astype(int)
    topleft = None
    topright = None
    bottomleft = None
    bottomright = None

    if not final and level != maxLevel:
        if img.shape[0] > 1 and img.shape[1] > 1:
            split_h = np.array_split(img, 2, axis=0)
            split_top = np.array_split(split_h[0], 2, axis=1)
            split_bottom = np.array_split(split_h[1], 2, axis=1)
            topleft =     createQuadTree(split_top[0], maxLevel, level + 1)
            topright =    createQuadTree(split_top[1], maxLevel, level + 1)
            bottomleft =  createQuadTree(split_bottom[0], maxLevel, level + 1)
            bottomright = createQuadTree(split_bottom[1], maxLevel, level + 1)
        elif img.shape[0] == 1:
            split = np.array_split(img, 2, axis=1)
            topleft = createQuadTree(split[0], maxLevel, level + 1)
            topright = createQuadTree(split[1], maxLevel, level + 1)
        elif img.shape[1] == 1:
            split = np.array_split(img, 2, axis=0)
            topleft = createQuadTree(split[0], maxLevel, level + 1)
            bottomleft = createQuadTree(split[1], maxLevel, level + 1)

    return Node(color, final, level, resolution, topleft, topright, bottomleft, bottomright)


def joinQuadrants(top_left, top_right, bottom_left, bottom_right):
    if top_right is None:
        return np.concatenate((top_left, bottom_left), axis=0)
    elif bottom_left is None:
        return np.concatenate((top_left, top_right), axis=1)

    top = np.concatenate((top_left, top_right), axis=1)
    bottom = np.concatenate((bottom_left, bottom_right), axis=1)
    return np.concatenate((top, bottom))


def getImageFromTree(node, level=-1):
    if node is None:
        return None
    if node.final or node.level == level:
        return np.tile(node.color, (node.resolution[0], node.resolution[1], 1))
    else:
        return joinQuadrants(getImageFromTree(node.topleft, level), getImageFromTree(node.topright, level),
                             getImageFromTree(node.bottomleft, level), getImageFromTree(node.bottomright, level)).astype(int)


image = (plt.imread('pics/photo.jpg')).astype(int)
_ax = plt.subplot(3, 1, 1)
_ax.set_axis_off()
_ax.set_title('Original')
plt.imshow(image)
origSize = get_size(image)

print('\n\n------------RLE------------')
print('Original size:     ', origSize, '   pixelCount: ', image.shape[0]*image.shape[1])
compressed = encodeRLE(image)
rleSize = get_size(compressed)
print('Compressed size:   ', rleSize)
decompressed = decodeRLE(compressed)
assert (image == decompressed).all
print('Decompressed size: ', get_size(decompressed))
print('Compression level: ', round(origSize / rleSize, 2))
print('Compression pct:   ', round(100 * rleSize / origSize, 2))

print('\n\n---------QuadTree----------')
print('Original size:     ', origSize, '   pixelCount: ', image.shape[0]*image.shape[1])
compressedQuad = createQuadTree(image)
treeSize = get_size(compressedQuad)
print('Compressed size:   ', treeSize, '   nodeCount:  ', nodeCount, '   avgNodeSize: ', int(treeSize/nodeCount))
decompressedQuad = getImageFromTree(compressedQuad)
assert (image == decompressedQuad).all
print('Decompressed size: ', get_size(decompressedQuad))
print('Compression level: ', round(origSize / treeSize, 2))
print('Compression pct:   ', round(100 * treeSize / origSize, 2))

_ax = plt.subplot(3, 1, 2)
_ax.set_axis_off()
_ax.set_title('RLE')
plt.imshow(decompressed)

_ax = plt.subplot(3, 1, 3)
_ax.set_axis_off()
_ax.set_title('QuadTree')
plt.imshow(decompressedQuad)
plt.show()


_ax = plt.subplot(1, 3, 1)
_ax.set_axis_off()
_ax.set_title('Level 3')
plt.imshow(getImageFromTree(compressedQuad, 3))

_ax = plt.subplot(1, 3, 2)
_ax.set_axis_off()
_ax.set_title('Level 7')
plt.imshow(getImageFromTree(compressedQuad, 7))

_ax = plt.subplot(1, 3, 3)
_ax.set_axis_off()
_ax.set_title('Level Maximum')
plt.imshow(getImageFromTree(compressedQuad))
plt.show()