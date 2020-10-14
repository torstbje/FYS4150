import os
import numpy as np
#import maplotlib.pyplot as plt


T = 30.#float(input("Choose number of days to run the simulations: "))
N = 301 #int(input("Choose number of measurement points: "))

while (True):
    print("choose the number corresponding to the system you want to plot")
    print("--------------------------------------------------------------")
    print("1: Earth and the Sun (stationary)")
    print("2: Earth, Jupiter and the Sun (stationary)")

    print(" ")
    print("c: Change number of days and measurement points")
    print("0: Stop program")
    ans = int(input("System: "))
    if (ans == 0):
        break
    if (ans == "c"):
        T = float(input("Choose number of days to run the simulations: "))
        N = int(input("Choose number of measurement points: "))

    if (ans == 1):
        algo = "Earth"
        #plt.plot(0, 0, "yo", label = "The sun")
        N_movable = 1
    if (ans == 2):
        algo = "EarthJup"
        #plt.plot(0, 0, "yo", label = "The sun")
        N_movable = 2

    os.system("c++ -o main.out main.cpp -larmadillo" + " " + str(N) + " " + str(T) + " " + algo)
    os.system("./main.out")

    in_name = algo + ".txt"
    plot_name = algo + "plot.txt"
    infile = open(in_name)
    names = []
    coordinates = np.zeros()
    line1 = infile.readline().split(" ")
    for name in line1:
        names.append(name)

    time = np.linspace(0,T,N)

    coordinates = np.zeros((N,N_movable,3))         #dimensions correspond to 1:which object, 2:spacial dimension, 3:timestep
    i = 0           #iterator for timestep
    j = 0           #iterator for objects
    for line in infile:
        objects = line.split(",")
        for obj in objects:
            obj = obj.split(" ")
            for k in range(3):
                coordinates[i,j,k] = obj[k]
            j += 1
        i += 1
