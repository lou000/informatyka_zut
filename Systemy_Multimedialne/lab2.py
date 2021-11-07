import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
import sounddevice as sd
import soundfile as sf


def quantize(_data, _bits):
    assert _bits > 1

    out_val = data.astype(np.float32)
    _start = 0
    _end = 0

    if np.issubdtype(_data.dtype, np.floating):
        _start = -1
        _end = 1
    else:
        _start = np.iinfo(_data.dtype).min
        _end   = np.iinfo(_data.dtype).max

    _range2 = 2**_bits-1
    out_val = (out_val-_start)/(_end-_start)
    out_val = np.round(out_val*_range2)/_range2
    out_val = ((out_val*(_end-_start))+_start).astype(_data.dtype)
    return out_val


def plot_me2(_data, _fs):
    fsize = 2 ** 8
    plt.figure()
    plt.subplot(2, 1, 1)
    plt.plot(np.arange(0, _data.shape[0]) / _fs, _data)

    plt.subplot(2, 1, 2)
    yf = scipy.fftpack.fft(_data, fsize)
    plt.plot(np.arange(0, _fs / 2, _fs / fsize), 20 * np.log10(np.abs(yf[:fsize // 2])))
    plt.show()

def plot_me(_data):
    plt.figure()
    plt.plot(_data)
    plt.show()


# data, fs = sf.read('sounds/sin_8000Hz.wav', dtype=np.int32)
data = np.arange(np.iinfo(np.int32).min, np.iinfo(np.int32).max, 1000, dtype=np.int32)
fs = 100
plt.plot(data, quantize(data, 2))
plt.show()

