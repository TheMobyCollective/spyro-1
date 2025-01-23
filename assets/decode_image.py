from PIL import Image
import numpy as np
import struct
import sys

def decode_24bit_image(input_data, width, height):
    """
    Decode a 24-bit compressed image

    :param data: Bytearray of input compressed image data.
    :param width: Width of the image.
    :param height: Height of the image.
    :return: A PIL Image object.
    """
    idx = 0

    pos = 0

    image = Image.new("RGB", (width, height))

    buf = np.zeros((width * height * 3), dtype=np.uint8)

    while True:
        # Check the most significant bit to determine if we're out of data
        if (input_data[idx] & 0x80000000) != 0:
            break

        # Calculate the number of pixels to process and the offset
        offset = input_data[idx] & 0x1ffff
        size = input_data[idx] >> 17
        idx += 1
        pos += offset * 4

        for _ in range(size):
            buf[pos + 0] = input_data[idx] & 0xFF
            buf[pos + 1] = (input_data[idx] >> 8) & 0xFF
            buf[pos + 2] = (input_data[idx] >> 16) & 0xFF
            buf[pos + 3] = (input_data[idx] >> 24) & 0xFF
            idx += 1
            pos += 4

    image.putdata(list(zip(buf[0::3], buf[1::3], buf[2::3])))

    return image


# Have to specify input and output file names
if len(sys.argv) != 3:
    print("Usage: python decode_image.py <input_file> <output_file>")
    sys.exit(1)

with open(sys.argv[1], "rb") as f:
    compressed_data = f.read()
    # Convert binary data to a list of 32-bit unsigned integers
    num_integers = len(compressed_data) // 4
    format_string = f'{num_integers}I'
    image = decode_24bit_image(list(struct.unpack(format_string, compressed_data)), width=512, height=240)
    image.save(sys.argv[2])
