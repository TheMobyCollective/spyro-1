
from PIL import Image
import struct
import sys

def encode_24bit_image(image):
    """
    Encode a 24-bit image

    :param image: A PIL Image object.
    :return: A bytearray of compressed image data.
    """

    data = list(image.getdata())

    # Turn the list of RGB tuples into a list of 8-bit integers
    data = [x for rgb in data for x in rgb]

    # Convert the image data to a list of 32-bit integers
    input_data = []
    for i in range(0, len(data), 4):
        input_data.append(data[i] | (data[i + 1] << 8) | (data[i + 2] << 16) | (data[i + 3] << 24))

    # Compress the image data
    # This essentially just removes any zero sequences by skipping over them
    compressed_data = []

    idx = 0
    lastOffset = 0
    while idx < len(input_data):
        # Count the number of zeros
        if input_data[idx] == 0:
          while idx < len(input_data) and input_data[idx] == 0:
              idx += 1
        
        # Start with the header that specifies the offset and the size of ints that aren't zero
        offset = idx
        size = 0
        data = []
        while idx < len(input_data) and input_data[idx] != 0:
            data.append(input_data[idx])
            idx += 1
            size += 1

            if size >= 0x2000:
                break
        
        if size == 0:
            continue

        # Write the header
        compressed_data.append((offset - lastOffset) | (size << 17))

        lastOffset = offset + size

        # Write the data
        for d in data:
            compressed_data.append(d)

    # Write the end of data marker
    compressed_data.append(0xFFFFFFFF)

    return compressed_data

# Have to specify input and output file names
if len(sys.argv) != 3:
    print("Usage: python encode_image.py <input_file> <output_file>")
    sys.exit(1)

with open(sys.argv[1], "rb") as f:
    image = Image.open(f)
    compressed_data = encode_24bit_image(image.convert('RGB'))
    # Convert the compressed data to a binary string
    format_string = f'{len(compressed_data)}I'
    binary_data = struct.pack(format_string, *compressed_data)
    with open(sys.argv[2], "wb") as out:
        out.write(binary_data)