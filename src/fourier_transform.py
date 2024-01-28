import numpy as np
from functools import partial
from multiprocessing import Pool


def fft_freq_2d(x: np.ndarray) -> np.ndarray:
    return inv_fft_2d(x)


def inv_fft_freq_2d(x: np.ndarray) -> np.ndarray:
    return fft_2d(x)


def fft_freq(x: np.ndarray) -> np.ndarray:
    return inv_fft(x)


def inv_fft_freq(x: np.ndarray) -> np.ndarray:
    return fft(x)


def inv_fft(x: np.ndarray) -> np.ndarray:
    N = len(x)
    if N <= 1:
        return x

    even = inv_fft(x[0::2])
    odd = inv_fft(x[1::2])

    t = np.exp(-2j * np.pi * np.arange(N) / N)

    first = even + t[: N // 2] * odd
    second = even + t[N // 2 :] * odd
    res = np.concatenate([first, second])
    return res


def fft(x: np.ndarray) -> np.ndarray:
    N = len(x)
    if N <= 1:
        return x

    even = fft(x[::2])
    odd = fft(x[1::2])

    t = np.exp(2j * np.pi * np.arange(N) / N)

    res_even = even + t[: N // 2] * odd
    res_odd = even + t[N // 2 :] * odd
    res = np.concatenate([res_even, res_odd])

    return res


def inv_fft_2d(X: np.ndarray) -> np.ndarray:
    inv_fft_rows = np.apply_along_axis(inv_fft, axis=1, arr=X)

    X_fft_2d = np.apply_along_axis(inv_fft, axis=0, arr=inv_fft_rows)

    return X_fft_2d


def fft_2d(X):
    fft_cols = np.apply_along_axis(fft, axis=0, arr=X)

    X_fft_2d = np.apply_along_axis(fft, axis=1, arr=fft_cols)

    return X_fft_2d


def inv_dft(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 1

    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)
    N = arr.shape[0]
    one_over_sqrt_N: float = 1 / np.sqrt(N)

    for i in range(N):
        Wn = np.exp(1j * 2 * np.pi * np.arange(N).reshape(-1, 1) * i / N)
        dft_ndarray[i] = one_over_sqrt_N * (np.sum(arr * Wn))
    return dft_ndarray


def dft(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 1

    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)
    N = arr.shape[0]
    one_over_sqrt_N: float = 1 / np.sqrt(N)

    for i in range(N):
        Wn = np.exp(-1j * 2 * np.pi * np.arange(N).reshape(-1, 1) * i / N)
        dft_ndarray[i] = one_over_sqrt_N * (np.sum(arr * Wn))
    return dft_ndarray


def dft_2d(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 2
    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)

    N, M = arr.shape[0], arr.shape[1]
    one_over_sqrt_NM: float = 1 / np.sqrt(N * M)

    for i in range(N):
        for k in range(M):
            Wn = np.exp(-1j * 2 * np.pi * np.arange(N).reshape(-1, 1) * i / N)
            Wm = np.exp(-1j * 2 * np.pi * np.arange(M) * k / M)
            dft_ndarray[i, k] = one_over_sqrt_NM * (np.sum(arr * Wm * Wn))
    return dft_ndarray


def __dft_process_channel(arr, chan):
    return dft_2d(arr[:, :, chan])


def dft_3d_multiproc(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 3
    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)

    partial_process_channel = partial(__dft_process_channel, arr)
    C = arr.shape[2]

    with Pool() as pool:
        result_list = pool.map(partial_process_channel, range(C))

    for chan, result in zip(range(C), result_list):
        dft_ndarray[:, :, chan] = result
    return dft_ndarray


def dft_3d(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 3
    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)

    C = arr.shape[2]
    for chan in range(C):
        dft_ndarray[:, :, chan] = dft_2d(arr[:, :, chan])
    return dft_ndarray


def inv_dft_3d(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 3
    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)

    C = arr.shape[2]
    for chan in range(C):
        dft_ndarray[:, :, chan] = inv_dft_2d(arr[:, :, chan])
    return dft_ndarray


def inv_dft_2d(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 2
    inv_dft_ndarray = np.zeros_like(arr, dtype=np.complex64)

    N, M = arr.shape[0], arr.shape[1]
    one_over_sqrt_NM: float = 1 / np.sqrt(N * M)

    for i in range(N):
        for k in range(M):
            Wn = np.exp(1j * 2 * np.pi * np.arange(N).reshape(-1, 1) * i / N)
            Wm = np.exp(1j * 2 * np.pi * np.arange(M) * k / M)
            inv_dft_ndarray[i, k] = one_over_sqrt_NM * (np.sum(arr * Wm * Wn))
    return inv_dft_ndarray
