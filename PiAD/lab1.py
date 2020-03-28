import numpy

a = numpy.array([1, 2, 3, 4, 5, 6, 7])
b = numpy.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]])
print(numpy.transpose(b))

print(numpy.arange(0, 100))

print(numpy.linspace(0, 2, 10))

print(numpy.arange(0, 100, 5))

print(numpy.random.random(20).round(2))

print(numpy.random.randint(1, 1000))

print(numpy.zeros((3, 2)))

print(numpy.ones((3, 2)))

print(numpy.random.randint(0, 100, (5, 5), 'int32'))

a = numpy.random.random(10)
b = a.astype(int)
print(b)
print(a.round().astype(int))

b = numpy.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]], dtype=numpy.int32)
print(b.ndim)
print(b.size)
print(b[0, 1], b[0, 3])
print(b[0, :])
print(b[:, 0])



