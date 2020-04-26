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
# print(np.divide(a, b))  # divide by zero error
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
b = b[b[:, 1].argsort()];
print(b[2, 2])

# Zadania podsumowujące:
# Zadanie 1:
arr = np.random.randint(100, size=(10, 5))
print(np.trace(arr))
print(np.diag(arr))

# Zadanie 2:
a = np.random.randn(4)
b = np.random.randn(4)
print(a * b)

# Zadanie 3:
a = np.random.randint(1, 100, size=(5, 5))
b = np.random.randint(1, 100, size=(5, 5))
print(a+b)

# Zadanie 4:
a = np.random.randint(1, 100, size=(5, 4))
b = np.random.randint(1, 100, size=(4, 5))
b = b.reshape(5, 4)
print(a+b)

# Zadanie 5:
print(a[:, 2] * (b[:, 3]))

# Zadanie 6:
a = (np.random.normal(0, 10, size=(5, 5)))
b = (np.random.uniform(0, 10, size=(5, 5)))
print(a.mean(), b.mean())
print(a.std(), b.std())
print(a.var(), b.var())

# Zadanie 7:
a = np.random.randint(1, 100, size=(4, 4))
b = np.random.randint(1, 100, size=(4, 4))
print(a*b)
print(a.dot(b))

# Zadanie 8:
a = np.random.randint(1, 100, size=(4, 4))
a = np.lib.stride_tricks.as_strided(a, (5, 3))
print(a)

# Zadanie 9:
a = np.random.randint(1, 100, size=(4, 4))
b = np.random.randint(1, 100, size=(4, 4))
print(np.hstack((a, b)), np.vstack((a, b)))

# Zadanie 10:
a = np.arange(24).reshape(4, 6)
a = np.lib.stride_tricks.as_strided(a, shape=(6, 2, 3), strides=(12, 24, 4))
print(a)
print('max', np.amax(a, axis=2))


