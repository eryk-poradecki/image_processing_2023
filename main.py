from src.argparser import ConsoleParser
from src.image import ImageReader, ImageWriter
if __name__ == '__main__':
    parser = ConsoleParser()
    args = parser.parse_args()
    print(args.filename)
    img = ImageReader.read(args.filename)
    ImageWriter.write('output.png', img)