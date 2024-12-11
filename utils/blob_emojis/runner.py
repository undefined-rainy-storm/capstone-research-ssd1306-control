from PIL import Image
import numpy as np

# Load the image from a file
image_path = ['angry.png', 'contempt.png', 'digust.png', 'fear.png', 'happy.png', 'neutral.png', 'sad.png', 'surprise.png']
for each in image_path:
    image = Image.open(each).resize((64, 64))
    
    # Check if the image has an alpha channel
    if image.mode == 'RGBA':
        alpha = image.split()[-1]
        image = Image.composite(image, Image.new('RGBA', image.size, (0, 0, 0, 255)), alpha)
    
    # Convert red pixels to black if the image is in RGB or RGBA mode
    if each not in ['angry.png', 'fear.png']:
        if image.mode in ('RGB', 'RGBA'):
            data = np.array(image)
            # filter = (data[:, :, 0] > 237) & (data[:, :, 1] > 100) & (data[:, :, 2] > 40)
            # data[filter] = [0, 0, 0, 255] if image.mode == 'RGBA' else [0, 0, 0]
            filter = (data[:, :, 0] > 230) | (data[:, :, 1] > 230) | (data[:, :, 2] > 230)
            data[filter] = [0, 0, 0, 255] if image.mode == 'RGBA' else [0, 0, 0]
            image = Image.fromarray(data, image.mode)
    
    # Convert the image to grayscale
    image = image.convert('L')
    array = np.array(image)
    bin_array = (array > 127).astype(int)

    strbuf = []
    for row in bin_array:
        rowbuf = []
        for i in range(0, 64, 8):
            rowbuf.append('B' + ''.join(['1' if x == 1 else '0' for x in row[i:i + 8]]))
        strbuf.append(', '.join(rowbuf))

    each = each.split('.')[0]
    with open(f'{each}.h', 'w') as f:
        f.write(
            f'const uint8_t PROGMEM {each}[] = {{\n' +
            ',\n'.join(strbuf) +
            '\n};'
        )
