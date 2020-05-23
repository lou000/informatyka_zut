from __future__ import print_function
import pandas as pd
import numpy as np
import builtins as __builtin__
from scipy import stats as sp
import matplotlib.pyplot as plot


def print(*args, **kwargs):
    args2 = (*args, '\n')  # adding one extra line to standart print
    return __builtin__.print(*args2, **kwargs)


data = {'data': pd.date_range(start= '2020-03-01', periods=5), 'a': np.random.random(5), 'b': np.random.random(5),
        'c': np.random.random(5)}
frame = pd.DataFrame(data)
print(frame)

data = {'ID': range(1, 21), 'a': np.random.random(20), 'b': np.random.random(20), 'c': np.random.random(20)}
frame = pd.DataFrame(data).set_index('ID')
print(frame)
print(frame[:3])
print(frame[-3:])
for col in frame.columns:
    print(col)
print(frame.values)
print(frame.sample(n=5))
print(frame[['a', 'b']])
print(frame.iloc[:3, :2])
print(frame.iloc[4])
print(frame.iloc[[0, 5, 6, 7], [1, 2]])
print(frame.describe())
print(frame > 0)
print(frame[frame > 0])
print(frame[frame['a'] > 0])
print(frame.mean())
print(frame.mean(axis=1))

data2 = {'data': pd.date_range(start= '2020-03-01', periods=5), 'a': np.random.randint(5, 10),
         'b': np.random.randint(5, 10), 'c': np.random.randint(5, 10)}
frame2 = pd.DataFrame(data2)
print(pd.concat([frame, frame2]))
print(pd.concat([frame, frame2]).transpose())

data= {'x': [1, 2, 3, 4, 5], 'y': ['a', 'b', 'a', 'b', 'b']}
df = pd.DataFrame(data, index=np.arange(5))
df.index.name = 'id'
print(df)

print(df[['x', 'y']].sort_index())
print(df[['x', 'y']].sort_index(ascending=False))

slownik = {'Day': ["Mon", "Tue", "Mon", "Tue", "Mon"], 'Fruit': ["Apple", "Apple", "Banana", "Banana", "Apple"],
           'Pound': [10, 15, 50, 40, 5], 'Profit': [20, 30, 25, 20, 10]}
df3 = pd.DataFrame(slownik)
print("Słownik \n", df3, "\n")
print(df3.groupby('Day').sum())
print(df3.groupby(['Day', 'Fruit']).sum())

df = pd.DataFrame(np.random.randn(20, 3), index=np.arange(20), columns=['A', 'B', 'C'])
df.index.name = 'id'
print(df)
df['B'] = 1  # ustawienie calej kolumna na wartosc 1
print(df)
df.iloc[1, 2] = 10  # w kolumnie od indeksie 2 w rzedzie o indeksie 1 wartosc = 10
print(df)
df[df < 0] = -df  # odwrócenie wartosci ujemnych na dodatnie
print(df)

df.iloc[[0, 3], 1] = np.nan  # komorki o wartosci 0 i 3 w kolumnie o indeksie 1 przyjmuja wartosc NaN
print(df)
df.fillna(0, inplace=True)  # wartosci NaN są zamieniane na 0
print(df)
df.iloc[[0, 3], 1] = np.nan  # jw
df = df.replace(to_replace=np.nan, value=-9999)  # wartości NaN są zamienione na -9999
print(df)
df.iloc[[0, 3], 1] = np.nan
print(pd.isnull(df))  # zamienia zero i nan na true a liczby!=0 i nan na false

# Zadania:

# 1
data = {
    'x': [1, 2, 3, 4, 5],
    'y': ['a', 'b', 'a', 'b', 'b']}
df = pd.DataFrame(data)
print(df.groupby('y')['x'].mean())  # w poleceniu jest na odwrot ale to chyba nie ma sensu

# 2
print(df['x'].value_counts(), df['y'].value_counts())

# 3
# brak nazw kolumn, nie chce wczytac floatow
# fileNP = np.loadtxt('autos.csv', delimiter=',', skiprows=1)
# print(fileNP)
# dziala kompetentnie
filePD = pd.read_csv('autos.csv')
print(filePD)

# 4
print(filePD.groupby('make')['highway-mpg'].mean())
print(filePD.groupby('make')['city-mpg'].mean())

# 5
print(filePD.groupby('make')['fuel-type'].value_counts())

# 6
print(np.polyval(np.polyfit(filePD['city-mpg'], filePD['length'], 1), 1))
print(np.polyval(np.polyfit(filePD['city-mpg'], filePD['length'], 2), 2))

# 7
print(sp.spearmanr(filePD['city-mpg'], filePD['length']).correlation)

# 8
plot.plot(filePD['length'], filePD['city-mpg'], '*')
plot.plot(np.unique(filePD['length']),
         np.poly1d(np.polyfit(filePD['length'], filePD['city-mpg'], 1))(np.unique(filePD['length'])))
plot.show()

# 9/10
gaussian_length = sp.gaussian_kde(np.sort(filePD['length']))
gaussian_width = sp.gaussian_kde(np.sort(filePD['width']))

ax = plot.subplot(1, 3, 1)
ax.plot(np.sort(filePD['length']), gaussian_length(np.sort(filePD['length'])), 'b',
        label='length')
ax.set_title('LENGTH')
ax.legend()

ax = plot.subplot(1, 3, 3)
ax.plot(np.sort(filePD['width']), gaussian_width(np.sort(filePD['width'])), 'b', label='width')
ax.set_title('WIDTH')
ax.legend()
plot.show()



