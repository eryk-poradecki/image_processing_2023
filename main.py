import numpy as np

from src.argparser import ConsoleParser
from src.image import ImageReader, ImageWriter
from src.filters import low_pass_filter, high_pass_filter, band_pass_filter, band_cut_filter, apply_filter, high_pass_filter_edge, phase_modifying_filter
from src.visualize import visualize_fourier_spectrum, save_fourier_spectrum
from src.fourier_transform import fft_2d

if __name__ == "__main__":
    parser = ConsoleParser()
    args = parser.parse_args()

    img = ImageReader.read(args.filename)
    mask = ImageReader.read(args.mask) if args.mask else None

    if args.visualize:
        original_fft = fft_2d(img)
        save_fourier_spectrum(original_fft, "before.png")

    if args.filter == 'low_pass':
        result = apply_filter(low_pass_filter, img, band_size=args.band)
    elif args.filter == 'high_pass':
        result = apply_filter(high_pass_filter, img, band_size=args.band)
    elif args.filter == 'band_pass':
        result = apply_filter(band_pass_filter, img, band_size_low=args.bandlow, band_size_high=args.bandhigh)
    elif args.filter == 'band_cut':
        result = apply_filter(band_cut_filter, img, band_size_low=args.bandlow, band_size_high=args.bandhigh)
    elif args.filter == 'high_pass_edge':
        result = apply_filter(high_pass_filter_edge, img, mask)
    elif args.filter == 'phase_modifying':
        result = apply_filter(phase_modifying_filter, img, a=args.l, k=args.k)
    else:
        raise ValueError(f'Unsupported filter type: {args.filter}')

    if args.visualize:
        filtered_fft = fft_2d(result)
        save_fourier_spectrum(filtered_fft, "after.png")

    output_path = f"output_{args.filter}.png"

    ImageWriter.write(output_path, result.astype(np.uint8))
