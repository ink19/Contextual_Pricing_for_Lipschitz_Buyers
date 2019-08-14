#!/usr/bin/env  python3
from PIL import Image
import numpy as np

data = np.zeros([1000, 1000], dtype=np.uint8)

for line in open('data.csv', 'r'):
    line_sp = line.split(',')
    x_begin = int(float(line_sp[0]) * 1000)
    x_end = int(float(line_sp[1]) * 1000)
    y_begin = int(999 - float(line_sp[3]) * 1000)
    y_end = int(999 - float(line_sp[2]) * 1000)
    for i in range(x_begin, x_end):
        for j in range(y_end, y_begin):
            data[j][i] = 255

im = Image.fromarray(data)
im.show()
