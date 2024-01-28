import argparse


class ConsoleParser:
    def __init__(self):
        self.parser = argparse.ArgumentParser(description="Argument Parser")
        self._add_arguments()

    def _add_arguments(self):
        self.parser.add_argument(
            "-f", "--filename", type=str, help="Specify the file name"
        )
        self.parser.add_argument("--mask", type=str, help="Specify the mask file name")
        self.parser.add_argument(
            "--filter",
            choices=[
                "low_pass",
                "high_pass",
                "band_pass",
                "band_cut",
                "high_pass_edge",
                "phase_modifying",
                "low_pass_sharp",
                "high_pass_sharp",
            ],
            help="Specify the filter type",
        )
        self.parser.add_argument(
            "-v",
            "--visualize",
            action="store_true",
            help="Specify if FFT should be visualized",
        )
        self.parser.add_argument(
            "--band", type=int, help="Specify the band size for filters"
        )
        self.parser.add_argument(
            "--bandlow",
            type=int,
            help="Specify the low band size for band-pass and band-cut filters",
        )
        self.parser.add_argument(
            "--bandhigh",
            type=int,
            help="Specify the high band size for band-pass and band-cut filters",
        )
        self.parser.add_argument(
            "-l", type=float, help="Specify the l parameter for phase modifying filters"
        )
        self.parser.add_argument(
            "-k", type=float, help="Specify the k parameter for phase modifying filters"
        )

    def parse_args(self):
        return self.parser.parse_args()
