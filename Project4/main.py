import os
import numpy as np
import matplotlib.pyplot as plt

for i in range(8):
    print(" ")
os.system("g++ -o main.out main.cpp -larmadillo -std=c++17")

while (True):
    """
    Repeatable menu
    """
    print("Choose starting spin configuration")
    print("0: Stop program")
    print("1: Random states")
    print("2: Alligned states (All spin up)")
    ans = int(input("Input: "))
    if (ans == 0):
        break
    elif (ans == 1):
        version = " random"
    else:
        version = " alligned"

    print("Plot against temperature or cycles")
    print("0: Stop program")
    print("1: Temperature")
    print("2: Number of cycles")
    ans = int(input("Input: "))
    if (ans == 0):
        break
    elif (ans == 1):
        temp = np.arange(2,2.3,0.01)
        k = len(temp)
        energies = np.zeros(k)
        magnetization = np.zeros(k)
        chi = np.zeros(k)
        Cv = np.zeros(k)
        print("Choose lattice dimension")
        L = int(input("Input: "))
        print("Choose number of MonteCarlo cycles")
        n = int(input("Input: "))
        it = 0
        for T in temp:
            drive_string = "./main.out " + str(L) + " " + str(T) + " " + str(n) + version
            os.system(drive_string)
            infile = open("meanvalues.txt")
            numbers = infile.readline().split(" ")

            E = float(numbers[0])
            M = float(numbers[4])
            E2 = float(numbers[2])
            M2 = float(numbers[3])

            infile.close()

            energies[it] = E
            magnetization[it] = M
            chi[it] = (M2-M**2)/T
            Cv[it] = (E2-E**2)/(T**2)
            it += 1
        plt.plot(temp,energies,'r',label = "Energy")
        plt.plot(temp,magnetization,'b',label = "Magnetization")
        plt.plot(temp,chi,'m',label = "Susceptibility")
        plt.plot(temp,Cv,'y',label = "Specific heat")

        plt.title("Energy and magnetization for %d Monte-Carlo cycles with L = %d" % (n,L))
        plt.legend()
        plt.show()


    else:

        print("Choose temperature ([kT/J])")
        temp = float(input("Input: "))
        print("Choose lattice dimension")
        L = int(input("Input: "))
        print("Choose number of MonteCarlo cycles")
        n = int(input("Input: "))


        drive_string = "./main.out " + str(L) + " " + str(temp) + " " + str(n) + version
        os.system(drive_string)
        infile = open("energy_magnetization.txt");
        nList = np.zeros(n)
        energy = np.zeros(n)
        magnetization = np.zeros(n)

        energy_var = np.zeros(n)
        magnet_var = np.zeros(n)

        n_changes = np.zeros(n)
        i = 0
        for line in infile:
            numbers = line.split()
            nList[i] = numbers[0]
            energy[i] = int(numbers[1])
            magnetization[i] = int(numbers[2])
            n_changes[i] = int(numbers[3])
            i += 1

        infile.close()

        infile2 = open("meanvalues.txt")
        i = 0
        for line in infile2:
            numbers = line.split()
            energy_var[i] = float(numbers[2]) - float(numbers[0])**2
            magnet_var[i] = float(numbers[3]) - float(numbers[4])**2
            i += 1


        chi = magnet_var/temp
        Cv = energy_var/(temp**2)


        plt.plot(nList,energy,'r',label = "Energy")
        plt.plot(nList,magnetization,'b',label = "Magnetization")
        plt.plot(nList,Cv,'m',label = "Susceptibility")
        plt.plot(nList,chi,'y',label = "Specific heat")
        plt.title("Change in Energy and magnetization for lattice at temperature T = %.2f" % (temp))
        plt.xlabel("MonteCarlo cycles")
        plt.ylabel("Value")
        plt.legend()
        plt.show()

        plt.plot(nList,n_changes,'b')
        plt.title("Amount of accepted energy changes per cycle")
        plt.xlabel("Number of cycles")
        plt.show()

        infile = open("energy_probabilities.txt")

        energyvalues = np.zeros(L**2 + 1)
        n_values = np.zeros(L**2 + 1)
        i = 0
        for line in infile:
            numbers = line.split()
            energyvalues[i] = numbers[0]
            n_values[i] = numbers[1]
            i += 1

        n_values = n_values/np.linalg.norm(n_values)
        plt.plot(energyvalues,n_values,'b')
        plt.title("probability density of Energies")
        plt.xlabel("Energy")
        plt.ylabel("probability")
        plt.show()
