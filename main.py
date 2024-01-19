import numpy as np

from src.argparser import ConsoleParser
from src.fourier_transform import fft_2d, inv_fft_2d
from src.image import ImageReader, ImageWriter
from src.visualize import save_fourier_spectrum, visualize_fourier_spectrum


if __name__ == "__main__":
    parser = ConsoleParser()
    # args = parser.parse_args()
    # print(args.filename)
    img = ImageReader.read("lenag.bmp")
    ImageWriter.write("output.png", img)

    fft = inv_fft_2d(img)
    inv = fft_2d(fft)
    # visualize_fourier_spectrum(fft)
    # visualize_fourier_spectrum(img)
    save_fourier_spectrum(fft)
