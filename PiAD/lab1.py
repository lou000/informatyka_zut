import numpy as np

# Tablice:
a = np.array([1, 2, 3, 4, 5, 6, 7])
b = np.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]])
print(np.transpose(b))
print(np.arange(0, 100))
print(np.linspace(0, 2, 10))
print(np.arange(0, 100, 5))

# Liczby losowe:
print(np.random.random(20).round(2))
print(np.random.randint(1, 1000))
print(np.zeros((3, 2)))
print(np.ones((3, 2)))
print(np.random.randint(0, 100, (5, 5), 'int32'))
a = np.random.random(10)
b = a.astype(int)
print(b)
print(a.round().astype(int))

# Selekcja danych:
b = np.array([[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]], dtype=np.int32)
print(b.ndim)
print(b.size)
print(b[0, 1], b[0, 3])
print(b[0, :])
print(b[:, 0])
arr = np.random.randint(low=0, high=100, size=(20, 7))
print(arr[:, 0:3])

# Operacje matematyczne i logiczne:
a = np.random.randint(low=0, high=10, size=(3, 3))
b = np.random.randint(low=0, high=10, size=(3, 3))
print(a + b)
print(a * b)
print(np.divide(a, b))  # divide by zero error
print(a ** b)
print(a >= 4)
print(b.trace())

# Dane statystyczne:
print(b.sum())
print(b.max())
print(b.min())
print(b.std())
print(b.mean())
print(b.mean(axis=0))

# Rzutowanie wymiarów za pomocą shape lub resize:
arr = np.random.randint(1, 10, 50)
mat = np.reshape(arr, (10, 5))
print(mat)
print(mat.ravel())
a = np.random.randint(1, 10, 5)
b = np.random.randint(1, 10, 4)
print(a[:, np.newaxis] + b)

# Sortowanie danych:
a = np.random.randn(5, 5)
a.sort(axis=0)
a[::-1].argsort(axis=1)
b = np.array([(1, 'MZ', 'mazowieckie'), (2, 'ZP', 'zachodniopomorskie'), (3, 'ML', 'małopolskie')])
b.reshape((3, 3))
b=b[b[:, 1].argsort()];
print()