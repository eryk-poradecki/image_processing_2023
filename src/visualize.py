import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


def visualize_fourier_spectrum(fft_2d):
    fft_shifted = np.fft.fftshift(fft_2d)

    magnitude_spectrum = np.abs(fft_shifted)

    plt.imshow(10 * np.log1p(magnitude_spectrum), cmap="viridis")
    plt.colorbar()
    plt.title("Fourier Spectrum")
    plt.show()


def save_fourier_spectrum(fft_2d, path):
    fft_shifted = np.fft.fftshift(fft_2d)

    # magnitude_spectrum = np.abs(fft_shifted)

    image_data = (10 * np.log1p(fft_shifted)).astype(np.uint8)

    image = Image.fromarray(image_data, mode="L")

    image.save(path)
