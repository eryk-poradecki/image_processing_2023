import numpy as np


def fft(x: np.ndarray) -> np.ndarray:
    N = len(x)
    if N <= 1:
        return x

    even = fft(x[0::2])
    odd = fft(x[1::2])

    t = np.exp(-2j * np.pi * np.arange(N) / N)

    first = even + t[: N // 2] * odd
    second = even + t[N // 2 :] * odd
    res = np.concatenate([first, second])
    return res


def invfft(x: np.ndarray) -> np.ndarray:
    N = len(x)
    if N <= 1:
        return x

    even = invfft(x[::2])
    odd = invfft(x[1::2])

    t = np.exp(2j * np.pi * np.arange(N) / N)

    res_even = even + t[: N // 2] * odd
    res_odd = even + t[N // 2 :] * odd
    res = np.concatenate([res_even, res_odd]) / 2

    return res


def fft_2d(X: np.ndarray) -> np.ndarray:
    x_fft_rows = np.apply_along_axis(fft, axis=1, arr=X)

    x_fft_2d = np.apply_along_axis(fft, axis=0, arr=x_fft_rows)

    return x_fft_2d


def invfft_2d(X):
    x_invfft_cols = np.apply_along_axis(invfft, axis=0, arr=X)

    x_invfft_2d = np.apply_along_axis(invfft, axis=1, arr=x_invfft_cols)

    return x_invfft_2d
