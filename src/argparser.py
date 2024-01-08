import argparse

class ConsoleParser:
    def __init__(self):
        self.parser = argparse.ArgumentParser(description='Argument Parser')
        self._add_arguments()

    def _add_arguments(self):
        self.parser.add_argument('-f', '--filename', type=str, help='Specify the file name')

    def parse_args(self):
        return self.parser.parse_args()
