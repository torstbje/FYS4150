import os
import numpy as np
import matplotlib.pyplot as plt

for i in range(10):
    print(" ")
os.system("g++ -o main.out main.cpp -larmadillo -std=c++17")

os.system("./main.out")
