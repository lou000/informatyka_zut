import cv2
import numpy as np
import matplotlib.pyplot as plt

##############################################################################
######   Konfiguracja       ##################################################
##############################################################################

kat = '.\\'  # katalog z plikami wideo
plik = "clip_1.mp4"  # nazwa pliku
ile = 100  # ile klatek odtworzyc? <0 - calosc
key_frame_counter = 4  # co ktora klatka ma byc kluczowa i nie podlegac kompresji
plot_frames = np.array([30, 45])  # automatycznie wyrysuj wykresy
auto_pause_frames = np.array([25])  # automatycznie zapauzuj dla klatki i wywietl wykres
subsampling = "4:4:4"  # parametry dla chorma subsamplingu
wyswietlaj_kaltki = True  # czy program ma wyswietlac kolejene klatki


##############################################################################
####     Kompresja i dekompresja    ##########################################
##############################################################################
class data:
    def __init__(self):
        self.Cr = None
        self.Cb = None
        self.Y = None


def compress(Y, Cb, Cr, key_frame_Y, key_frame_Cb, key_frame_Cr, inne_paramerty_do_dopisania=None):
    data.Y = Y
    data.Cb = Cb
    data.Cr = Cr
    return data


def decompress(data, key_frame_Y, key_frame_Cb, key_frame_Cr, inne_paramerty_do_dopisania=None):
    frame = np.dstack([data.Y, data.Cr, data.Cb]).astype(np.uint8)
    return frame


##############################################################################
####     GĹowna petla programu      ##########################################
##############################################################################

cap = cv2.VideoCapture(kat + '\\' + plik)

if ile < 0:
    ile = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))

cv2.namedWindow('Normal Frame')
cv2.namedWindow('Decompressed Frame')

compression_information = np.zeros((3, ile))

for i in range(ile):
    ret, frame = cap.read()
    if wyswietlaj_kaltki:
        cv2.imshow('Normal Frame', frame)
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2YCrCb)
    if (i % key_frame_counter) == 0:  # pobieranie klatek kluczowych
        key_frame = frame
        cY = frame[:, :, 0]
        cCb = frame[:, :, 2]
        cCr = frame[:, :, 1]
        d_frame = frame
    else:  # kompresja
        cdata = compress(frame[:, :, 0], frame[:, :, 2], frame[:, :, 1], key_frame[:, :, 0], key_frame[:, :, 2],
                         key_frame[:, :, 1])
        cY = cdata.Y
        cCb = cdata.Cb
        cCr = cdata.Cr
        d_frame = decompress(cdata, key_frame[:, :, 0], key_frame[:, :, 2], key_frame[:, :, 1])

    compression_information[0, i] = (frame[:, :, 0].size - cY.size) / frame[:, :, 0].size
    compression_information[1, i] = (frame[:, :, 0].size - cCb.size) / frame[:, :, 0].size
    compression_information[2, i] = (frame[:, :, 0].size - cCr.size) / frame[:, :, 0].size
    if wyswietlaj_kaltki:
        cv2.imshow('Decompressed Frame', cv2.cvtColor(d_frame, cv2.COLOR_YCrCb2BGR))

    if np.any(plot_frames == i):  # rysuj wykresy
        # bardzo sĹaby i sztuczny przyklad wykrozystania tej opcji
        fig, axs = plt.subplots(1, 3, sharey=True)
        fig.set_size_inches(16, 5)
        axs[0].imshow(frame)
        axs[2].imshow(d_frame)
        diff = frame.astype(float) - d_frame.astype(float)
        print(np.min(diff), np.max(diff))
        axs[1].imshow(diff, vmin=np.min(diff), vmax=np.max(diff))

    if np.any(auto_pause_frames == i):
        cv2.waitKey(-1)  # wait until any key is pressed

    k = cv2.waitKey(1) & 0xff

    if k == ord('q'):
        break
    elif k == ord('p'):
        cv2.waitKey(-1)  # wait until any key is pressed

plt.figure()
plt.plot(np.arange(0, ile), compression_information[0, :] * 100)
plt.plot(np.arange(0, ile), compression_information[1, :] * 100)
plt.plot(np.arange(0, ile), compression_information[2, :] * 100)