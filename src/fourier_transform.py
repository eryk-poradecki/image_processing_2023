import numpy as np


def fft(x: np.ndarray) -> np.ndarray:
    N = len(x)
    if N <= 1:
        return x

    even = fft(x[0::2])
    odd = fft(x[1::2])

    t = np.exp(-2j * np.pi * np.arange(N) / N)

    first_half = even + t[: N // 2] * odd
    second_half = even + t[N // 2 :] * odd

    return np.concatenate([first_half, second_half])


def invfft(x: np.ndarray) -> np.ndarray:
    N = len(x)
    if N <= 1:
        return x

    even = invfft(x[::2])
    odd = invfft(x[1::2])

    t = np.exp(2j * np.pi * np.arange(N) / N)

    first_half = even + t[: N // 2] * odd
    second_half = even + t[N // 2 :] * odd

    return np.concatenate([first_half, second_half]) / 2
