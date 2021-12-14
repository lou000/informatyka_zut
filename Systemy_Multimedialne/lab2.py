import numpy as np
from pylab import rcParams
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import scipy.fftpack
import sounddevice as sd
import soundfile as sf


def quantize(_data, _bits):
    assert 2 <= _bits <= 32

    out_val = _data.astype(np.float32)
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


def decimate(_data, _interval):
    return _data[::_interval].copy()


def interp_signal(_data, _freq, _new_freq, _interp_type="linear"):
    time = _data.shape[0]/_freq
    x  = np.arange(0, time, 1/_freq)
    x1 = np.arange(0, time, 1/_new_freq)

    func = interp1d(x, _data, _interp_type, fill_value="extrapolate")
    return func(x1).astype(_data.dtype)


def plot_sound(_data, _freq, _time_ms, _title="???"):
    _max = int(_freq*(_time_ms/1000))
    plt.subplot(2, 1, 1)
    plt.plot(np.arange(0, _max)/_freq, _data[0:_max])
    plt.subplot(2, 1, 2)
    plot_spectrum(_data, _freq)
    plt.title(_title)
    plt.show()


def plot_spectrum(_data, _freq):
    fsize = 2 ** 8
    yf = scipy.fftpack.fft(_data, fsize)
    plt.plot(np.arange(0, _freq / 2, _freq / fsize), 20 * np.log10(np.abs(yf[:fsize // 2])))


def plot_freq_change(_data, _old_freq, _new_freq, _time_ms):
    plt.subplot(3, 1, 1)
    plot_spectrum(decimate(_data, int(_old_freq / _new_freq)), _new_freq)
    plt.title("Decimation (" + str(_new_freq) + "Hz)")
    plt.subplot(3, 1, 2)
    plot_spectrum(interp_signal(_data, _old_freq, _new_freq, "linear"), _new_freq)
    plt.title("Linear interpolation (" + str(_new_freq) + "Hz)")
    plt.subplot(3, 1, 3)
    plot_spectrum(interp_signal(_data, _old_freq, _new_freq, "cubic"), _new_freq)
    plt.title("Cubic interpolation (" + str(_new_freq) + "Hz)")
    plt.show()


rcParams['figure.figsize'] = 10, 10
data, freq = sf.read('sounds/sing_low1.wav', dtype=np.int32)
print(freq, data.shape)
if len(data.shape) > 1:
    data = data[:, 0]

ms = 100
plot_sound(quantize(data, 4),  freq, ms, "Quantization 4 bit")
plot_sound(quantize(data, 8),  freq, ms, "Quantization 8 bit")
plot_sound(quantize(data, 16), freq, ms, "Quantization 16 bit")
plot_sound(quantize(data, 24), freq, ms, "Quantization 24 bit")

# plot_sound(decimate(data, int(freq / 2000)), 2000, 1000)
# plot_freq_change(data, freq, 2000 , ms)
# plot_freq_change(data, freq, 4000 , ms)
# plot_freq_change(data, freq, 8000 , ms)
# plot_freq_change(data, freq, 16000, ms)
# plot_freq_change(data, freq, 24000, ms)
# plot_freq_change(data, freq, 41000, ms)
# plot_freq_change(data, freq, 16950, ms)


# sd.play(data, samplerate=freq, blocking=True)
# sd.play(quantize(data, 4), samplerate=freq, blocking=True)
# sd.play(quantize(data, 8), samplerate=freq, blocking=True)
# sd.play(quantize(data, 16), samplerate=freq, blocking=True)
# sd.play(quantize(data, 24), samplerate=freq, blocking=True)
#
# frequencies = [2000, 4000, 8000, 16000, 24000, 41000, 16950]
#
# for new_freq in frequencies:
#     sd.play(decimate(data, int(freq/new_freq)), samplerate=new_freq, blocking=True)
# for new_freq in frequencies:
#     sd.play(interp_signal(data, freq, new_freq, "linear"), samplerate=new_freq, blocking=True)
# for new_freq in frequencies:
#     sd.play(interp_signal(data, freq, new_freq, "cubic"), samplerate=new_freq, blocking=True)


