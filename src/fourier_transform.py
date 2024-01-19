import numpy as np


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
    res = np.concatenate([res_even, res_odd]) / 2

    return res


def inv_fft_2d(X: np.ndarray) -> np.ndarray:
    inv_fft_rows = np.apply_along_axis(inv_fft, axis=1, arr=X)

    X_fft_2d = np.apply_along_axis(inv_fft, axis=0, arr=inv_fft_rows)

    return X_fft_2d


def fft_2d(X):
    fft_cols = np.apply_along_axis(fft, axis=0, arr=X)

    X_fft_2d = np.apply_along_axis(fft, axis=1, arr=fft_cols)

    return X_fft_2d
