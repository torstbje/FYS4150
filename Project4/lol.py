import numpy as np
import matplotlib.pyplot as plt

"""
def E(S, i, j, L):
    if i == 0:
        E = S(i, j+1) + S(i, j-1) + S(i+1, j) + S(L, j)
    elif i == L:
        E = S(i, j+1) + S(i, j-1) + S(0, j) + S(i-1, j)
    else:
        E = S(i, j+1) + S(i, j-1) + S(i+1, j) + S(i-1, j)
"""
data = np.loadtxt("meanvalues.txt")
energy = data[:,0]
magn = data[:,1]
T = np.linspace(2.3, 2.5, len(energy))
plt.plot(T, energy)
plt.show()

plt.plot(T,magn)
plt.show()
