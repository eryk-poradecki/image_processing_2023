import numpy as np

from src.argparser import ConsoleParser
from src.image import ImageReader, ImageWriter
from src.filters import low_pass_filter, high_pass_filter, band_pass_filter, band_cut_filter, apply_filter, high_pass_filter_edge, phase_modifying_filter

if __name__ == "__main__":
    parser = ConsoleParser()
    args = parser.parse_args()

    img = ImageReader.read(args.filename)
    mask = ImageReader.read(args.mask) if args.mask else None

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
        result = apply_filter(phase_modifying_filter, img, l=args.l, k=args.k)
    else:
        raise ValueError(f'Unsupported filter type: {args.filter}')
    
    output_path = f"output_{args.filter}.png"
    
    ImageWriter.write(output_path, result.astype(np.uint8))

