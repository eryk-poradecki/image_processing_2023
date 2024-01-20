import numpy as np
from numpy.core.multiarray import ndarray


def w_matrixN(N):
    i, j = np.meshgrid(np.arange(N), np.arange(N))
    omega = np.exp(-2 * np.pi * 1j / N)
    W = np.power(omega, i * j) / np.sqrt(N)
    return W


def inv_w_matrixN(N):
    i, j = np.meshgrid(np.arange(N), np.arange(N))
    omega = np.exp(2 * np.pi * 1j / N)
    W = np.power(omega, i * j) / np.sqrt(N)
    return W


def dft_2d_matrix(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 2

    N, M = arr.shape[0], arr.shape[1]
    Wn = w_matrixN(N)
    Wm = w_matrixN(M)
    return Wn.dot(arr).dot(Wm.T)


def inv_dft_2d_matrix(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 2

    N, M = arr.shape[0], arr.shape[1]
    Wn = inv_w_matrixN(N)
    Wm = inv_w_matrixN(M)
    return Wn.dot(arr).dot(Wm.T)


def dft_3d_matrix(arr: np.ndarray) -> np.ndarray:
    assert arr.ndim == 3
    dft_ndarray = np.zeros_like(arr, dtype=np.complex64)

    C = arr.shape[2]
    for chan in range(C):
        dft_ndarray[:, :, chan] = dft_2d_matrix(arr[:, :, chan])
    return dft_ndarray
