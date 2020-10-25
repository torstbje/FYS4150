import os
import numpy as np
import matplotlib.pyplot as plt

os.system("g++ -o main.out main.cpp -larmadillo")       #compiles the c++ files
T = float(input("Choose number of days to run the simulations: "))
N = int(input("Choose number of measurement points: "))

while (True):
    '''
    Repeatable menu
    '''
    print("Choose the number corresponding to the system you want to plot")
    print("--------------------------------------------------------------")
    print("1: Circular Earth orbit with stationary Sun (Verlet)")
    print("2: Circular Earth orbit with stationary Sun (Euler)")
    print("3: Earth, Jupiter and stationary Sun (Verlet)")
    print("4: Same as 3 but with mass of Jupiter multiplied by 10")
    print("5: Same as 3 but with mass of Jupiter multiplied by 1000")
    print("6: Earth, with custom value of beta and stationary Sun (Verlet)")
    print("7: Elliptical Earth orbit with stationary Sun (Verlet)")
    print("8: All planets and Sun (Verlet)")
    print("9: Mercury with relativistic correction to the Newtonian force, stationary sun (Verlet)")

    print(" ")
    print("99: Change number of days and measurement points")
    print("0: Stop program")
    ans = int(input("Input: "))


    if (ans == 0):
        #Stops the program
        break
    if (ans == 99):
        #Changes amount of days and measurement points
        T = float(input("Choose number of days to run the simulations: "))
        N = int(input("Choose number of measurement points: "))
        continue

    if (ans == 1):
        algo = "Earth"
        N_movable = 1
    if (ans == 2):
        algo = "EarthEuler"
        N_movable = 1
    if (ans == 3):
        algo = "EarthJup"
        N_movable = 2
    if (ans == 4):
        algo = "EarthMegaJup"
        N_movable = 2
    if (ans == 5):
        algo = "EarthGigaJup"
        N_movable = 2
    if (ans == 6):
        algo = "EarthBeta"
        N_movable = 1
    if (ans == 7):
        algo = "EllipticalEarth"
        N_movable = 1
    if (ans == 8):
        algo = "All"
        N_movable = 9
    if (ans == 9):
        algo = "RelMercury"
        N_movable = 1
        T = 36524        #Days in a century


    os.system("./main.out"  + " " + str(N) + " " + str(T) + " " + algo)         #Calls the c++ program

    in_name = algo + ".txt"
    plot_name = algo + "plot.txt"
    infile = open(in_name)                                                      #Reads the file made by the c++ programs
    names = []

    line1 = infile.readline().split(" , ")
    for name in line1:
        names.append(name)

    coordinates = np.zeros((N, N_movable, 3))         #dimensions correspond to 1:timestep, 2:which objects, 3:spacial dimesion
    i = 0                                             #iterator for timestep
    lines = infile.readlines()

    for line in lines:
        '''
        Reads the information into arrays
        '''
        j = 0                                         #iterator for objects
        objects = line.split(",")
        for obj in objects:
            obj = obj.split()
            for k in range(3):
                coordinates[i,j,k] = float(obj[k])
            j += 1
        i += 1

    infile.close()
    if (algo == "RelMercury"):
        #Plots Mercurys perihelion as a function of years
        merc = coordinates[:,0,:-1]             #We know mercury (in this model) does not have z coordinates
        theta = []
        time = []
        prev = 1                                #Previous position (This is set to 1 so it finds the first perihelion)
        distance = np.linalg.norm(merc[0,:])    #Current distance
        n = 0
        for i in range(N-1):
            #Loops over timesteps
            next = np.linalg.norm(merc[i+1,:])
            if (distance < prev and distance < next):
                n += 1
                t = i*T/(N*365.24)
                theta.append(np.arctan(merc[i,1]/merc[i,0])/(60**4))
                time.append(t);
                #theta.append(merc[i,1])
                #time.append(merc[i,0])
            prev = distance
            distance = next

        print(theta[-1])
        plt.plot(time,theta ,'bo', markersize = 1)
        plt.title("Perihelion of Mercury over 100 years")
        plt.xlabel("Time [Years]")
        plt.ylabel("Angle of Perihelion")
        plt.show()

    if (ans != 8):
        #Plots a stationary sun
        plt.plot(0, 0, "yo", label = "The sun")

    for i in range(len(coordinates[0,:,0])):
        #Loops over and plots all nonstationary objects
        names[i] = names[i].capitalize()
        plt.plot(coordinates[:,i,0],coordinates[:,i,1],label = names[i], markersize = 1)

    plt.title("Motion of %s plotted over %s days" % (", ".join(names), int(T)))
    plt.xlabel("x [AU]")
    plt.ylabel("y [AU]")
    plt.legend()
    plt.show()
