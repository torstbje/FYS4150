#include <iostream>
#include <fstream>
#include "Node.hpp"
#include "Node.cpp"
#include "Lattice.cpp"
#include "Traverser.cpp"

using namespace std;

int main(int argc, char const *argv[]){

<<<<<<< HEAD
  int l = 8;
  Lattice grid(l,random);
  grid.monteCarloCycle();
=======
  int l = stoi(argv[1]);
  double temperature = stod(argv[2]);
  int n_cycles = stoi(argv[3]);
  string state = argv[4];
  Lattice grid(l,state,temperature);

  ofstream file("energy_magnetization.txt");
  ofstream meanFile("meanvalues.txt");

  for (int i = 0; i < n_cycles; i++){
    grid.monteCarloCycle();
    file << i << " " << grid.getEnergy() << " " << abs(grid.getMagnetization()) << " "<< grid.acceptence();
    file << " " << pow(grid.getEnergy(),2) << " " << pow(grid.getMagnetization(),2) << endl;

    meanFile << grid.getAveE()/(pow(l,2)*(i+1)) << " " << grid.getAveM()/(pow(l,2)*(i+1)) << " " << grid.getAveESQ()/(pow(l,2)*(i+1)) << " ";
    meanFile << grid.getAveMSQ()/(pow(l,2)*(i+1)) << " "<< grid.getAbsM()/(pow(l,2)*(i+1)) << endl;
  }
  meanFile.close();
  file.close();




  vec probs = grid.getEnergyProbabilities();
  ofstream probFile("energy_probabilities.txt");
  int precalcPow = -pow(l,2);
  for (int i = 0; i < pow(l,2) + 1; i++){
    probFile << precalcPow + 4*i << " " << probs(i) << endl;
  }
  probFile.close();

>>>>>>> b393b70c695f8e791c4f7f560daec4f7f45a7ad0
  grid.writeCoords();

  return 1;
}
