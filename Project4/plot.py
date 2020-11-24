import numpy as np
import matplotlib.pyplot as plt

L = 300
J = 1
kb = 1
T = np.linspace(0.01,20,1000)
S = np.loadtxt("ValueGrid.txt")

#print(XY)
G = np.zeros((L,L))

for i in range(L):
    for j in range(L):
        G[i,j] = np.random.randint(2,10)%2 - 1
#print(S)


title = str(L) + "x" + str(L)# + ", " + r"$\beta=5$"#r"$\beta = \ln(1+\sqrt{2})/2$"
figurename = "L_" + str(L) + ".pdf"
plt.matshow(S,cmap=plt.cm.Blues)
plt.title(title, y=-0.09)
plt.savefig(figurename)
plt.show()
"""
beta = 1./(kb*T)
Z = 4*(np.cosh(8*J*beta)+3)
E = -(8*J*np.sinh(8*J*beta))/(np.cosh(8*J*beta)+3)
C_V = (8*J*beta)**2*((1+3*np.cosh(8*J*beta))/(3+np.cosh(8*J*beta))**2)
M = (8/Z)*(2+np.exp(8*beta*J))
X = 32*beta*((1/Z)*(1+np.exp(8*J*beta)) - (2/Z**2)*(2+np.exp(8*J*beta))**2)

plt.plot(T, E, label=r"$\langle E\rangle$")
plt.plot(T, C_V, label=r"$C_V$")
plt.plot(T, M, label=r"$\langle |\mathcal{M}|\rangle$")
plt.plot(T, X, label=r"$\chi$")
plt.legend()
plt.xlabel("T  []")
plt.ylabel("")
plt.savefig("ECvMX.pdf")
plt.show()
"""
