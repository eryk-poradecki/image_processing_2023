import matplotlib.pyplot as plt
import numpy as np

from src.argparser import ConsoleParser
from src.filters import (
    apply_filter,
    band_cut_filter,
    band_pass_filter,
    create_circle_function_window,
    create_step_function_window,
    high_pass_filter,
    high_pass_filter_edge,
    high_pass_filter_edge_dynamic,
    high_pass_filter_sharp,
    low_pass_filter,
    low_pass_filter_sharp,
    phase_modifying_filter,
)
from src.fourier_transform import fft_2d
from src.image import ImageReader, ImageWriter
from src.visualize import save_fourier_spectrum, visualize_fourier_spectrum

# TODO: add plot for fast fourier
if __name__ == "__main__":

    parser = ConsoleParser()
    args = parser.parse_args()
    args.filename = "IMG_1/lena.bmp"
    args.filter = "high_pass_sharp"
    args.band = 50
    img = ImageReader.read(args.filename)

    # result_1 = high_pass_filter_edge_dynamic(img, 50, 150, 80, 100)
    # original_fft = fft_2d(img)
    # save_fourier_spectrum(original_fft, "before.png")
    # filtered_fft = fft_2d(result_1)
    # save_fourier_spectrum(filtered_fft, "after.png")
    # ImageWriter.write("dynamic.png", result_1.astype(np.uint8))

    mask = ImageReader.read(args.mask) if args.mask else None

    if args.visualize:
        original_fft = fft_2d(img)
        save_fourier_spectrum(original_fft, "before.png")

    if args.filter == "low_pass":
        result = apply_filter(low_pass_filter, img, band_size=args.band)
    elif args.filter == "low_pass_sharp":
        result = apply_filter(low_pass_filter_sharp, img, band_size=args.band)
    elif args.filter == "high_pass":
        result = apply_filter(high_pass_filter, img, band_size=args.band)
    elif args.filter == "high_pass_sharp":
        result = apply_filter(high_pass_filter_sharp, img, band_size=args.band)
    elif args.filter == "band_pass":
        result = apply_filter(
            band_pass_filter,
            img,
            band_size_low=args.bandlow,
            band_size_high=args.bandhigh,
        )
    elif args.filter == "band_cut":
        result = apply_filter(
            band_cut_filter,
            img,
            band_size_low=args.bandlow,
            band_size_high=args.bandhigh,
        )
    elif args.filter == "high_pass_edge":
        result = apply_filter(high_pass_filter_edge, img, mask)
    elif args.filter == "phase_modifying":
        result = apply_filter(phase_modifying_filter, img, a=args.l, k=args.k)
    elif args.filter == "high_pass_edge_dynamic":
        result = apply_filter(high_pass_filter_edge_dynamic, img, 50, 150, 80, 100)
    else:
        raise ValueError(f"Unsupported filter type: {args.filter}")

    if args.visualize:
        filtered_fft = fft_2d(result)
        save_fourier_spectrum(filtered_fft, "after.png")

    output_path = f"output_{args.filter}.png"

    ImageWriter.write(output_path, result.astype(np.uint8))
