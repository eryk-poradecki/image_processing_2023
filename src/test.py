import numpy as np
import matplotlib.pyplot as plt

N = 256 

#arctan gets the angle

def generate_mask(r1: int, r2: int) -> np.ndarray:
    assert r1 < r2
    
    image_array = np.zeros((N, N), dtype=np.uint8)
    center = (N // 2, N // 2)

    x, y = np.indices((N, N))

    mask1 = ((x - center[0])**2 + (y - center[1])**2) <= r1**2
    mask2 = ((x - center[0])**2 + (y - center[1])**2) <= r2**2
    image_array[mask2] = 1
    image_array[mask1] = 0
    
    return image_array

def generate_mask_angles(r1: int, r2: int, a1: int, a2: int, N: int = N) -> np.ndarray:
    assert r1 < r2
    
    image_array = np.zeros((N, N), dtype=np.uint8)
    center = (N // 2, N // 2)

    x, y = np.indices((N, N))

    theta = np.arctan2(y - center[1], x - center[0])
    theta = (theta + 2 * np.pi) % (2 * np.pi)

    r = np.sqrt((x - center[0])**2 + (y - center[1])**2)

    mask1 = (r <= r1) & (a1 <= theta) & (theta <= a2)
    mask2 = (r <= r2) & (a1 <= theta) & (theta <= a2)

    image_array[mask2] = 1
    image_array[mask1] = 0
    
    return image_array
    
def combine_masks(mask1: np.ndarray, mask2: np.ndarray) -> np.ndarray:
    image_array = generate_mask_angles(5, 255, np.radians(30), np.radians(90))
    mirrored_image_array = np.flipud(np.fliplr(image_array))
    sum_result = image_array + mirrored_image_array
    
    return sum_result

image_array = generate_mask_angles(5, 255, np.radians(30), np.radians(90))
mirrored_image_array = np.flipud(np.fliplr(image_array))
sum_result = image_array + mirrored_image_array
plt.imshow(sum_result, cmap='gray', interpolation='nearest')
plt.title('dynamic mask')
plt.show()
