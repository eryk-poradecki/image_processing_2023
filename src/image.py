from PIL import Image
import numpy as np

class ImageReader:
    @classmethod
    def read(cls, path):
        return np.array(Image.open(path))

class ImageWriter:
    @classmethod
    def write(cls, path, image):
        Image.fromarray(image).save(path)
