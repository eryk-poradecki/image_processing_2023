import numpy as np
import matplotlib.pyplot as plt
from scipy import fftpack

def create_hamming_window(image_side_length: int, band_size: int):
    hamming1D = np.hamming(image_side_length)[:, None]
    hamming2D = np.sqrt(np.dot(hamming1D, hamming1D.T)) ** band_size
    return hamming2D

def low_pass_filter_np(band_size: int, array_image: np.ndarray) -> np.ndarray:
    fft_result = fftpack.fft2(array_image)
    fft_shifted = np.fft.fftshift(fft_result)
    fft_shifted *= create_hamming_window(len(fft_shifted), band_size)
    fft_unshifted = np.fft.ifftshift(fft_shifted)
    inv_fft_result = fftpack.ifft2(fft_unshifted)
    result = np.abs(inv_fft_result)
    result -= result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)

def high_pass_filter_np(band_size: int, array_image: np.ndarray) -> np.ndarray:
    low_pass_result = low_pass_filter_np(band_size, array_image)
    result = array_image - low_pass_result
    result = result - result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)

def band_pass_filter_np(band_size_low: int, band_size_high: int, array_image: np.ndarray) -> np.ndarray:
    low_pass_result = low_pass_filter_np(band_size_low, array_image)
    high_pass_result = high_pass_filter_np(band_size_high, array_image)
    band_cut_result = band_cut_filter_np(band_size_low, band_size_high, array_image)
    result = np.abs(array_image - band_cut_result).clip(0, 255)
    return result

def band_cut_filter_np(band_size_low: int, band_size_high: int, array_image: np.ndarray) -> np.ndarray:
    low_pass_result = low_pass_filter_np(band_size_low, array_image)
    high_pass_result = high_pass_filter_np(band_size_high, array_image)
    result = low_pass_result + high_pass_result
    result -= result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)

def edge_detection_filter_np(array_image: np.ndarray) -> np.ndarray:
    sobel_filter = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    edges = np.abs(np.convolve(array_image, sobel_filter, mode='same'))
    edges = edges - edges.min()
    edges = edges * 255 / edges.max()
    return edges.clip(0, 255)

def high_pass_edge_detection_filter_np(band_size: int, array_image: np.ndarray) -> np.ndarray:
    low_pass_result = low_pass_filter_np(band_size, array_image)
    edge_detection_result = edge_detection_filter_np(array_image)
    result = low_pass_result + edge_detection_result
    result -= result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)

def phase_modifying_filter_np(array_image: np.ndarray, l: int, k: int) -> np.ndarray:
    N, M = array_image.shape
    n = np.arange(0, N)
    m = np.arange(0, M)
    P = np.exp(1j * ((-n*k*2*np.pi)/N + (-m*l*2*np.pi)/M + (k + l) * np.pi))
    fft_result = fftpack.fft2(array_image)
    magnitude = np.abs(fft_result)
    phase = np.angle(fft_result)
    modified_phase = phase + P
    modified_fft = magnitude * np.exp(1j * modified_phase)
    inv_fft_result = fftpack.ifft2(modified_fft)
    result = np.abs(inv_fft_result)
    result -= result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)
