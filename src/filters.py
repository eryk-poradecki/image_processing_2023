import numpy as np
from .fourier_transform import fft_freq_2d, inv_fft_freq_2d


def create_hamming_window(image_side_length: int, band_size: int):
    n = np.arange(0, image_side_length)
    hamming1D = 0.54 - 0.46 * np.cos(2 * np.pi * n / (image_side_length - 1))
    hamming2D = np.sqrt(np.outer(hamming1D, hamming1D)) ** band_size

    return hamming2D


def low_pass_filter(image: np.ndarray, band_size: int) -> np.ndarray:
    fft_result = fft_freq_2d(image)
    fft_shifted = np.fft.fftshift(fft_result)
    fft_shifted *= create_hamming_window(len(fft_shifted), band_size)
    fft_unshifted = np.fft.ifftshift(fft_shifted)
    inv_fft_result = inv_fft_freq_2d(fft_unshifted)
    result = np.abs(inv_fft_result)
    result -= result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)


def high_pass_filter(image: np.ndarray, band_size: int) -> np.ndarray:
    low_pass_result = low_pass_filter(image, band_size)
    result = image - low_pass_result
    result = result - result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)


def band_pass_filter(
    image: np.ndarray, band_size_low: int, band_size_high: int
) -> np.ndarray:
    band_cut_result = band_cut_filter(image, band_size_low, band_size_high)
    result = np.abs(image - band_cut_result).clip(0, 255)
    return result


def band_cut_filter(
    image: np.ndarray, band_size_low: int, band_size_high: int
) -> np.ndarray:
    low_pass_result = low_pass_filter(image, band_size_low)
    high_pass_result = high_pass_filter(image, band_size_high)

    result = low_pass_result + high_pass_result
    result -= result.min()
    result = result * 255 / result.max()

    return result.clip(0, 255)


def high_pass_filter_edge(image: np.ndarray, mask: np.ndarray) -> np.ndarray:
    fft_result = fft_freq_2d(image)
    image_lpf = fft_result * mask
    image_hp = fft_result - image_lpf
    image_hp = np.fft.fftshift(image_hp)
    image_hp = fft_freq_2d(image_hp)
    result = np.abs(image_hp)
    result -= result.min()
    result = result * 255 / result.max()
    return result


def phase_modifying_filter(image: np.ndarray, a: int, k: int) -> np.ndarray:
    fft_result = fft_freq_2d(image)
    fft_shifted = np.fft.fftshift(fft_result)
    N, M = image.shape
    n_values = np.arange(N)
    m_values = np.arange(M)
    n, m = np.meshgrid(n_values, m_values)

    mask = np.exp(
        1j * ((-n * k * 2 * np.pi) / N + (-m * a * 2 * np.pi) / M + (k + a) * np.pi)
    )

    fft_shifted *= mask
    fft_unshifted = np.fft.ifftshift(fft_shifted)
    inv_fft_result = inv_fft_freq_2d(fft_unshifted)

    result = np.abs(inv_fft_result)
    result -= result.min()
    result = result * 255 / result.max()
    return result.clip(0, 255)


def apply_filter(filter_function, *args, **kwargs) -> np.ndarray:
    if filter_function == high_pass_filter_edge:
        return filter_function(*args, **kwargs)
    if len(args) == 0 or not isinstance(args[0], np.ndarray):
        raise ValueError("Input image not provided or invalid.")

    image = args[0]
    if len(image.shape) == 2:  # Grayscale image
        return filter_function(image, *args[1:], **kwargs)
    elif len(image.shape) == 3 and image.shape[2] == 3:  # RGB image
        result_channels = [
            filter_function(image[:, :, i], *args[1:], **kwargs) for i in range(3)
        ]
        return np.stack(result_channels, axis=-1)
    else:
        raise ValueError(
            "Unsupported image format. Only grayscale (2D) or RGB (3D) images are supported."
        )
