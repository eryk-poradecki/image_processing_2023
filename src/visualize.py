import matplotlib.pyplot as plt
import numpy as np


def visualize_fourier_spectrum(fft_2d):
    fft_shifted = np.fft.fftshift(fft_2d)

    magnitude_spectrum = np.abs(fft_shifted)

    plt.imshow(np.log1p(magnitude_spectrum), cmap="viridis")
    plt.colorbar()
    plt.title("Fourier Spectrum")
    plt.show()


def save_fourier_spectrum(fft_2d):
    fft_shifted = np.fft.fftshift(fft_2d)

    magnitude_spectrum = np.abs(fft_shifted)

    plt.imshow(np.log1p(magnitude_spectrum), cmap="viridis")
    plt.colorbar()
    plt.title("Fourier Spectrum")
    plt.savefig("fourier.png")
