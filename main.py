import os
import numpy as np
import matplotlib.pyplot as plt


T = float(input("Choose number of days to run the simulations: "))
N = int(input("Choose number of measurement points: "))

while (True):
    print("choose the number corresponding to the system you want to plot")
    print("--------------------------------------------------------------")
    print("1: Circular Earth orbit with stationary sun (Verlet)")
    print("2: Circular Earth orbit with stationary sun (Euler)")
    print("3: Earth, Jupiter and stationary Sun (Verlet)")

    print(" ")
    print("99: Change number of days and measurement points")
    print("0: Stop program")
    ans = int(input("System: "))
    if (ans == 0):
        break
    if (ans == 99):
        T = float(input("Choose number of days to run the simulations: "))
        N = int(input("Choose number of measurement points: "))
        continue

    if (ans == 1):
        algo = "Earth"
        plt.plot(0, 0, "yo", label = "The sun")
        N_movable = 1
    if (ans == 2):
        algo = "EarthEuler"
        plt.plot(0, 0, "yo", label = "The sun")
        N_movable = 1
    if (ans == 3):
        algo = "EarthJup"
        plt.plot(0, 0, "yo", label = "The sun")
        N_movable = 2

    os.system("g++ -o main.out main.cpp -larmadillo")
    os.system("./main.out"  + " " + str(N) + " " + str(T) + " " + algo)

    in_name = algo + ".txt"
    plot_name = algo + "plot.txt"
    infile = open(in_name)
    names = []

    line1 = infile.readline().split(" , ")
    for name in line1:
        names.append(name)

    coordinates = np.zeros((N, N_movable, 3))         #dimensions correspond to 1:timestep, 2:which objects, 3:spacial dimesion
    i = 0                                             #iterator for timestep
    lines = infile.readlines()

    for line in lines:
        j = 0                                         #iterator for objects
        objects = line.split(",")
        for obj in objects:
            obj = obj.split()
            for k in range(3):
                coordinates[i,j,k] = float(obj[k])
            j += 1
        i += 1


    infile.close()
    for i in range(len(coordinates[0,:,0])):
        plt.plot(coordinates[:,i,0],coordinates[:,i,1],label = names[i].capitalize())
    plt.legend()
    plt.show()
