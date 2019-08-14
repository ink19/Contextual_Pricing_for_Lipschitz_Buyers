#!/usr/bin/env  python3
import matplotlib.pyplot as plt
import numpy as np

X = np.linspace(0, 1, 256, endpoint=True)
for line in open('data.csv', 'r'):
    line_sp = line.split(',')
    k = float(line_sp[0])
    b = float(line_sp[1])
    if line_sp[2] == '0\n':
        #dec
        Y = - np.abs(k - X) + b
        plt.plot(X, Y, color='green')
    else:
        #inc
        Y = np.abs(k - X) + b
        plt.plot(X, Y, color='blue')
Y = 0.5 * (X - 0.5) * (X - 0.5)
plt.plot(X, Y, color='red')
plt.axis([0, 1, 0, 1])
plt.show()